#include "MagicSystemComponent.h"
#include "CharacterBase.h"
#include "EnemyBase.h"
#include "StatsComponent.h"

UMagicSystemComponent::UMagicSystemComponent()
{

}

void UMagicSystemComponent::CastSpell(AMagicBase* Spell, AActor* Target)
{
	Spell->SetCaster(this->GetOwner());
	Spell->SetInstigator(Controller);
	Spell->FireInDirection(Target->GetActorLocation());
}

float UMagicSystemComponent::CalculateMagicalDamage(AActor* DamageCauser, AActor* DamageReciever, AMagicBase* Spell)
{
	ACharacterBase* MC = Cast<ACharacterBase>(DamageCauser);
	AEnemyBase* Enemy = Cast<AEnemyBase>(DamageReciever);
	if (MC && Enemy) //If the player is the one who attacked
	{
		float BaseDamage;
		float Damage1;
		float Damage2;
		float MagicBaseModifier = MC->StatsComponent->MagicAttack.GetCurrentValue() - MC->StatsComponent->MagicAttack.GetValueAtLevel(MC->StatsComponent->Level);
		//Magic Defense
		float EnemyDefenseModifier = Enemy->StatsComponent->MagicDefense.GetCurrentValue() - Enemy->StatsComponent->MagicDefense.GetValueAtLevel(Enemy->StatsComponent->Level);
		if (EnemyDefenseModifier <= 0.f)
		{
			EnemyDefenseModifier = 1.f;
		}

		float EnemyDefense = (Enemy->StatsComponent->MagicDefense.GetValueAtLevel(Enemy->StatsComponent->Level) * (100 + EnemyDefenseModifier)) / 100;
		if (MagicBaseModifier <= 0.f)
		{
			MagicBaseModifier = 1.f;
		}
		//Base Damage = 6 * (MAt + Lvl)
		//Damage = [Base Damage * (100 + Magical Base Mod) / 100]

		BaseDamage = 6 * (MC->StatsComponent->MagicAttack.GetValueAtLevel(MC->StatsComponent->Level) + MC->StatsComponent->Level);
		Damage1 = (BaseDamage * (100 + MagicBaseModifier)) / 100;
		Damage2 = (Damage1 * (512 - EnemyDefense)) / 512;
		if (Spell->bIsRestoritive)
		{
			return Damage2 * -1;
		}

		return Damage2;
	}

	Enemy = Cast<AEnemyBase>(DamageCauser);
	MC = Cast<ACharacterBase>(DamageReciever);
	if (Enemy && MC) //If the enemy is the one who attacked
	{
		float BaseDamage;
		float Damage1;
		float Damage2;
		float MagicBaseModifier = Enemy->StatsComponent->MagicAttack.GetCurrentValue() - Enemy->StatsComponent->MagicAttack.GetValueAtLevel(Enemy->StatsComponent->Level);
		//Magic Defense
		float PlayerDefenseModifier = MC->StatsComponent->MagicDefense.GetCurrentValue() - MC->StatsComponent->MagicDefense.GetValueAtLevel(MC->StatsComponent->Level);
		if (PlayerDefenseModifier <= 0.f)
		{
			PlayerDefenseModifier = 1.f;
		}

		float PlayerDefense = (MC->StatsComponent->MagicDefense.GetValueAtLevel(MC->StatsComponent->Level) * (100 + PlayerDefenseModifier)) / 100;
		if (MagicBaseModifier <= 0.f)
		{
			MagicBaseModifier = 1.f;
		}
		//Base Damage = 6 * (MAt + Lvl)
		//Damage = [Base Damage * (100 + Magical Base Mod) / 100]

		BaseDamage = 6 * (Enemy->StatsComponent->MagicAttack.GetValueAtLevel(Enemy->StatsComponent->Level) + Enemy->StatsComponent->Level);
		Damage1 = (BaseDamage * (100 + MagicBaseModifier)) / 100;
		Damage2 = (Damage1 * (512 - PlayerDefense)) / 512;
		if (Spell->bIsRestoritive)
		{
			return Damage2 * -1;
		}
		return Damage2;
	}

}