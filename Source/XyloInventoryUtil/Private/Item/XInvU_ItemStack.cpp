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
	
	const TArray<UXInvU_ItemFragmentDefinition*>& DefaultFragments = InItemDefinition->GetFragmentDefinitions();

	// Copy fragments dynamic data
	FragmentsDynamicData.Empty(DefaultFragments.Num());
	for (const UXInvU_ItemFragmentDefinition* FragmentDefinition : DefaultFragments)
	{
		if (IsValid(FragmentDefinition))
		{
			if (const FXInvU_ItemFragmentData* DynamicData = FragmentDefinition->GetFragmentDynamicData())
			{
				FXInvU_ItemFragmentContainer NewFragment;
				NewFragment.FragmentTag = FragmentDefinition->GetFragmentTag();
				NewFragment.FragmentData.InitializeAsScriptStruct(DynamicData->GetScriptStruct(), reinterpret_cast<const uint8*>(DynamicData));
				FragmentsDynamicData.Add(NewFragment);
			}
		}
	}

	// Set count
	const FXInvU_StackableItemFragment* StackableFragment = nullptr; // TODO: find fragment
	int32 MaxCount = StackableFragment ? StackableFragment->MaxCount : 1;
	Count = FMath::Min(InCount, MaxCount);
}

const UXInvU_Item* FXInvU_ItemStack::GetItem() const
{
	UXInvU_ItemDefinition* Definition = ItemDefinition.Get();
	return Definition ? Definition->GetItem<>() : nullptr;
}

void FXInvU_ItemStack::SetCount(int32 NewCount)
{
	Count = NewCount;
}

FXInvU_ItemFragmentData* FXInvU_ItemStack::GetFragmentDynamicData(FGameplayTag FragmentTag, UStruct* StructType)
{
	for (FXInvU_ItemFragmentContainer& FragmentContainer : FragmentsDynamicData)
	{
		if (FragmentContainer.FragmentTag.MatchesTagExact(FragmentTag) && FragmentContainer.FragmentData.GetScriptStruct()->IsChildOf(StructType))
		{
			return FragmentContainer.FragmentData.GetMutablePtr<>();
		}
	}
	return nullptr;
}

const FXInvU_ItemFragmentData* FXInvU_ItemStack::GetFragmentDynamicData(FGameplayTag FragmentTag, UStruct* StructType) const
{
	for (const FXInvU_ItemFragmentContainer& FragmentContainer : FragmentsDynamicData)
	{
		if (FragmentContainer.FragmentTag.MatchesTagExact(FragmentTag) && FragmentContainer.FragmentData.GetScriptStruct()->IsChildOf(StructType))
		{
			return FragmentContainer.FragmentData.GetPtr<>();
		}
	}
	return nullptr;
}
