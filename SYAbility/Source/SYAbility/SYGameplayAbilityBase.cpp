// Fill out your copyright notice in the Description page of Project Settings.


#include "SYGameplayAbilityBase.h"
#include "Abilities/GameplayAbilityTargetTypes.h"


FGameplayEffectSpecGroup USYGameplayAbilityBase::CreateGameplayEffectSpecGroup(const FGameplayEventData& EventData)
{
	FGameplayEffectSpecGroup RetSpecGroup;

	FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
	NewData->TargetActorArray.Add(const_cast<AActor*>(EventData.Target));
	RetSpecGroup.TargetDataHandle.Add(NewData);


	if (GameplayEffectClass)
	{
		RetSpecGroup.SpecHandle = MakeOutgoingGameplayEffectSpec(GameplayEffectClass, 1);
	}
		
	return RetSpecGroup;
}

void USYGameplayAbilityBase::ApplyGameplayEffectToTargetFromEventData(const FGameplayEventData& EventData)
{
	if (GameplayEffectClass && EventData.Target)
	{
		// make effect spec handle
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(GameplayEffectClass, 1);

		// make target data handle
		FGameplayAbilityTargetDataHandle TargetDataHandle;
		FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
		NewData->TargetActorArray.Add(const_cast<AActor*>(EventData.Target));
		TargetDataHandle.Add(NewData);

		ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle, TargetDataHandle);
	}
}
