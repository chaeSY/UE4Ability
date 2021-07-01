// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SYGameplayAbilityBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGameplayEffectSpecGroup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAbilityTargetDataHandle TargetDataHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayEffectSpecHandle SpecHandle;
};


UCLASS()
class SYABILITY_API USYGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "SYAbility", BlueprintCallable)
	FGameplayEffectSpecGroup CreateGameplayEffectSpecGroup(const FGameplayEventData& EventData);

	UFUNCTION(Category = "SYAbility", BlueprintCallable)
	void ApplyGameplayEffectToTargetFromEventData(const FGameplayEventData& EventData);


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
};
