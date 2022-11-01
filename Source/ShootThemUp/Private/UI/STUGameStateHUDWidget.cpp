// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameStateHUDWidget.h"
#include "GameModes/STUGameModeBase.h"

bool USTUGameStateHUDWidget::GetRoundTimeLeft(int32& TimeLeft) const
{
	if (!GetWorld()) return false;

	const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	TimeLeft = GameMode->GetRoundTimeLeft();
	
	return true;
}

bool USTUGameStateHUDWidget::GetRoundsInfo(int32& Rounds, int32& CurrentRound) const
{
	if (!GetWorld()) return false;

	const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	GameMode->GetRoundsInfo(Rounds, CurrentRound);
	
	return true;
}


