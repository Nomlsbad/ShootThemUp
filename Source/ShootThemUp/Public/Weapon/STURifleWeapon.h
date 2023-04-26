// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UAudioComponent;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
	
public:

	ASTURifleWeapon();
	
	virtual void StartFire() override;
	
    virtual void StopFire() override;

	virtual void Zoom(bool Enabled) override;
    
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FOVZoomAngle = 50.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName = "TraceTarget";
	
	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	UPROPERTY()
	UAudioComponent* FireAudioComponent;
	
	FTimerHandle ShotTimerHandle;

	float DefaultCameraFOV = 90.0f;

	void InitFX();
	
	void SetFXActive(bool IsActive);
	
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
};
