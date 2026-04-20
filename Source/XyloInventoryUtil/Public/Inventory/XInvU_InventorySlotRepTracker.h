// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_InventorySlotRepTracker.generated.h"


/**
 * 
 */
USTRUCT()
struct XYLOINVENTORYUTIL_API FXInvU_InventorySlotRepTracker
{
	GENERATED_BODY()

	/** Call when properties on the stack changed. */
	void MarkStackPropertyDirty();

	/** Call when the stack itself got changed in its entirety. */
	void MarkStackDirty();

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	UPROPERTY()
	uint8 StackID = 0;
	
	UPROPERTY()
	uint8 ChangeID = 0;

protected:
	UPROPERTY()
	bool bStackDirty = false;

	UPROPERTY()
	bool bStackChanged = false;
};

template<>
struct TStructOpsTypeTraits<FXInvU_InventorySlotRepTracker> : public TStructOpsTypeTraitsBase2<FXInvU_InventorySlotRepTracker>
{
	enum 
	{
		WithNetSerializer = true,
	};
};