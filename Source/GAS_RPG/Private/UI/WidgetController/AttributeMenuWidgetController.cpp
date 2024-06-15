// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\UI\WidgetController\AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo)

	for (auto& pair : AS->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(pair.Key);
		Info.AttributeValue = pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(pair.Value())
		                      .AddLambda([this,pair](const FOnAttributeChangeData& Data)
		                      {
			                      FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(pair.Key);
			                      Info.AttributeValue = Data.NewValue;
			                      AttributeInfoDelegate.Broadcast(Info);
		                      });
	}
}
