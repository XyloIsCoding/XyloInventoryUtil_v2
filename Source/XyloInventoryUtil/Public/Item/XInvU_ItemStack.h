// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Fragment/XInvU_ItemFragment.h"
#include "StructUtils/InstancedStruct.h"
#include "XInvU_ItemStack.generated.h"

class UXInvU_Item;
class UXInvU_ItemDefinition;

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

	const UXInvU_ItemDefinition* GetItemDefinition() const { return ItemDefinition.Get(); }
	const UXInvU_Item* GetItem() const;
	int32 GetCount() const { return Count; }
	
	const FXInvU_ItemFragment* FindFragment(const UScriptStruct* FragmentClass) const;

	template<std::derived_from<FXInvU_ItemFragment> T>
	const T* FindFragment() const { return static_cast<const T*>(FindFragment(T::StaticStruct())); }
	
protected:
	UPROPERTY()
	TWeakObjectPtr<UXInvU_ItemDefinition> ItemDefinition = nullptr;

	UPROPERTY(BlueprintReadOnly)
	int32 Count = 0;

	UPROPERTY()
	TArray<TInstancedStruct<FXInvU_ItemFragment>> DynamicFragments;
};
