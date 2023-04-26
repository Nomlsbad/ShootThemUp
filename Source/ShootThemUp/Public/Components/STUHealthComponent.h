// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), BlueprintType, meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	USTUHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsHealthFull() const { return FMath::IsNearlyEqual(Health, MaxHealth); }
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealtPercent() const { return Health / MaxHealth; }

	float GetHealth() const { return Health; }

	bool TryToHeal(float RecoverableHealth);
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0"))
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Healing", meta = (ClampMin = "0.0"))
	bool bAutoHeal = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Healing", meta = (ClampMin = "0.0", EditCondition = "bAutoHeal"))
	float HealRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Healing", meta = (ClampMin = "0.0", EditCondition = "bAutoHeal"))
	float HealDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Healing", meta = (ClampMin = "0.0", EditCondition = "bAutoHeal"))
	float HealModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	TMap<UPhysicalMaterial*, float> DamageModifiers;
	
	virtual void BeginPlay() override;
	
private:

	FTimerHandle HealTimerHandle;
	
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent,
		FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser );

	UFUNCTION()
	void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo,
		class AController* InstigatedBy, AActor* DamageCauser );

	void ApplyDamage(float Damage, AController* InstigatedBy);
	
	void OnAutoHeal();

	void SetHealth(float NewHealth);

	void PlayCameraShake();

	void Killed(AController* KillerController);

	float GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName);

	void ReportDamage(float Damage, AController* InstigatedBy);
};
