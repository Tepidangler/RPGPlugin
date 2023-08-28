#include "AbilityBase.h"

UAbilityBase::UAbilityBase()
{
	Name = "Default Name";
	Cost = 0.f;
	CastTime = 0.f;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
}