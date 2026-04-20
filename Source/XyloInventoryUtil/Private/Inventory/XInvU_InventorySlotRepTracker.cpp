// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Inventory/XInvU_InventorySlotRepTracker.h"


void FXInvU_InventorySlotRepTracker::MarkStackPropertyDirty()
{
	if (!bStackDirty)
	{
		StackID += 1;
		bStackDirty = true;
	}
}

void FXInvU_InventorySlotRepTracker::MarkStackDirty()
{
	if (!bStackChanged)
	{
		ChangeID += 1;
		StackID = 0;
		bStackChanged = true;
		bStackDirty = true;
	}
}

bool FXInvU_InventorySlotRepTracker::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	Ar.SerializeBits(&StackID, 8);
	Ar.SerializeBits(&ChangeID, 8);
	return true;
}