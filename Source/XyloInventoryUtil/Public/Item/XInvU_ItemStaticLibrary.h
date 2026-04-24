// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_ItemStack.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XInvU_ItemStaticLibrary.generated.h"

class UXInvU_ItemFragment;
class UXInvU_ItemFragmentDefinition;
class UXInvU_ItemDefinition;
class UXInvU_Item;

/**
 * 
 */
UCLASS(DisplayName="Item Static Library")
class XYLOINVENTORYUTIL_API UXInvU_ItemStaticLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static bool MakeItemStack(FXInvU_ItemStack& OutItemStack, const UXInvU_ItemDefinition* ItemDefinition, int32 Count);

	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static const UXInvU_ItemDefinition* GetItemDefinition(const FXInvU_ItemStack& ItemStack);

	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static bool GetItemCategories(FGameplayTagContainer& OutCategories, const FXInvU_ItemStack& ItemStack);

	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static const UXInvU_Item* GetItem(const FXInvU_ItemStack& ItemStack);

	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static int32 GetStackCount(const FXInvU_ItemStack& ItemStack);

	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static int32 GetStackMaxCount(const FXInvU_ItemStack& ItemStack);

	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static void SetStackCount(UPARAM(ref) FXInvU_ItemStack& ItemStack, int32 NewCount);
	
	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static const UXInvU_ItemFragmentDefinition* GetFragmentDefinition(const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag);

	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static const UXInvU_ItemFragment* GetFragment(const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag);
	
	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static bool GetFragmentData(TInstancedStruct<FXInvU_ItemFragmentData>& OutData, const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag, const UScriptStruct* StructType);

	UFUNCTION(Category="ItemStaticLibrary", BlueprintCallable)
	static bool SetFragmentDynamicData(UPARAM(ref) FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag, const TInstancedStruct<FXInvU_ItemFragmentData>& NewData);

	static const FXInvU_ItemFragmentData* FindFragmentData(const UXInvU_ItemDefinition* ItemDefinition, FGameplayTag FragmentTag, const UScriptStruct* StructType);

	template<std::derived_from<FXInvU_ItemFragmentData> T>
	static const T* FindFragmentData(const UXInvU_ItemDefinition* ItemDefinition, FGameplayTag FragmentTag) { return static_cast<const T*>(FindFragmentData(ItemDefinition, FragmentTag, T::StaticStruct())); }
	
	static const FXInvU_ItemFragmentData* FindFragmentData(const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag, const UScriptStruct* StructType);

	template<std::derived_from<FXInvU_ItemFragmentData> T>
	static const T* FindFragmentData(const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag) { return static_cast<const T*>(FindFragmentData(ItemStack, FragmentTag, T::StaticStruct())); }
};
