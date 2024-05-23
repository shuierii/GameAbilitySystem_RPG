// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters//AuraCharacterBase.h"

#include "AbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacterBase::InitializeMainAttributes() const
{
	const FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent.Get()->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent.Get()->MakeOutgoingSpec(DefaultMainAttributes, 1.0f, EffectContextHandle);
	AbilitySystemComponent.Get()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), AbilitySystemComponent);
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}
