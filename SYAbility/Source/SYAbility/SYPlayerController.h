// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SYPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SYABILITY_API ASYPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* aPawn) override;

	UUserWidget* GetHUD() { return HUDWidget; }

private:
	void InitHUD(APawn* Pawn);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* HUDWidget;

	bool bInitHUD = false;
};
