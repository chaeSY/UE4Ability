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

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
		UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			AActor* DamageCauser = Source->AbilityActorInfo->AvatarActor.Get();

			float DamageAmount = GetDamage();
			TargetCharacter->HandleDamage(DamageAmount, DamageCauser);

			float oldHealth = GetHealth();
			float resultHealth = FMath::Clamp(oldHealth - DamageAmount, 0.f, GetMaxHealth());
			float healthDelta = oldHealth - resultHealth;

			SetHealth(resultHealth);
			TargetCharacter->HandleChangedHealth(-healthDelta);

			SetDamage(0);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		if (TargetCharacter)
		{
			float resultHealth = FMath::Clamp(GetHealth(), 0.f, GetMaxHealth());
			float delta = GetHealth() - resultHealth;
			SetHealth(resultHealth);
			TargetCharacter->HandleChangedHealth(delta);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		if (TargetCharacter)
		{
			float resultStamina = FMath::Clamp(GetStamina(), 0.f, GetMaxStamina());
			float delta = GetStamina() - resultStamina;
			SetStamina(resultStamina);
			TargetCharacter->HandleChangedStamina(delta);
		}
	}
}
