#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityBase.h"
#include "ASComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RPGBUILDER_API UASComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UASComponent();

public:

	TMap<float, TSubclassOf<UAbilityBase*>> AbilityList;
};

