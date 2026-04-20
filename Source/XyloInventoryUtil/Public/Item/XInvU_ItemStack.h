// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Fragment/XInvU_ItemFragmentData.h"
#include "StructUtils/InstancedStruct.h"
#include "XInvU_ItemStack.generated.h"

class UXInvU_Item;
class UXInvU_ItemDefinition;

USTRUCT()
struct XYLOINVENTORYUTIL_API FXInvU_ItemFragmentContainer
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag FragmentTag;

	UPROPERTY()
	TInstancedStruct<FXInvU_ItemFragmentData> FragmentData;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct XYLOINVENTORYUTIL_API FXInvU_ItemStack
{
	GENERATED_BODY()

	FXInvU_ItemStack() {}
	FXInvU_ItemStack(UXInvU_ItemDefinition* InItemDefinition, int32 InCount = 1);
	
public:
	void InitializeAs(UXInvU_ItemDefinition* InItemDefinition, int32 InCount);

	const UXInvU_ItemDefinition* GetItemDefinition() const { return ItemDefinition; }
	
	const UXInvU_Item* GetItem() const;
	
	int32 GetCount() const { return Count; }
	
	void SetCount(int32 NewCount);

	FXInvU_ItemFragmentData* GetFragmentDynamicData(FGameplayTag FragmentTag, UStruct* StructType);

	template<std::derived_from<FXInvU_ItemFragmentData> T>
	T* GetFragmentDynamicData(FGameplayTag FragmentTag) { return GetFragmentDynamicData(FragmentTag, T::StaticStruct()); }

	const FXInvU_ItemFragmentData* GetFragmentDynamicData(FGameplayTag FragmentTag, UStruct* StructType) const;

	template<std::derived_from<FXInvU_ItemFragmentData> T>
	const T* GetFragmentDynamicData(FGameplayTag FragmentTag) const { return GetFragmentDynamicData(FragmentTag, T::StaticStruct()); }
	
protected:
	UPROPERTY()
	TObjectPtr<UXInvU_ItemDefinition> ItemDefinition = nullptr;

	UPROPERTY(BlueprintReadOnly)
	int32 Count = 0;

	UPROPERTY()
	TArray<FXInvU_ItemFragmentContainer> FragmentsDynamicData;
};
