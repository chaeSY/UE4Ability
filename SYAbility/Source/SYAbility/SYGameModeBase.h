// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SYGameModeBase.generated.h"

/**
 * 
 */

class UUserWidget;

UCLASS()
class SYABILITY_API ASYGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASYGameModeBase();
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> SYHUDClass;
	
	UPROPERTY()
	UUserWidget* SYHUD;
};
