// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"



UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	int32 TeamID;

	FLinearColor TeamColor;

	void AddKill() { ++KillsNum; }

	int32 GetKillsNum() const { return KillsNum; }
	
	void AddDeath() { ++DeathsNum; }

	int32 GetDeathNum() const { return DeathsNum; }

private:

	int32 KillsNum = 0;

	int32 DeathsNum = 0;
};
