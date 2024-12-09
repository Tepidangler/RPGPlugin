#include "WeaponBase.h"
#include "CharacterBase.h"
#include "EnemyBase.h"
#include "InventoryComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	//SkeletalMesh->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepWorldTransform);

	Attack = 1.f;

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
		
		AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
		if (Enemy)
		{
			check(WeaponOwner);
			UGameplayStatics::ApplyDamage(Enemy, WeaponOwner->CalculatePhysicalDamage(), WeaponOwner->GetController(), this, DamageTypeClass);
		//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Enemy->HitParticles, Hit.ImpactPoint, FRotator(0.f), true);
		}
		else
		{
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitWorldParticles, Hit.ImpactPoint, FRotator(0.f), true);
		}
		
	}
}



void AWeaponBase::AddToInventory(ACharacterBase* MC)
{
	MC->Inventory->AddWeapon(this);
}