// Fill out your copyright notice in the Description page of Project Settings.


#include "SYAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

void USYAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		ChangedHealthEvent.Broadcast();
	}
}
