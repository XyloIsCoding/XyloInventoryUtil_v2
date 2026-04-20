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
	FXInvU_ItemStack(const UXInvU_ItemDefinition* InItemDefinition, int32 InCount = 1);
	
public:
	void InitializeAs(const UXInvU_ItemDefinition* InItemDefinition, int32 InCount);

	const UXInvU_ItemDefinition* GetItemDefinition() const { return ItemDefinition; }
	
	int32 GetCount() const { return Count; }
	
	void SetCount(int32 NewCount);

	FXInvU_ItemFragmentData* FindFragmentDynamicData(FGameplayTag FragmentTag, const UScriptStruct* StructType);

	template<std::derived_from<FXInvU_ItemFragmentData> T>
	T* FindFragmentDynamicData(FGameplayTag FragmentTag) { return static_cast<T*>(FindFragmentDynamicData(FragmentTag, T::StaticStruct())); }

	const FXInvU_ItemFragmentData* FindFragmentDynamicData(FGameplayTag FragmentTag, const UScriptStruct* StructType) const;

	template<std::derived_from<FXInvU_ItemFragmentData> T>
	const T* FindFragmentDynamicData(FGameplayTag FragmentTag) const { return static_cast<T*>(FindFragmentDynamicData(FragmentTag, T::StaticStruct())); }
	
protected:
	UPROPERTY()
	TObjectPtr<const UXInvU_ItemDefinition> ItemDefinition = nullptr;

	UPROPERTY(BlueprintReadOnly)
	int32 Count = 0;

	UPROPERTY()
	TArray<FXInvU_ItemFragmentContainer> FragmentsDynamicData;
};
