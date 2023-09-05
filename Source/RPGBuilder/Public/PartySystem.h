#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterBase.h"
#include "PartySystem.generated.h"

UCLASS()
class RPGBUILDER_API UPartySystem : public UObject
{
	GENERATED_BODY()

public:
	UPartySystem();

public:

	TArray<ACharacterBase*> Party;

	int PartyLimit;

};

