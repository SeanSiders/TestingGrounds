// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "../Weapons/Gun.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
    
    CameraComponentFP = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    CameraComponentFP->SetupAttachment(GetCapsuleComponent());
    CameraComponentFP->RelativeLocation = FVector(-39.56f, 1.75f, 64.f);
    CameraComponentFP->bUsePawnControlRotation = true;
    
    FPArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonArms"));
    FPArms->SetOnlyOwnerSee(true);
    FPArms->SetupAttachment(CameraComponentFP);
    FPArms->bCastDynamicShadow = false;
    FPArms->CastShadow = false;
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
    
    if (GunBP == NULL)
    {
        UE_LOG(LogTemp, Warning, TEXT("BP_Gun not found"))
        return;
    }
    
    Gun = GetWorld()->SpawnActor<AGun>(GunBP);
	Gun->AttachToComponent(FPArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
    Gun->AnimInstance = FPArms->GetAnimInstance();
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::Fire);
}

void AMannequin::Fire()
{
    Gun->OnFire();
}

