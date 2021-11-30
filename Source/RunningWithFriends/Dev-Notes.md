# Dev Log

## 30/11/21

Added in replication for the first time. Trying to get Player Track data replicated over for the Level Builder
Subsystem. 

On a single ListenServer client I can see it spawning but when I remember to filter the log for the right category
I got the following below. 

Bed time now but tomorrow at some point I need to look in setting those struct property defaults and change the code
where clients try to find RepActor. Since the RepActor was spawnned by the server it should be created by the server on
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