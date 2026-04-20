// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_InventorySlot.h"
#include "Item/XInvU_ItemStack.h"
#include "UObject/Object.h"
#include "XInvU_Inventory.generated.h"

/**
 * 
 */
USTRUCT()
struct XYLOINVENTORYUTIL_API FXInvU_Inventory
{
	GENERATED_BODY()

	FXInvU_Inventory() {}
	
	FXInvU_Inventory(int32 Size)
	{
		Slots.SetNum(Size);
	}
	
	virtual ~FXInvU_Inventory() {}

	virtual const FXInvU_ItemStack* GetStack(int32 SlotIndex) const;
	
	virtual void SetStack(int32 SlotIndex, const FXInvU_ItemStack& NewStack);

	virtual int32 AddStack(const FXInvU_ItemStack& NewStack, int32 CountOverride = 0);

	virtual void RemoveStack(int32 SlotIndex);

	virtual int32 ConsumeItem(UXInvU_ItemDefinition* ItemDefinition, int32 Count);

	virtual void GetChangedIndexes(const FXInvU_Inventory& OldInventory, TArray<int32>& OutChangedIndexes);
	
protected:
	UPROPERTY()
	TArray<FXInvU_InventorySlot> Slots;
};
