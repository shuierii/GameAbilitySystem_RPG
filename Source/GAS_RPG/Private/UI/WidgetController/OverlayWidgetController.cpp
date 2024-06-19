// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	const UAuraAttributeSet* AuraAS = GetAuraAS();

	// 初始化时的进度条百分比变化
	OnHealthChanged.Broadcast(AuraAS->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAS->GetMana());
	OnMaxManaChanged.Broadcast(AuraAS->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	UAuraAttributeSet* AuraAS = GetAuraAS();
	AAuraPlayerState* AuraPS = GetAuraPS();
	UAuraAbilitySystemComponent* AuraASC = GetAuraASC();
	
	AuraPS->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	AuraPS->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel, bool bLevelUp)
		{
			OnPlayerLevelChangedDelegate.Broadcast(NewLevel, bLevelUp);
		}
	);

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
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute())
	                      .AddLambda([this](const FOnAttributeChangeData& Data)
	                      {
		                      OnHealthChanged.Broadcast(Data.NewValue);
	                      });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute())
	                      .AddLambda([this](const FOnAttributeChangeData& Data)
	                      {
		                      OnMaxHealthChanged.Broadcast(Data.NewValue);
	                      });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetManaAttribute())
	                      .AddLambda([this](const FOnAttributeChangeData& Data)
	                      {
		                      OnManaChanged.Broadcast(Data.NewValue);
	                      });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxManaAttribute())
	                      .AddLambda([this](const FOnAttributeChangeData& Data)
	                      {
		                      OnMaxManaChanged.Broadcast(Data.NewValue);
	                      });

	if (AuraASC)
	{
		AuraASC->AbilityEquipped.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);
		if (AuraASC->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else
		{
			AuraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}

		AuraASC->EffectAssetTags.AddLambda(
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
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	const ULevelUpInfo* LevelUpInfo = GetAuraPS()->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unabled to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}

void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot) const
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	FAuraAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PreviousSlot;
	LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;
	// Broadcast empty info if PreviousSlot is a valid slot. Only if equipping an already-equipped spell
	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = Slot;
	AbilityInfoDelegate.Broadcast(Info);
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
