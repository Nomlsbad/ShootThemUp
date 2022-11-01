// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USTUWeaponComponent();

	virtual void StartFire();
	void StopFire();

	virtual void NextWeapon();
	
	void Reload();
	bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponClass, int32 ClipsAmount);

	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	int32 GetBulletsLeft() const;
	int32 GetClipsLeft() const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;
	
	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	bool CanFire() const;
	
	bool CanEquip() const;

	void EquipWeapon(int32 WeaponIndex);
	
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	bool bEquipAnimInProgress = false;
	
	bool bReloadAnimInProgress = false;

	void SpawnWeapons();

	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void PlayAnimMontage(UAnimMontage* Animation);
	
	void InitAnimation();
	
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
	
	bool CanReload() const;

	void OnClipEmpty();
	
	void ChangeClip();

	template <class T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;
	
		const auto NotifyEvents = Animation->Notifies;
		for (auto NotifyEvent : NotifyEvents)
		{
			if (auto AnimNotify = Cast<T>(NotifyEvent.Notify))
			{
				return AnimNotify;
			}
		}

		return  nullptr;
	}
};
