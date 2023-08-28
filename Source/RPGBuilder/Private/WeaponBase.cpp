#include "WeaponBase.h"
#include "CharacterBase.h"
#include "InventoryComponent.h"
#include "StatsComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	Damage = 0;
	Strength = 0;
	Agility = 0;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentHit.AddDynamic(this, &AWeaponBase::OnHit);

}

void AWeaponBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		/**
		AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
		if (Enemy)
		{
			check(WeaponOwner);
			//UGameplayStatics::ApplyDamage(Enemy, CalculateDamage(WeaponOwner, Enemy), WeaponOwner->GetController(), this, DamageTypeClass);
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Enemy->HitParticles, Hit.ImpactPoint, FRotator(0.f), true);
		}
		else
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitWorldParticles, Hit.ImpactPoint, FRotator(0.f), true);
		}
		*/
	}
}

void AWeaponBase::AddBuff(ACharacterBase* MC)
{
	switch (BuffType)
	{
	case EBuffType::EBT_Agility:
		MC->StatsComponent->Agility += Agility;
		break;
	case EBuffType::EBT_Strength:
		MC->StatsComponent->Strength += Strength;
	}

}

void AWeaponBase::RemoveBuff(ACharacterBase* MC)
{
	switch (BuffType)
	{
	case EBuffType::EBT_Agility:
		MC->StatsComponent->Agility -= Agility;
		break;
	case EBuffType::EBT_Strength:
		MC->StatsComponent->Strength -= Strength;
	}
}

int32 AWeaponBase::CalculateDamage(ACharacterBase* MC, AEnemyBase* Enemy)
{
	/**
	//Formula = Battle Power + ((Level * Level * Attack) / 256) * 3 / 2
	int32 A = MC->CharacterStats.Strength; //Character's Strength
	int32 B = Enemy->EnemyStats.Defense; // Enemy's Defense
	int32 C = 8; //Some Constant
	int32 D = MC->CharacterStats.Strength2; //Characters Second Strength Stat
	int32 E = MC->CharacterStats.Agility; //Using this to substitute for battle power
	int32 F = MC->CharacterStats.Level; //Characters Level
	int32 G = MC->CharacterStats.Attack; //Characters Attack
	if (A > 128)
	{
		D = 255;
	}
	int32 Formula = E + ((F * F * G) / 256) * 3 / 2;
	*/

	//Damage = (Formula * (FMath::RandRange(968, 999) - B) / 256) + 1;

	return 0;
}

void AWeaponBase::AddToInventory(ACharacterBase* MC)
{
	MC->Inventory->AddWeapon(this);
}