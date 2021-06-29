// Fill out your copyright notice in the Description page of Project Settings.


#include "SYCharacter.h"
#include "AbilitySystemComponent.h"
#include "SYAttributeSet.h"
#include "SYPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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

	// ability
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

void ASYCharacter::UpdateHUD() const
{
	ASYPlayerController* controller = GetController<ASYPlayerController>();
	if (!IsValid(controller))
		return;

	UUserWidget* hud = controller->GetHUD();
	if (!IsValid(hud))
		return;

	UUserWidget* HealthBar = Cast<UUserWidget>(hud->GetWidgetFromName(FName("WB_HealthBar")));
	if (IsValid(HealthBar))
	{
		UProgressBar* progressbar = Cast<UProgressBar>(HealthBar->GetWidgetFromName(FName("PB_HP")));
		if (IsValid(progressbar))
		{
			float percent = GetHealth() / GetMaxHealth();
			progressbar->SetPercent(percent);
		}

		UTextBlock* tb = Cast<UTextBlock>(HealthBar->GetWidgetFromName(FName("TB_HP")));
		if (IsValid(tb))
		{
			FString s = FString::Printf(TEXT("HP: %.0f / %.0f"), GetHealth(), GetMaxHealth());
			FText t = FText::FromString(s);
			tb->SetText(t);
		}
	}

}

float ASYCharacter::GetHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetHealth();
	}

	return -1.f;
}

float ASYCharacter::GetMaxHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMaxHealth();
	}

	return -1.f;
}

float ASYCharacter::GetStamina() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetStamina();
	}

	return -1.f;
}

float ASYCharacter::GetMaxStamina() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMaxStamina();
	}

	return -1.f;
}

void ASYCharacter::HandleChangedHealth(float DeltaHealth)
{
	if (OnChangedHealth.IsBound())
	{
		OnChangedHealth.Broadcast(DeltaHealth);
	}
}

void ASYCharacter::HandleChangedStamina(float DeltaStamina)
{
	if (OnChangedStamina.IsBound())
	{
		OnChangedStamina.Broadcast(DeltaStamina);
	}
}

void ASYCharacter::HandleDamage(float DamageAmount, AActor* DamageCauser)
{
	if (OnDamaged.IsBound())
	{
		OnDamaged.Broadcast(DamageAmount, DamageCauser);
	}
}

void ASYCharacter::InitAbility()
{
	for (int i =0; i<AbilityClasses.Num(); ++i)
	{
		GrantAbility(AbilityClasses[i], 1, i);
	}

	// apply passive gameplay effect
	for (TSubclassOf<UGameplayEffect> GEClass : PassiveAbilityEffects)
	{
		if (IsValid(AbilitySystemComponent))
		{
			UGameplayEffect* e = GEClass->GetDefaultObject<UGameplayEffect>();
			FGameplayEffectContextHandle h = AbilitySystemComponent->MakeEffectContext();
			if (e)
			{
				AbilitySystemComponent->ApplyGameplayEffectToSelf(e, 1, h);
			}
		}
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
