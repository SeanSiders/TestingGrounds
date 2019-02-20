// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Projectiles/BallProjectile.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    // Create a gun mesh component
    Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
    Gun->bCastDynamicShadow = false;
    Gun->CastShadow = false;
    // Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
    Gun->SetupAttachment(RootComponent);
    
    MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    MuzzleLocation->SetupAttachment(Gun);
    MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
    
    // Default offset from the character location for projectiles to spawn
    GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}
void AGun::OnFire()
{
    // try and fire a projectile
    if (ProjectileClass != NULL)
    {
        UWorld* const World = GetWorld();
        if (World != NULL)
        {
            
            const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
                // MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
            const FVector SpawnLocation = MuzzleLocation->GetComponentLocation();
            
            //Set Spawn Collision Handling Override
            FActorSpawnParameters ActorSpawnParams;
            ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
                
            // spawn the projectile at the muzzle
            World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
        }
    }
    
    // try and play the sound if specified
    if (FireSound != NULL)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    }
    
    // try and play a firing animation if specified
    if (FireAnimation != NULL)
    {
        if (AnimInstance != NULL)
        {
            AnimInstance->Montage_Play(FireAnimation, 1.f);
        }
    }
}


