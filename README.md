# Tick Collector Plugin

<h1>Usage:</h1>

- Disable tick in your actor
- Inherit ITickCollectorInterface to your actor

```cpp
class YOURPOJECT_API AMyAwesomeClass : public AActor, public ITickCollectorInterface
```

- Add this to your beginplay:

```cpp
UWorld* World = GetWorld();
if(World)
    {
        if(UTickCollectionWorldSubsystem* TickCollectionWorldSubsystem = World->GetSubsystem<UTickCollectionWorldSubsystem>())
        {
            TickCollectionWorldSubsystem->AddToCollection(this);
        }
    }
 ```

Step 4- override CollectionTick() and implement your tick logic there, if you want you can call Super::Tick()

```cpp
// .h
virtual void CollectionTick(float DeltaTime);

// .cpp
void AMyAwesomeClass::CollectionTick(float DeltaTime)
{
    Super::Tick(DeltaTime); // if you need it. you dont always need to call it.
    
    // your awesome logic here.
}
 ```

step 5- Have fun of instant micro optimisation because your call time of Tick() function is reduced slightly, with more actors it will be more visible on framerate, with fewer actors it doesnt even worth it. What this function does is adds your class to an array and loops them on *single* tick. That way your *call time* of Tick() function reduces. Tadaa!!..