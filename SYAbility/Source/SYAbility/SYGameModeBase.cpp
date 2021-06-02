// Fill out your copyright notice in the Description page of Project Settings.


#include "SYGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

ASYGameModeBase::ASYGameModeBase()
{

}

void ASYGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(SYHUDClass))
	{
		SYHUD = CreateWidget<UUserWidget>(GetWorld(), SYHUDClass, TEXT("SYHUD"));
		SYHUD->AddToViewport();
	}

	UUserWidget* HealthBar = Cast<UUserWidget>(SYHUD->GetWidgetFromName(FName("WB_HealthBar")));
	if (IsValid(HealthBar))
	{
		UProgressBar* progressbar = Cast<UProgressBar>(SYHUD->GetWidgetFromName(FName("PB_HP")));
		if (IsValid(progressbar))
		{
			progressbar->SetPercent(0.f);
		}

		UTextBlock* text = Cast<UTextBlock>(SYHUD->GetWidgetFromName(FName("TB_HP")));
		if (IsValid(text))
		{
			//FString txt = TEXT("Test");
			//text->SetText(txt);
		}
	}
}
