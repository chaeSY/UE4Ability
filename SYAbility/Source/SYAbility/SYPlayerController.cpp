// Fill out your copyright notice in the Description page of Project Settings.


#include "SYPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "SYCharacter.h"

void ASYPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	//InitHUD(aPawn);
}

void ASYPlayerController::InitHUD(APawn* InPawn)
{
	if (bInitHUD)
		return;

	bInitHUD = true;

	if (IsValid(HUDWidgetClass))
	{
		HUDWidget = CreateWidget<UUserWidget>(this, HUDWidgetClass, FName("HUDWidget"));
		
		if (IsValid(HUDWidget))
		{
			HUDWidget->AddToViewport();
		}		
	}
}
