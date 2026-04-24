// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_ItemStackPtr.generated.h"

struct FXInvU_ItemStack;
struct FXInvU_Inventory;

/**
 * 
 */
USTRUCT()
struct XYLOINVENTORYUTIL_API FXInvU_ItemStackPtr
{
	GENERATED_BODY()

	FXInvU_ItemStackPtr() : SlotIndex(0), OwningInventory(nullptr) {}

	FXInvU_ItemStackPtr(FXInvU_Inventory& Inventory, int32 Slot) : SlotIndex(Slot), OwningInventory(&Inventory) {}

	FXInvU_ItemStack* operator->();
	
	const FXInvU_ItemStack* operator->() const;

	const FXInvU_ItemStack& Get() const;

	void MarkStackPropertyDirty();
	void MarkStackDirty(const FXInvU_ItemStack& OldStack);
	
	int32 SlotIndex;
	
	FXInvU_Inventory* OwningInventory;
};
