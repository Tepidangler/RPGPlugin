#include "MagicBase.h"
#include "CharacterBase.h"
#include "EnemyBase.h"
#include "MagicSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AMagicBase::AMagicBase()
{
	Name = "Default Name";
	Cost = 0.f;
	CastTime = 0.f;
	BuffMultiplier = 1.f;
	DebuffMultiplier = 0.05f;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.f);
	RootComponent = CollisionComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->Bounciness = .05f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	
}

// Called when the game starts or when spawned
void AMagicBase::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentHit.AddDynamic(this, &AMagicBase::OnHit);
}

// Called every frame
void AMagicBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMagicBase::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
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

void AMagicBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		ACharacterBase* MC = Cast<ACharacterBase>(OtherActor);
		if (MC)
		{
			UGameplayStatics::ApplyDamage(MC, MC->MagicSystemComponent->CalculateMagicalDamage(Caster, MC, this), Instigator, this, DamageTypeClass);
			return;
		}

		AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
		if (Enemy)
		{
			UGameplayStatics::ApplyDamage(Enemy, Enemy->MagicComponent->CalculateMagicalDamage(Caster, Enemy, this), Instigator, this, DamageTypeClass);
			return;
		}
	}
}
