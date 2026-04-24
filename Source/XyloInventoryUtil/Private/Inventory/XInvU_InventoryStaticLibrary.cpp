// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Inventory/XInvU_InventoryStaticLibrary.h"

void UXInvU_InventoryStaticLibrary::DebugPrintInventory(const FXInvU_Inventory& Inventory)
{
	Inventory.DebugPrintInventory();
}

void UXInvU_InventoryStaticLibrary::CopyInventoryContent(FXInvU_Inventory& Target, const FXInvU_Inventory& Source)
{
	Target.CopyInventoryContent(Source);
}

bool UXInvU_InventoryStaticLibrary::GetStack(FXInvU_ItemStack& OutStack, const FXInvU_Inventory& Inventory, int32 SlotIndex)
{
	if (const FXInvU_ItemStack* FoundStack = Inventory.GetStack(SlotIndex))
	{
		OutStack = *FoundStack;
		return true;
	}
	return false;
}

void UXInvU_InventoryStaticLibrary::SetStack(FXInvU_Inventory& Inventory, int32 SlotIndex, const FXInvU_ItemStack& NewStack)
{
	Inventory.SetStack(SlotIndex, NewStack);
}

int32 UXInvU_InventoryStaticLibrary::AddStack(FXInvU_Inventory& Inventory, const FXInvU_ItemStack& NewStack, int32 CountOverride)
{
	return Inventory.AddStack(NewStack, CountOverride);
}

void UXInvU_InventoryStaticLibrary::RemoveStack(FXInvU_Inventory& Inventory, int32 SlotIndex)
{
	Inventory.RemoveStack(SlotIndex);
}

int32 UXInvU_InventoryStaticLibrary::ConsumeItem(FXInvU_Inventory& Inventory, UXInvU_ItemDefinition* ItemDefinition, int32 Count)
{
	return Inventory.ConsumeItem(ItemDefinition, Count);
}

bool UXInvU_InventoryStaticLibrary::GetSlotCategoryFilter(const FXInvU_Inventory& Inventory, int32 SlotIndex, FGameplayTagContainer& OutCategoryFilter)
{
	return Inventory.GetSlotCategoryFilter(SlotIndex, OutCategoryFilter);
}

void UXInvU_InventoryStaticLibrary::SetSlotCategoryFilter(FXInvU_Inventory& Inventory, int32 SlotIndex, FGameplayTagContainer NewCategoryFilter)
{
	Inventory.SetSlotCategoryFilter(SlotIndex, NewCategoryFilter);
}

void UXInvU_InventoryStaticLibrary::GetChangedIndexes(const FXInvU_Inventory& Inventory, const FXInvU_Inventory& OldInventory, TArray<int32>& OutChangedIndexes)
{
	Inventory.GetChangedIndexes(OldInventory, OutChangedIndexes);
}

void UXInvU_InventoryStaticLibrary::BroadcastChanges(FXInvU_Inventory& Inventory, const FXInvU_Inventory& OldInventory)
{
	Inventory.BroadcastChanges(OldInventory);
}
