// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SYAttributeSet.generated.h"

/**
 * 
 */

DECLARE_EVENT(USYAttributeSet, FAttributeChangedEvent);

UCLASS()
class SYABILITY_API USYAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USYAttributeSet, Health);

	const FAttributeChangedEvent& OnChangedHealth() const { return ChangedHealthEvent; }
	FAttributeChangedEvent ChangedHealthEvent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Damage;
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Damage);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Damage);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Damage);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USYAttributeSet, Damage);

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data);
};
