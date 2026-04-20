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

	FXInvU_InventorySlotRepTracker() {}

	FXInvU_InventorySlotRepTracker(const FXInvU_InventorySlotRepTracker& Other) : StackID(Other.StackID), ChangeID(Other.ChangeID) { }
	
	FXInvU_InventorySlotRepTracker(FXInvU_InventorySlotRepTracker&& Other) noexcept : StackID(Other.StackID), ChangeID(Other.ChangeID) { }

	FXInvU_InventorySlotRepTracker& operator=(const FXInvU_InventorySlotRepTracker& Other)
	{
		StackID = Other.StackID;
		ChangeID = Other.ChangeID;
		return *this;
	}

	FXInvU_InventorySlotRepTracker& operator=(FXInvU_InventorySlotRepTracker&& Other) noexcept
	{
		StackID = Other.StackID;
		ChangeID = Other.ChangeID;
		return *this;
	}

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
	UPROPERTY(Transient)
	bool bStackDirty = false;

	UPROPERTY(Transient)
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