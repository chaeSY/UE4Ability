// Fill out your copyright notice in the Description page of Project Settings.


#include "SYAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "SYCharacter.h"

void USYAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ASYCharacter* TargetCharacter = nullptr;


	// Compute the delta between old and new, if it is available
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ASYCharacter>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		if (TargetCharacter)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Health: %f"), GetHealth()));
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Delta: %f"), DeltaValue));
			TargetCharacter->HandleChangedHealth(DeltaValue);
		}
	}
}
