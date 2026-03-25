// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Item/XInvU_ItemStack.h"

#include "Item/XInvU_ItemDefinition.h"
#include "Item/Fragment/Base/XInvU_StackableItemFragment.h"

FXInvU_ItemStack::FXInvU_ItemStack(UXInvU_ItemDefinition* InItemDefinition, int32 InCount)
{
	InitializeAs(InItemDefinition, InCount);
}

void FXInvU_ItemStack::InitializeAs(UXInvU_ItemDefinition* InItemDefinition, int32 InCount)
{
	ItemDefinition = InItemDefinition;
	
	const TArray<UXInvU_ItemFragmentDefinition*>& DefaultFragments = InItemDefinition->GetDefaultFragments();

	// Copy dynamic fragments
	DynamicFragments.Empty(DefaultFragments.Num());
	for (const UXInvU_ItemFragmentDefinition* FragmentDefinition : DefaultFragments)
	{
		if (IsValid(FragmentDefinition))
		{
			if (const FXInvU_ItemFragment* DynamicFragment = FragmentDefinition->GetDynamicFragment())
			{
				TInstancedStruct<FXInvU_ItemFragment> NewFragment;
				NewFragment.InitializeAsScriptStruct(DynamicFragment->GetScriptStruct(), reinterpret_cast<const uint8*>(DynamicFragment));
				DynamicFragments.Add(NewFragment);
			}
		}
	}

	// Set count
	const FXInvU_StackableItemFragment* StackableFragment = InItemDefinition->FindDefaultFragment<FXInvU_StackableItemFragment>();
	int32 MaxCount = StackableFragment ? StackableFragment->MaxCount : 1;
	Count = FMath::Min(InCount, MaxCount);
}

const UXInvU_Item* FXInvU_ItemStack::GetItem() const
{
	UXInvU_ItemDefinition* Definition = ItemDefinition.Get();
	return Definition ? Definition->GetItem<>() : nullptr;
}

const FXInvU_ItemFragment* FXInvU_ItemStack::FindFragment(const UScriptStruct* FragmentClass) const
{
	// Look for fragment in ItemStack
	const TInstancedStruct<FXInvU_ItemFragment>* FoundFragment = DynamicFragments.FindByPredicate([FragmentClass](const TInstancedStruct<FXInvU_ItemFragment>& Fragment)->bool
	{
		return Fragment.GetScriptStruct() == FragmentClass;
	});
	
	if (FoundFragment)
	{
		return FoundFragment->GetPtr<>();
	}

	// If not found, look in DefaultFragments on the definition
	UXInvU_ItemDefinition* Definition = ItemDefinition.Get();
	return Definition ? Definition->FindDefaultFragment(FragmentClass) : nullptr;
}

FXInvU_ItemFragment* FXInvU_ItemStack::FindDynamicFragment(const UScriptStruct* FragmentClass)
{
	TInstancedStruct<FXInvU_ItemFragment>* FoundFragment = DynamicFragments.FindByPredicate([FragmentClass](const TInstancedStruct<FXInvU_ItemFragment>& Fragment)->bool
	{
		return Fragment.GetScriptStruct() == FragmentClass;
	});
	return FoundFragment ? FoundFragment->GetMutablePtr<>() : nullptr;
}
