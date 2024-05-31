// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// 初始化GameplayTags
	FAuraGameplayTags::InitializeNativeGameplayTags();

	// 使用 Target Data 必须的初始化步骤
	UAbilitySystemGlobals::Get().InitGlobalData();
}
