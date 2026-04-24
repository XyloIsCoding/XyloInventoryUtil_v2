// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_InventorySlot.h"
#include "Item/XInvU_ItemStack.h"
#include "Item/XInvU_ItemStackPtr.h"
#include "UObject/Object.h"
#include "XInvU_Inventory.generated.h"

struct FXInvU_Inventory;

DECLARE_MULTICAST_DELEGATE_TwoParams(FXInvU_InventoryStackPropertyChanged, FXInvU_Inventory& /* Inventory */, int32 /* SlotIndex */)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FXInvU_InventoryStackChanged, FXInvU_Inventory& /* Inventory */, int32 /* SlotIndex */, const FXInvU_ItemStack& /* OldStack */)

/**
 * 
 */
USTRUCT(BlueprintType)
struct XYLOINVENTORYUTIL_API FXInvU_Inventory
{
	GENERATED_BODY()
	friend FXInvU_ItemStackPtr;

	FXInvU_Inventory() {}
	
	FXInvU_Inventory(int32 Size, AActor* Owner = nullptr)
		: InventoryOwner(Owner)
	{
		Slots.SetNum(Size);
	}
	
	virtual ~FXInvU_Inventory() {}

/*====================================================================================================================*/
	// InventoryManagement

public:
	virtual void DebugPrintInventory() const;

	virtual void CopyInventoryContent(const FXInvU_Inventory& Source);
	
	virtual int32 GetInventorySize() const { return Slots.Num(); }

	virtual const FXInvU_ItemStack* GetStack(int32 SlotIndex) const;

	virtual FXInvU_ItemStackPtr GetStackPtr(int32 SlotIndex);
	
	virtual void SetStack(int32 SlotIndex, const FXInvU_ItemStack& NewStack);

	virtual int32 AddStack(const FXInvU_ItemStack& NewStack, int32 CountOverride = 0);

	virtual void RemoveStack(int32 SlotIndex);

	virtual int32 ConsumeItem(UXInvU_ItemDefinition* ItemDefinition, int32 Count);

	virtual int32 GetItemCount(UXInvU_ItemDefinition* ItemDefinition) const;

	virtual int32 GetItemCountByCategory(FGameplayTag Category) const;

protected:
	virtual FXInvU_ItemStack* GetStackMutable(int32 SlotIndex);

	// ~InventoryManagement
/*====================================================================================================================*/

/*====================================================================================================================*/
	// SlotFilters

public:
	virtual FGameplayTagContainer& GetSlotCategoryFilterRef(int32 SlotIndex);

	virtual bool GetSlotCategoryFilter(int32 SlotIndex, FGameplayTagContainer& OutCategoryFilter) const;

	virtual void SetSlotCategoryFilter(int32 SlotIndex, FGameplayTagContainer NewCategoryFilter);

	virtual void AddSlotCategoryFilter(int32 SlotIndex, FGameplayTag NewCategoryFilter);
	
protected:
	virtual bool IsStackCompatibleWithSlot(const FXInvU_InventorySlot& Slot, const FXInvU_ItemStack& NewStack) const;

	// ~SlotFilters
/*====================================================================================================================*/

/*====================================================================================================================*/
	// Replication
	
protected:
	virtual bool CanMarkDirty() const;
	virtual void MarkStackPropertyDirty(FXInvU_InventorySlot& Slot, int32 SlotIndex);
	virtual void MarkStackDirty(FXInvU_InventorySlot& Slot, int32 SlotIndex, const FXInvU_ItemStack& OldStack);

	// ~Replication
/*====================================================================================================================*/

/*====================================================================================================================*/
	// Callbacks
	
public:
	FXInvU_InventoryStackPropertyChanged StackPropertyChangedDelegate;
	FXInvU_InventoryStackChanged StackChangedDelegate;

	virtual void GetChangedIndexes(const FXInvU_Inventory& OldInventory, TArray<int32>& OutChangedIndexes) const;
	virtual void BroadcastChanges(const FXInvU_Inventory& OldInventory);

	// ~Callbacks
/*====================================================================================================================*/
	
protected:
	UPROPERTY()
	TArray<FXInvU_InventorySlot> Slots;

	UPROPERTY()
	TWeakObjectPtr<AActor> InventoryOwner;
};
