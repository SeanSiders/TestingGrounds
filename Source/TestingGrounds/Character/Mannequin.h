// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

class AGun;

UCLASS()
class TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AGun> GunBP;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    

private:
    
    UPROPERTY(EditDefaultsOnly, Category = "Mesh")
    class USkeletalMeshComponent* FPArms;
    
    UPROPERTY(EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* CameraComponentFP;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    AGun* Gun;
    
    void Fire();
    void StopFire();
};
