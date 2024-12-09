#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterBase.h"
#include "PartySystem.generated.h"

UCLASS(Blueprintable)
class RPGBUILDER_API UPartySystem : public UObject
{
	GENERATED_BODY()

public:
	UPartySystem();
	UFUNCTION(BlueprintCallable)
	ACharacterBase* GetPrimaryPartyMember();
	UFUNCTION(BlueprintCallable)
	void AttachPartyMember(ACharacterBase* Value);
	UFUNCTION(BlueprintCallable)
	void DetachPartyMember(ACharacterBase* Value);
	UFUNCTION(BlueprintCallable)
	void ReplacePartyMember(int Key, ACharacterBase* Value);
	UFUNCTION(BlueprintCallable)
	TMap<int, ACharacterBase*> GetMembers();
	UFUNCTION(BlueprintCallable)
	int FindMember(ACharacterBase* Value);
	UFUNCTION(BlueprintCallable)
	void SetPrimaryPartyMember(int Key);
	UFUNCTION(BlueprintCallable)
	void SetPartyLimit(int Limit);
	UFUNCTION(BlueprintCallable)
	int GetPartyLimit();
	UFUNCTION(BlueprintCallable)
	void SetPlayerControlledMember(int Key);

public:

	UPROPERTY()
	TMap<int, ACharacterBase*> Party;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Party")
	int PartyLimit;
	UPROPERTY()
	int ControlledCharacterKey;
	UPROPERTY()
	int32 Money;

};

