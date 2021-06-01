// Fill out your copyright notice in the Description page of Project Settings.


#include "SYCharacter.h"
#include "AbilitySystemComponent.h"
#include "SYAttributeSet.h"

// Sets default values
ASYCharacter::ASYCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// ability system component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
}

// Called when the game starts or when spawned
void ASYCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AbilitySystemComponent))
	{
		AttributeSet = AbilitySystemComponent->GetSet<USYAttributeSet>();
	}

	InitAbility();
}

// Called every frame
void ASYCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->ClearOnScreenDebugMessages();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%f"), GetHealth()));
}

// Called to bind functionality to input
void ASYCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ASYCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float ASYCharacter::GetHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetHealth();
	}

	return -1.f;
}

void ASYCharacter::InitAbility()
{
	for (int i =0; i<AbilityClasses.Num(); ++i)
	{
		GrantAbility(AbilityClasses[i], 1, i);
	}
}

void ASYCharacter::GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode)
{
	if (IsValid(AbilitySystemComponent) && IsValid(AbilityClass))
	{
		UGameplayAbility* Ability = AbilityClass->GetDefaultObject<UGameplayAbility>();

		if (IsValid(Ability))
		{
			FGameplayAbilitySpec Spec(Ability, Level, InputCode);
			AbilitySystemComponent->GiveAbility(Spec);
		}
	}
}

void ASYCharacter::CancelAbility()
{
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->CancelAllAbilities();
	}

}
