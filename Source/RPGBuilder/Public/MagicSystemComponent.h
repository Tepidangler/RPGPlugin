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

	TMap<float, TSubclassOf<UMagicBase*>> MagicList;
};

