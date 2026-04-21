// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_InventorySlotRepTracker.h"
#include "Item/XInvU_ItemStack.h"
#include "XInvU_InventorySlot.generated.h"


/**
 * 
 */
USTRUCT()
struct XYLOINVENTORYUTIL_API FXInvU_InventorySlot
{
	GENERATED_BODY()

	UPROPERTY()
	FXInvU_ItemStack Stack;

	UPROPERTY(NotReplicated)
	FGameplayTagContainer CategoryFilter;
	
	UPROPERTY()
	FXInvU_InventorySlotRepTracker RepTracker;
};
