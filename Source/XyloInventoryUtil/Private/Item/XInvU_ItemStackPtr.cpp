// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Item/XInvU_ItemStackPtr.h"

#include "Inventory/XInvU_Inventory.h"

FXInvU_ItemStack* FXInvU_ItemStackPtr::operator->()
{
	return OwningInventory->GetStackMutable(SlotIndex);
}

const FXInvU_ItemStack* FXInvU_ItemStackPtr::operator->() const
{
	return OwningInventory->GetStack(SlotIndex);
}

const FXInvU_ItemStack& FXInvU_ItemStackPtr::Get() const
{
	return *OwningInventory->GetStack(SlotIndex);
}

void FXInvU_ItemStackPtr::MarkStackPropertyDirty()
{
	FXInvU_InventorySlot& Slot = OwningInventory->Slots[SlotIndex];
	OwningInventory->MarkStackPropertyDirty(Slot, SlotIndex);
}

void FXInvU_ItemStackPtr::MarkStackDirty(const FXInvU_ItemStack& OldStack)
{
	FXInvU_InventorySlot& Slot = OwningInventory->Slots[SlotIndex];
	OwningInventory->MarkStackDirty(Slot, SlotIndex, OldStack);
}
