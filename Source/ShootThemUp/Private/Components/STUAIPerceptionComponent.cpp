// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return  nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PerceiveActor : PerceiveActors)
	{
		const auto HealthComponent = STUUtils::GetPlayerComponent<USTUHealthComponent>(PerceiveActor);

		const auto PerceivePawn = Cast<APawn>(PerceiveActor);
		const bool AreEnemies = PerceivePawn && STUUtils::AreEnemies(Controller, PerceivePawn->GetController());
		
		if (AreEnemies && HealthComponent && !HealthComponent->IsDead())
		{
			const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerceiveActor;
			}
		}
	}

	return  BestPawn;
}
