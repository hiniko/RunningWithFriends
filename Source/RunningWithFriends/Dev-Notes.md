# Dev Log

## 14/12/21

Ok I've had a couple of days of just being really confused and unsure what to do when it comes to controlling the replications of level sections in respect to their differing location on the client.

I think the best thing to do is to just let the client handle the positions and get the server to send messages that trigger what needs to happen. As long as I can get the player input replicated on all the clients, it should all be good. I have a feeling I'm going to have more of an issue when it comes to the Player Characters since I'm not using their usual replication code. But I guess we will have to see.

Handling things on the client and making checks and balances on the server is going to be a lot easier to handle that what I'm currently doing to be fair.

So the current thinking is this:

* GameState on the server is responsible for what the level should look like.
  * It deals with calls for new level parts and replicates that to all clients

* The clients will broadcast when an update to the level state is made leaving the Level builder to work out the differences in the new state to the old and handle creating the right pieces in the right place.


Let's see how we get on with that....

## 10/12/21
I've neglected my notes for a few hours and I'm regretting it already. Can't remember what I was supposed to be doing.

So I'm currently trying to do something I consider simple but of course in practice isn't.

_I want the print on screen the current client's `PlayerId`_

I thought the Player Controller would be a good place for this, as each client should only have one. This isn't working out the way I thought it would.

* The code runs on the server
  * This makes sense, as only the server has a `PlayerController` for all of the players. I just need to check that the current instance's NetMode is not `NM_Client`
  * However, I'm using a listen server, where the client is both, and doesn't match the level of `NM_Client`
  * The important take away here is that if working with `Listen Servers`, one must be careful about code that needs to be run on the host itself. Often you will need to check if you are a listen server and run the code you want clients to run, while clients will run it automatically, if the code is triggered from replication. This is an important point to remember
* There are always more Player Controllers than you think there are:
  * The output below shows this with a Listen Server with one client connected.
```
LogRWF: Display: Handling Starting New Player: RWF_GamePlayerController_0
LogRWF: Display: PC: CLIENT ROLE_Authority with ROLE_SimulatedProxy
LogRWF: Display: PC: SERVER  ROLE_Authority with ROLE_None
LogRWF: Display: Handling Starting New Player: RWF_GamePlayerController_1
LogRWF: Display: PC: CLIENT ROLE_AutonomousProxy with ROLE_Authority
```
* This is my current understanding. After we handle the player start:
  * First the Listen Server "Client" Controller appears, Locally seen as Authority and remotely as a Simulated Proxy
  * Then the Server Controller appears. I am basing this as it has no Remote Authority.
  * When a client connects, We see them as an AutonomousProxy locally and a remote role of Authority.
  * However we dont' see a server side version of this come alive?

-- 

OK I think I know what is going on!

I got this output when running in PI in `Net Mode: Play as Client` rather than `Net Mode: Play as Listen Server` 

```
LogRWF: Display: PC: SERVER  ROLE_Authority with ROLE_None
LogRWF: Display: Handling Starting New Player: RWF_GamePlayerController_0
LogRWF: Display: PC: CLIENT ROLE_AutonomousProxy with ROLE_Authority
LogRWF: Display: PC: SERVER  ROLE_Authority with ROLE_None
LogRWF: Display: Handling Starting New Player: RWF_GamePlayerController_1
LogRWF: Display: PC: CLIENT ROLE_AutonomousProxy with ROLE_Authority
```

* Server creates a controller for Client 1 Server side with Local Authority and no Remote
* GameMode handles the start of this new Controller
* Client Creates the Autonomous Proxy Controller locally, which the remote has Authority over it
* The same happens for Client 2

So the take away here is that:

_In ListenServer mode, since the client is the server, It only creates one PlayerController but is a SimulatedProxy Remotely_, 

Also as a bonus you can filter log messages in editor with binary operators! : `RWF && PC | Handling` Gave the above output.

## 8/12/21

So I'm still missing something big here about replication. 

