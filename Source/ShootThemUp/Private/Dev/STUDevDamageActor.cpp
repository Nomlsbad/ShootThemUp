// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/STUDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


ASTUDevDamageActor::ASTUDevDamageActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}


void ASTUDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(), Damage, GetActorLocation(), Radius, DamageTypeClass,
		{},this, nullptr, DoFullDamage);
	
}

