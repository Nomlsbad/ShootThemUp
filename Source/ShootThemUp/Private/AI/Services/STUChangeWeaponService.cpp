// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/STUChangeWeaponService.h"

#include "AIController.h"
#include "Components/STUAIWeaponComponent.h"
#include "STUUtils.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller)
	{
		const auto WeaponComponent = STUUtils::GetPlayerComponent<USTUAIWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && !FMath::IsNearlyZero(Probability) && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
