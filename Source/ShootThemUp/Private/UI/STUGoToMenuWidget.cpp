// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGoToMenuWidget.h"
#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGoToMenuWidget, All, All);

void USTUGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnGoToMenu);
	}
}

void USTUGoToMenuWidget::OnGoToMenu()
{
	if (!GetWorld()) return;

	const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!GameInstance) return;

	if (GameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogSTUGoToMenuWidget, Error, TEXT("Menu level name is none"));
		return;
	}

	UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelName());
}
