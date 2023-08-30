#pragma once
#include "CoreMinimal.h"
#include "ASComponent.h"
#include "MagicBase.h"
#include "MagicSystemComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RPGBUILDER_API UMagicSystemComponent : public UASComponent
{
	GENERATED_BODY()

public:
	UMagicSystemComponent();

public:
	// Level, Spell
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Magic")
	TMap<float, TSubclassOf<AMagicBase>> MagicList;
};

