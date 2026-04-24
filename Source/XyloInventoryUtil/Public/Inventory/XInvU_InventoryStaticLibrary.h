// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_Inventory.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XInvU_InventoryStaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class XYLOINVENTORYUTIL_API UXInvU_InventoryStaticLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static void DebugPrintInventory(const FXInvU_Inventory& Inventory);
	
	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static void CopyInventoryContent(UPARAM(ref) FXInvU_Inventory& Target, const FXInvU_Inventory& Source);

	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static bool GetStack(FXInvU_ItemStack& OutStack, const FXInvU_Inventory& Inventory, int32 SlotIndex);

	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static void SetStack(UPARAM(ref) FXInvU_Inventory& Inventory, int32 SlotIndex, const FXInvU_ItemStack& NewStack);

	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static int32 AddStack(UPARAM(ref) FXInvU_Inventory& Inventory, const FXInvU_ItemStack& NewStack, int32 CountOverride = 0);

	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static void RemoveStack(UPARAM(ref) FXInvU_Inventory& Inventory, int32 SlotIndex);

	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static int32 ConsumeItem(UPARAM(ref) FXInvU_Inventory& Inventory, UXInvU_ItemDefinition* ItemDefinition, int32 Count);
	
	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static bool GetSlotCategoryFilter(const FXInvU_Inventory& Inventory, int32 SlotIndex, FGameplayTagContainer& OutCategoryFilter);

	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static void SetSlotCategoryFilter(FXInvU_Inventory& Inventory, int32 SlotIndex, FGameplayTagContainer NewCategoryFilter);

	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static void GetChangedIndexes(const FXInvU_Inventory& Inventory, const FXInvU_Inventory& OldInventory, TArray<int32>& OutChangedIndexes);

	UFUNCTION(Category="InventoryStaticLibrary", BlueprintCallable)
	static void BroadcastChanges(FXInvU_Inventory& Inventory, const FXInvU_Inventory& OldInventory);
};
