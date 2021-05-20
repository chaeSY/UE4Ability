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
	// IAbilitySystemInterface�� GetAbilitySystemComponent ����� ������
	// AbilitySystemComponent�� Interface�� ����� ����� �� ����


	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	const class USYAttributeSet* AttributeSet;

	UFUNCTION(BlueprintPure)
	float GetHealth() const;
};
