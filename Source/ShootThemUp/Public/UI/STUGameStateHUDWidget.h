// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameStateHUDWidget.generated.h"


struct FGameData;

UCLASS()
class SHOOTTHEMUP_API USTUGameStateHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetRoundTimeLeft(int32& TimeLeft) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetRoundsInfo(int32& Rounds, int32& CurrentRound) const;
};
