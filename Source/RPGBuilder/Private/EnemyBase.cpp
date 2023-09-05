#include "EnemyBase.h"
#include "StatsComponent.h"
#include "CharacterBase.h"
#include "Kismet/GameplayStatics.h"

AEnemyBase::AEnemyBase()
{
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));

	MagicComponent = CreateDefaultSubobject<UMagicSystemComponent>(TEXT("MagicComponent"));
	MagicComponent->Controller = GetController();
}

void AEnemyBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{

		ACharacterBase* MC = Cast<ACharacterBase>(OtherActor);
		if (MC)
		{
			UGameplayStatics::ApplyDamage(MC, CalculatePhysicalDamage(MC), GetController(), this, DamageTypeClass);
			//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Enemy->HitParticles, Hit.ImpactPoint, FRotator(0.f), true);
		}
		else
		{
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitWorldParticles, Hit.ImpactPoint, FRotator(0.f), true);
		}

	}
}

float AEnemyBase::CalculatePhysicalDamage(ACharacterBase* MC)
{
	float BaseDamage;
	float Damage1;
	float Damage2;
	float AttackBonus;
	float PhysicalBaseModifier = StatsComponent->Strength.GetCurrentValue() - StatsComponent->Strength.GetValueAtLevel(StatsComponent->Level);
	check(MC)
		//Physical Defense
		float PlayerDefenseModifier = MC->StatsComponent->Defense.GetCurrentValue() - StatsComponent->Defense.GetValueAtLevel(MC->StatsComponent->Level);
	if (PlayerDefenseModifier <= 0.f)
	{
		PlayerDefenseModifier = 1.f;
	}

	float PlayerDefense = (MC->StatsComponent->Defense.GetValueAtLevel(MC->StatsComponent->Level) * (100 + PlayerDefenseModifier)) / 100;
	if (PhysicalBaseModifier <= 0.f)
	{
		PhysicalBaseModifier = 1.f;
	}

	//Base Damage = Att + [(Att + Lvl) / 32] * [(Att * Lvl) / 32]
	//Damage = [Base Damage * (100 + Physical Base Mod) / 100

	AttackBonus = Attack + StatsComponent->Strength.GetValueAtLevel(StatsComponent->Level);
	BaseDamage = AttackBonus + ((AttackBonus + StatsComponent->Level) / 32) * ((AttackBonus * StatsComponent->Level) / 32);
	Damage1 = ((BaseDamage * (100 * PhysicalBaseModifier)) / 100);
	Damage2 = (Damage1 * (512 - PlayerDefense)) / 512;
	return Damage2;

}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (StatsComponent->CurrentHealth - DamageAmount <= 0.f)
	{
		StatsComponent->CurrentHealth = 0.f;
		Die(DamageCauser);
		if (DamageCauser)
		{
			ACharacterBase* MC = Cast<ACharacterBase>(DamageCauser);
			if (MC)
			{
				//MC->UpdateCombatTarget();
				//Implement target update here
			}
		}
	}
	else
	{
		StatsComponent->CurrentHealth -= DamageAmount;
	}

	return DamageAmount;
}

void AEnemyBase::Die(AActor* Causer)
{
	//Death Implementation goes here

}