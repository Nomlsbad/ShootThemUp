// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class USTUHealthComponent;
class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	virtual void Tick(float DeltaTime) override;

	void SetPlayerColor(const FLinearColor& Color);
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USTUWeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (UIMin = "1.0"))
	float RunningSpeedMultiplier = 1.2;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
	float LifeSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Landed")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.f);

	UPROPERTY(EditDefaultsOnly, Category = "Landed")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialColorName = "Paint Color";

	virtual void BeginPlay() override;

	virtual void OnDeath();

	virtual void OnHealthChanged(float Health, float HealthDelta);

private:
	
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);

	void SpawnWeapon();
};
