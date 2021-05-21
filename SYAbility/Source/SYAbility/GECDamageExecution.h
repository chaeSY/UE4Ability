// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GECDamageExecution.generated.h"

/**
 * 
 */
UCLASS()
class SYABILITY_API UGECDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	

public:
	UGECDamageExecution();
	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;
};
