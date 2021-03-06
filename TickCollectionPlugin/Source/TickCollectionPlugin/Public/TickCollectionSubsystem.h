// Made by Intax

#pragma once

#include "CoreMinimal.h"
#include "Engine/Public/Subsystems/WorldSubsystem.h"
#include "TickCollectionSubsystem.generated.h"

DECLARE_STATS_GROUP(TEXT("TickCollectionPlugin"), STATGROUP_TickCollectionPlugin, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("Total Collector Tick Time"), STAT_TickCollectorTotal, STATGROUP_TickCollectionPlugin);

// We dont want runtime allocations of ObjectCollection because they are very expensive. So instead we can
// allocate them all in the beginning. This constexpr variable also gonna be calculated in compile-time.
constexpr int32 ReserveCount = 200;

UCLASS()
class TICKCOLLECTIONPLUGIN_API UTickCollectionWorldSubsystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

	UTickCollectionWorldSubsystem()
	{
		
	}

	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
		bInitialized = true;
		
		ObjectCollection.Reserve(ReserveCount);
	}

	/* The actual collection data. */
	UPROPERTY()
	TArray<UObject*> ObjectCollection;

	bool bInitialized = false;
	
	/* Where we tick all collected objects. */
	virtual void Tick(float DeltaTime) override final;

	/* I'm not sure if this thing works like this.. but it seems so based on source code.. so lets see ¯\_(ツ)_/¯ */
	TStatId GetStatId() const override
	{
		return TStatId();
	}

	//=========================================
	// Setters & Getters 
	//=========================================

	public:

	FORCEINLINE void AddToCollection(UObject* Object) { ObjectCollection.Add(Object); }
	FORCEINLINE int32 GetCollectionCount() const { return ObjectCollection.Num(); }
};
