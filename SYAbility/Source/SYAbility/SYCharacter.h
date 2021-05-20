// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "SYCharacter.generated.h"

class UAbilitySystemComponent;

UCLASS()
class SYABILITY_API ASYCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASYCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const; 
	// IAbilitySystemInterface는 GetAbilitySystemComponent 상속을 강제함
	// AbilitySystemComponent로 Interface의 기능을 사용할 수 있음


	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	const class USYAttributeSet* AttributeSet;

	UFUNCTION(BlueprintPure)
	float GetHealth() const;
};
