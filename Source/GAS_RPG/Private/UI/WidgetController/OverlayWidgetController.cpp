// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
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

	// 第一种绑定委托方式，AuraAttributeSet->GetHealthAttribute() 在GET/SET宏定义上
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
	//                       .AddUObject(this, &UOverlayWidgetController::HealthChanged);
	//
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
	//                       .AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	//
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
	//                       .AddUObject(this, &UOverlayWidgetController::ManaChanged);
	//
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
	//                       .AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	// 第二种绑定委托方式，匿名函数
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
	                      .AddLambda([this](const FOnAttributeChangeData& Data)
	                      {
		                      OnHealthChanged.Broadcast(Data.NewValue);
	                      });
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
	                      .AddLambda([this](const FOnAttributeChangeData& Data)
	                      {
		                      OnMaxHealthChanged.Broadcast(Data.NewValue);
	                      });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
	                      .AddLambda([this](const FOnAttributeChangeData& Data)
	                      {
		                      OnManaChanged.Broadcast(Data.NewValue);
	                      });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
	                      .AddLambda([this](const FOnAttributeChangeData& Data)
	                      {
		                      OnMaxManaChanged.Broadcast(Data.NewValue);
	                      });
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		/* lambda里面不能调用成员函数，需要在[]中捕获对象才能调用 */
		[this](const FGameplayTagContainer& AssetTagsContainer)
		{
			for (const FGameplayTag& Tag : AssetTagsContainer)
			{
				// "A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
				// 检查是否属于 message 的子标签
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (!Tag.MatchesTag(MessageTag)) continue;

				// const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				// GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);

				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		});
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
