// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Item/XInvU_ItemStaticLibrary.h"

#include "Item/XInvU_ItemDefinition.h"

const UXInvU_ItemDefinition* UXInvU_ItemStaticLibrary::GetItemDefinition(const FXInvU_ItemStack& ItemStack)
{
	return ItemStack.GetItemDefinition();
}

const UXInvU_Item* UXInvU_ItemStaticLibrary::GetItem(const FXInvU_ItemStack& ItemStack)
{
	const UXInvU_ItemDefinition* ItemDefinition = ItemStack.GetItemDefinition();
	return ItemDefinition ? ItemDefinition->GetItem<>() : nullptr;
}

int32 UXInvU_ItemStaticLibrary::GetStackCount(const FXInvU_ItemStack& ItemStack)
{
	return ItemStack.GetCount();
}

void UXInvU_ItemStaticLibrary::SetStackCount(FXInvU_ItemStack& ItemStack, int32 NewCount)
{
	ItemStack.SetCount(NewCount);
}

const UXInvU_ItemFragmentDefinition* UXInvU_ItemStaticLibrary::GetFragmentDefinition(const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag)
{
	const UXInvU_ItemDefinition* ItemDefinition = ItemStack.GetItemDefinition();
	if (!ItemDefinition)
	{
		return nullptr;
	}

	return ItemDefinition->FindFragmentDefinition(FragmentTag);
}

const UXInvU_ItemFragment* UXInvU_ItemStaticLibrary::GetFragment(const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag)
{
	const UXInvU_ItemFragmentDefinition* FragmentDefinition = GetFragmentDefinition(ItemStack, FragmentTag);
	if (!FragmentDefinition)
	{
		return nullptr;
	}

	return FragmentDefinition->GetFragment<>();
}

bool UXInvU_ItemStaticLibrary::GetFragmentData(TInstancedStruct<FXInvU_ItemFragmentData>& OutData, const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag, const UScriptStruct* StructType)
{
	if (const FXInvU_ItemFragmentData* FragmentData = FindFragmentData(ItemStack, FragmentTag, StructType))
	{
		OutData.InitializeAsScriptStruct(FragmentData->GetScriptStruct(), reinterpret_cast<const uint8*>(FragmentData));
		return true;
	}
	return false;
}

bool UXInvU_ItemStaticLibrary::SetFragmentDynamicData(FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag, const TInstancedStruct<FXInvU_ItemFragmentData>& NewData)
{
	if (FXInvU_ItemFragmentData* FragmentDynamicData = ItemStack.FindFragmentDynamicData(FragmentTag, NewData.GetScriptStruct()))
	{
		*FragmentDynamicData = NewData.Get<>();
		return true;
	}
	return false;
}

const FXInvU_ItemFragmentData* UXInvU_ItemStaticLibrary::FindFragmentData(const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag, const UScriptStruct* StructType)
{
	const UXInvU_ItemDefinition* ItemDefinition = ItemStack.GetItemDefinition();
	if (!ItemDefinition)
	{
		return nullptr;
	}
	
	if (const FXInvU_ItemFragmentData* FragmentDynamicData = ItemStack.FindFragmentDynamicData(FragmentTag, StructType))
	{
		return FragmentDynamicData;
	}

	const UXInvU_ItemFragmentDefinition* FragmentDefinition = ItemDefinition->FindFragmentDefinition(FragmentTag);
	if (!FragmentDefinition)
	{
		return nullptr;
	}

	const FXInvU_ItemFragmentData* FragmentStaticData = FragmentDefinition->GetFragmentStaticData();
	if (!FragmentStaticData)
	{
		return nullptr;
	}

	return FragmentStaticData->GetScriptStruct()->IsChildOf(StructType) ? FragmentStaticData : nullptr;
}
