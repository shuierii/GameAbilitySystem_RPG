// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BB_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BB_AuraHUD"));

	// 显示
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	// 设置controller参数
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// 控件绑定controller
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	// 显示到视口
	Widget->AddToViewport();
}

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		// 创建UI控制器
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		// 设置UI控制器参数
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		// UI控制器注册委托
		OverlayWidgetController->BindCallbacksToDependcies();

		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		// 创建UI控制器
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		// 设置UI控制器参数
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		// UI控制器注册委托
		AttributeMenuWidgetController->BindCallbacksToDependcies();

		return AttributeMenuWidgetController;
	}

	return AttributeMenuWidgetController;
}
