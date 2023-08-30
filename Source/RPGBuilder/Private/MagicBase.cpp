#include "MagicBase.h"
#include "CharacterBase.h"
#include "Kismet/GameplayStatics.h"

AMagicBase::AMagicBase()
{
	Name = "Default Name";
	Cost = 0.f;
	CastTime = 0.f;
	BuffMultiplier = 1.f;
	DebuffMultiplier = 0.05f;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	
}

void AMagicBase::AddBuff()
{
	ACharacterBase* MC = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0));
	check(MC);
	MC->AddMagicBuff(BuffMultiplier, BuffType);
}


void AMagicBase::AddDebuff()
{
	ACharacterBase* MC = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0));
	check(MC);
	MC->AddMagicDebuff(DebuffMultiplier, DebuffType);
}