```
LogNet: Warning: UNetDriver::ProcessRemoteFunction: No owning connection for actor RWF_GameState_0. Function AddSectionForPlayer will not be processed.
LogRWF: Display: Replicated PlayerTracks! ROLE_SimulatedProxy, ROLE_Authority
LogRWF: Display: Updating Track's local player flag for 259
```

Currently have it setup so when a new piece of track is added to the game state, an `OnRep_PlayerTracks` function runs. I assumed this would run on all clients. This isn't he case. It only runs on the client with Authority? So how does a client respond to new replicated data coming in?

What I need to do really is for a client to know which track belongs to itself, so I can then start moving / rebasing things around. I have a feeling that isn't going to work much either. 

--

## 7/12/21

Ok! Yesterday's error! Synced up the project at work today hit build and actually got a useful error message!
```
  Circular dependency detected for filename C:\Users\shermanr\PersonalProjects\RunningWithFriends\Source\RunningWithFriends\LevelSection.h!
  Circular dependency detected for filename C:\Users\shermanr\PersonalProjects\RunningWithFriends\Source\RunningWithFriends\LevelSectionsDataTable.h!
```

Well what do you know. I did see a UEAnswers suggesting the same thing, as well as a few others but there you go.
Should be easier to fix now.

--

*Should be easier to fix*. - yeah right. I have actually fixed it now however. 
I don't know why I didnt see this coming earlier. be cause it was quite obvious in hindsight. 
The main issue was that `ALevelSection` now includes the `LevelBuilderSubsystem` as that keeps the `FPlayerTrack` struct.
I though it would be a good idea to keep a reference like that in the level section so I knew how it belonged to.
However `LevelBuilderSubsystem` includes `ALevelSection` as the Template `TSubClassOf` Needs the actual definition of that class in order to compile. It also needed the `FLevelSectionData` struct from the `LevelSectionDataTable` _WHICH_ in itself needed `ALevelSection`. 

Honestly, bit of a rookie error that one. And probably means that I'm not doing too well code design wise either.

--

Second DERP discovered. This time to do with PlayerControllers across the network.

* First, I know that players controllers only exist on:
  * The Server, Which has a Controller for all Connected Players / AI 
  * The Client, However only for the connected player. 
  
To get around this I thought I could Use the Unique ID of the player controller to replicate across. However I couldn't seem to be able to match this against the local players ID.

Turns out `uint32 GetUniqueID()` is a `UObjectBase` Identifier, It does not match across network. Which makes sense. 
What I wanted was `GetPlayerId` from the `PlayerState`

The more you know.

  


## 6/12/21

I don't know why but I started getting this error:

```
  LevelBuilderSubsystem.h(43): [] Unrecognized type 'FLevelSectionData' - type must be a UCLASS, USTRUCT or UENUM
```
The thing is, `FLevelSectionData` IS and always HAS been a `USTRUCT(BlueprintType)`. Clean builds, changing the code slight and some other things but to no effect. 
This is pretty annoying.

## 3/12/21
I have tried a number of things tonight in terms of replication, all I can really say is that I still do not understand it.

I have tried replicating an array of player tracks that should describe the state the clients should be in. This should work really, and since the clients need to move the tracks and players about to rearrange per player this should probably be the way to go. however I was never sure about the roles and ownership needed in order to set this up.

* When a client needs a new piece:
  * does it call an RPC and the server create a new actor on the stop
  * does the client call for a new piece the server tracks it in the PlayerTrack array and then notify clients to create piece?
  * Is there some other better way of doing it?

I'm kind of just hacking around now and I don't really think I'm getting anywhere. Trying to read a few things or find videos that are not blueprint related.

I'm no stranger to client server frameworks, but this one is kicking my butt.

--

Ok this is slightly embarrassing, but I got the spawning of the sections working.

* Firstly, I didnt activate replication on the actors. Big mistake. 
* Secondly, I was right on thinking tha the server spawns it it owns it, so A simple `UFUNCTION(Server, Reliable)` was all that was needed. 

So now all of players spawn in on tracks, and as each one progresses a new one appears. 
There are some errors about ownership however: 

``` 
UNetDriver::ProcessRemoteFunction: No owning connection for actor RWF_GameState_0. Function AddSectionForPlayer will not be processed.
```

