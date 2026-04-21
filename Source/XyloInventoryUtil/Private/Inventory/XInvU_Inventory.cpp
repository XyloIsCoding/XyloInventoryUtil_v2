// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Inventory/XInvU_Inventory.h"

#include "XyloInventoryUtil.h"
#include "Item/XInvU_ItemDefinition.h"
#include "Item/XInvU_ItemStaticLibrary.h"

void FXInvU_Inventory::CopyInventoryContent(const FXInvU_Inventory& Source)
{
	Slots = Source.Slots;
}

const FXInvU_ItemStack* FXInvU_Inventory::GetStack(int32 SlotIndex) const
{
	return Slots.IsValidIndex(SlotIndex) ? &Slots[SlotIndex].Stack : nullptr;
}

void FXInvU_Inventory::SetStack(int32 SlotIndex, const FXInvU_ItemStack& NewStack)
{
	if (!Slots.IsValidIndex(SlotIndex))
	{
		return;
	}

	FXInvU_InventorySlot& Slot = Slots[SlotIndex];
	if (IsStackCompatibleWithSlot(Slot, NewStack))
	{
		Slot.Stack = NewStack;
		MarkStackDirty(Slot);
	}
}

int32 FXInvU_Inventory::AddStack(const FXInvU_ItemStack& NewStack, int32 CountOverride)
{
	int32 CountLeftToAdd = CountOverride > 0 ? CountOverride : NewStack.GetCount();

	// Return if we cannot add anything.
	if (!IsValid(NewStack.GetItemDefinition()) || CountLeftToAdd <= 0)
	{
		return 0;
	}
	
	const int32 MaxCountPerStack = UXInvU_ItemStaticLibrary::GetStackMaxCount(NewStack);

	// Try to add count to existing stacks.
	for (FXInvU_InventorySlot& Slot : Slots)
	{
		if (Slot.Stack.GetItemDefinition() == NewStack.GetItemDefinition())
		{
			const int32 InvStackCount = Slot.Stack.GetCount();
			const int32 SpaceLeft = FMath::Max(MaxCountPerStack - InvStackCount, 0.f);
			if (SpaceLeft > 0)
			{
				const int32 CountToAdd = FMath::Min(SpaceLeft, CountLeftToAdd);
				
				Slot.Stack.SetCount(InvStackCount + CountToAdd);
				MarkStackPropertyDirty(Slot);

				CountLeftToAdd -= CountToAdd;
				if (CountLeftToAdd <= 0)
				{
					return CountLeftToAdd;
				}
			}
		}
	}

	// Start creating new stacks.
	for (FXInvU_InventorySlot& Slot : Slots)
	{
		bool bSlotEmpty = !IsValid(Slot.Stack.GetItemDefinition()) || Slot.Stack.GetCount() == 0;
		bool bSlotCompatible = IsStackCompatibleWithSlot(Slot, NewStack);
		if (bSlotEmpty && bSlotCompatible)
		{
			Slot.Stack = NewStack;
			Slot.Stack.SetCount(FMath::Min(MaxCountPerStack, CountLeftToAdd));
			MarkStackDirty(Slot);

			CountLeftToAdd -= Slot.Stack.GetCount();
			if (CountLeftToAdd <= 0)
			{
				return CountLeftToAdd;
			}
		}
	}

	return CountLeftToAdd;
}

void FXInvU_Inventory::RemoveStack(int32 SlotIndex)
{
	if (!Slots.IsValidIndex(SlotIndex))
	{
		return;
	}

	FXInvU_InventorySlot& Slot = Slots[SlotIndex];
	Slot.Stack = FXInvU_ItemStack();
	MarkStackDirty(Slot);
}

