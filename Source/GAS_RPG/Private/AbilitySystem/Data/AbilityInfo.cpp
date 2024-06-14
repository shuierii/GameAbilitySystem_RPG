// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AbilityInfo.h"

#include "GAS_RPG/LogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (auto Info : AbilityInformation)
	{
		if (Info.AbilityTag.MatchesTagExact(AbilityTag))
		{
			return Info;
		}
	}

	// if (bLogNotFound)
	// {
	// 	UE_LOG(LogAura, Error, TEXT("FindAbilityInfoForTag failed!"));
	// }

	return FAuraAbilityInfo();
}
