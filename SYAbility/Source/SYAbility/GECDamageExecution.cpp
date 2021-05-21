// Fill out your copyright notice in the Description page of Project Settings.


#include "GECDamageExecution.h"
#include "SYAttributeSet.h"
#include "AbilitySystemComponent.h"

struct FDamageStatics
{
	/* DECLARE_ATTRIBUTE_CAPTUREDEF(P);
	 * FProperty* P##Property; \
	 * FGameplayEffectAttributeCaptureDefinition P##Def; \
	 */

	//DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);
	FProperty* DamageProperty;
	FGameplayEffectAttributeCaptureDefinition DamageDef;

	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);


	FDamageStatics()
	{
		/* DEFINE_ATTRIBUTE_CAPTUREDEF(S, P, T, B);
		 * P##Property = FindFieldChecked<FProperty>(S::StaticClass(), GET_MEMBER_NAME_CHECKED(S, P)); \
		 * P##Def = FGameplayEffectAttributeCaptureDefinition(P##Property, EGameplayEffectAttributeCaptureSource::T, B); \
		 */

		// source
		//DEFINE_ATTRIBUTE_CAPTUREDEF(USYAttributeSet, Damage, Source, true);
		DamageProperty = FindFieldChecked<FProperty>(USYAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(USYAttributeSet, Damage));
		DamageDef = FGameplayEffectAttributeCaptureDefinition(DamageProperty, EGameplayEffectAttributeCaptureSource::Source, true);

		// target
		DEFINE_ATTRIBUTE_CAPTUREDEF(USYAttributeSet, Health, Target, false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics instance;
	return instance;
}


UGECDamageExecution::UGECDamageExecution()
{
	//capture

	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void UGECDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// todo: FAggregatorEvaluateParameters 생성하는 부분 따로 함수로 빼는 작업
	UAbilitySystemComponent* SourceAbilityComponent = ExecutionParams.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceAbilityComponent ? SourceAbilityComponent->GetAvatarActor() : nullptr;

	UAbilitySystemComponent* TargetAbilityComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* TargetActor = TargetAbilityComponent ? TargetAbilityComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// capturing
	float Damage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, Damage);

	// execute
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -Damage));
}
