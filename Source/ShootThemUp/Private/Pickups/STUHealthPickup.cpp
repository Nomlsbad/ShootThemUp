// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/STUHealthPickup.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"


bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;

	return HealthComponent->TryToHeal(RecoverableHealth);
}
