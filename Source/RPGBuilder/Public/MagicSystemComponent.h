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

	UFUNCTION(BlueprintCallable)
		float CalculateMagicalDamage(AActor* DamageCauser, AActor* DamageReciever, AMagicBase* Spell);

		void CastSpell(AMagicBase* Spell, AActor* Target);




public:
	// Level, Spell
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Magic")
	TMap<float, TSubclassOf<AMagicBase>> MagicList;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magic Info")
	AController* Controller;
};