int32 FXInvU_Inventory::ConsumeItem(UXInvU_ItemDefinition* ItemDefinition, int32 Count)
{
	if (!IsValid(ItemDefinition))
	{
		return 0;
	}

	int32 ConsumedCount = 0;

	for (FXInvU_InventorySlot& Slot : Slots)
	{
		if (Slot.Stack.GetItemDefinition() == ItemDefinition)
		{
			const int32 InvStackCount = Slot.Stack.GetCount();
			if (InvStackCount > 0)
			{
				const int32 CountToConsume = FMath::Min(Count, InvStackCount);
				
				Slot.Stack.SetCount(InvStackCount - CountToConsume);
				MarkStackPropertyDirty(Slot);

				ConsumedCount += CountToConsume;
				if (ConsumedCount >= Count)
				{
					return ConsumedCount;
				}
			}
		}
	}

	return ConsumedCount;
}

void FXInvU_Inventory::GetChangedIndexes(const FXInvU_Inventory& OldInventory, TArray<int32>& OutChangedIndexes) const
{
	for (int32 SlotIndex = 0; SlotIndex < Slots.Num(); ++SlotIndex)
	{
		const FXInvU_InventorySlot& Slot = Slots[SlotIndex];
		const FXInvU_InventorySlot& OldSlot = OldInventory.Slots[SlotIndex];
		if (Slot.RepTracker.StackID != OldSlot.RepTracker.StackID || Slot.RepTracker.ChangeID != OldSlot.RepTracker.ChangeID)
		{
			OutChangedIndexes.Add(SlotIndex);
		}
	}
}

void FXInvU_Inventory::MarkStackPropertyDirty(FXInvU_InventorySlot& Slot)
{
	Slot.RepTracker.MarkStackPropertyDirty();
}

void FXInvU_Inventory::MarkStackDirty(FXInvU_InventorySlot& Slot)
{
	Slot.RepTracker.MarkStackDirty();
}

void FXInvU_Inventory::DebugPrintInventory() const
{
	for (auto It = Slots.CreateConstIterator(); It; ++It)
	{
		const FXInvU_ItemStack& Stack = It->Stack;
		if (IsValid(Stack.GetItemDefinition()) && Stack.GetCount() > 0)
		{
			FString ItemName = Stack.GetItemDefinition()->GetItemName().ToString();
			UE_LOG(LogXyloInventoryUtil, Warning, TEXT("Slot %i: %s (%i)"), It.GetIndex(), *ItemName, Stack.GetCount())
		}
	}
}

FGameplayTagContainer& FXInvU_Inventory::GetSlotCategoryFilterRef(int32 SlotIndex)
{
	check(Slots.IsValidIndex(SlotIndex))
	
	FXInvU_InventorySlot& Slot = Slots[SlotIndex];
	return Slot.CategoryFilter;
}

bool FXInvU_Inventory::GetSlotCategoryFilter(int32 SlotIndex, FGameplayTagContainer& OutCategoryFilter) const
{
	if (!Slots.IsValidIndex(SlotIndex))
	{
		return false;
	}

	const FXInvU_InventorySlot& Slot = Slots[SlotIndex];
	OutCategoryFilter = Slot.CategoryFilter;
	return true;
}

void FXInvU_Inventory::SetSlotCategoryFilter(int32 SlotIndex, FGameplayTagContainer NewCategoryFilter)
{
	if (!Slots.IsValidIndex(SlotIndex))
	{
		return;
	}

	FXInvU_InventorySlot& Slot = Slots[SlotIndex];
	Slot.CategoryFilter = NewCategoryFilter;
}

bool FXInvU_Inventory::IsStackCompatibleWithSlot(const FXInvU_InventorySlot& Slot, const FXInvU_ItemStack& NewStack) const
{
	// Empty stack is always compatible
	if (!IsValid(NewStack.GetItemDefinition()))
	{
		return true;
	}

	// Compatible if no category filter or at least one match
	return Slot.CategoryFilter.IsEmpty() || Slot.CategoryFilter.HasAnyExact(NewStack.GetItemDefinition()->GetItemCategories());
}
