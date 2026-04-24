// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Inventory/XInvU_InventorySlotRepTracker.h"


void FXInvU_InventorySlotRepTracker::MarkStackPropertyDirty()
{
	if (!bStackPropertyChanged)
	{
		ChangeID += 1;
		bStackPropertyChanged = true;
	}
}

void FXInvU_InventorySlotRepTracker::MarkStackDirty()
{
	if (!bStackChanged)
	{
		StackID += 1;
		ChangeID = 0;
		bStackChanged = true;
		bStackPropertyChanged = true;
	}
}

bool FXInvU_InventorySlotRepTracker::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	bStackChanged = false;
	bStackPropertyChanged = false;
	
	Ar.SerializeBits(&StackID, 8);
	Ar.SerializeBits(&ChangeID, 8);
	return true;
}