Not sure why that is. Probably worth investigating the next chance I have. It's a bit of a issue that I can't reliably track which client threw the warning out, or easily breakpoint per client. I can disable the single threaded mode for multipler and see how that goes however. 


-- 

A thought on game design. The original simple thought was that each player gets a random set, but that feels a bit unfair really. Maybe some kind of "doing well" could mean your opponents have harder courses?

At the very least next time I need to make it so the level gen is already somewhat ahead of the lead player at least

Also, and this one will be a hard one, the client server rearrangement of the tracks...

## 1/12/21
Having issues with understanding replication, roles and running code the server and client.
There are two macros `UE_SERVER` and `WITH_SERVER_CODE` that can exclude code depending on the build but since I'm aiming
for a Listen server I don't think that is going to do much for me until dedicated servers.

So then I need to be able to restrict who can call what code. For example The Server Client is the only one who should be adding players to the `ULevelBuilderSubsystem` and it's replicated actor. However I'm seeing log output that suggests that isn't the case. Doesn't help that I can easily put if the log output was a client or which one.

Realistically though the reason for those log outputs may actually be I'm not setting safe defaults (as noted yesterday) on the `FPlayerTrack` struct. I will try that and see what happens first. Then come back to this who runs what issue.

-- 

Ok the warnings about properties not being initialised properly are gone, and I'm still getting warnings about RepActor not being valid, which I think has to be a Local client thing.

My current understanding is that the server would created the replicated actor and get the clients to make one too. So probably I need to be finding that actor for the `ULevelBuilderSubsystem`. 

Another odd thing however is that when I start `PIE` with only one player I can see the `ALevelBuilderReplication` that was created in the world by the `ULevelSubsystem`. So I am doing something wrong here I think.

--

So I did a bit more reading. I think I am making my life harder by having the `ULevelBuilderSubsystem` have to keep state about the level. So I moved the `FPlayerTrack` to the GameState, since that should be under the authority of the ListenServer and replicated by default to the clients. 

After I put back in the level sections under the players to see what would happen.
With 3 players, each could run and spawn a new section under them. _However_ each would spawn a different section.

This actually makes sense though. Each client is running the code to spawn a new Section actor, and it's random so it isn't the same one. I need to actually make calling out for a new level section a RPC, to get the server to decide which on and _then_ to spawn the correct section in the right place.

Once I get that done I think it is time to see if I can have the position of the tracks different on each client to the server, so players get the desired view of all the other tracks. 

## 30/11/21

Added in replication for the first time. Trying to get Player Track data replicated over for the Level Builder
Subsystem. 

On a single ListenServer client I can see it spawning but when I remember to filter the log for the right category
I got the following below. 

Bed time now but tomorrow at some point I need to look in setting those struct property defaults and change the code
where clients try to find RepActor. Since the RepActor was spawned by the server it should be created by the server on
all of the clients....


```
LogClass: Display: StructProperty FPlayerTrack::TrackPosition is not initialized properly. Module:RunningWithFriends File:LevelBuilderSubsystem.h
LogClass: Display: UInt32Property FPlayerTrack::OwningPlayerID is not initialized properly. Module:RunningWithFriends File:LevelBuilderSubsystem.h
LogLevelBuilder: Display: Tried to create LevelBuilderRepActor got 737867136
LogLevelBuilder: Error: RepActor was not valid! Bailing...
LogLevelBuilder: Display: Tried to create LevelBuilderRepActor got 740494208
LogLevelBuilder: Error: RepActor was not valid! Bailing...
LogLevelBuilder: Display: Tried to create LevelBuilderRepActor got 664137344
LogLevelBuilder: Display: Tried to create LevelBuilderRepActor got 1339584128
LogLevelBuilder: Error: RepActor was not valid! Bailing...
LogLevelBuilder: Error: RepActor was not valid! Bailing...
LogLevelBuilder: Display: Tried to create LevelBuilderRepActor got 707915392
LogLevelBuilder: Error: RepActor was not valid! Bailing...
````