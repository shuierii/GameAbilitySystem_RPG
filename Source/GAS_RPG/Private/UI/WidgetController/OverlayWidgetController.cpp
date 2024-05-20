// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// 初始化时的进度条百分比变化
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependcies()
{
	Super::BindCallbacksToDependcies();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// AuraAttributeSet->GetHealthAttribute() 在GET/SET宏定义上
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
