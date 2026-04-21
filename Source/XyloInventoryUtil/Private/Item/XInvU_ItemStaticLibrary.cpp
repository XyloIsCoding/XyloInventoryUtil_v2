// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Item/XInvU_ItemStaticLibrary.h"

#include "Item/XInvU_ItemDefinition.h"
#include "Item/Fragment/Base/XInvU_FragmentTags.h"
#include "Item/Fragment/Base/XInvU_StackableItemFragment.h"

bool UXInvU_ItemStaticLibrary::MakeItemStack(FXInvU_ItemStack& OutItemStack, const UXInvU_ItemDefinition* ItemDefinition, int32 Count)
{
	if (ensureMsgf(IsValid(ItemDefinition), TEXT("UXInvU_ItemStaticLibrary::MakeItemStack >> item definition must be valid")))
	{
		OutItemStack = FXInvU_ItemStack(ItemDefinition, Count);
		return true;
	}
	return false;
}

const UXInvU_ItemDefinition* UXInvU_ItemStaticLibrary::GetItemDefinition(const FXInvU_ItemStack& ItemStack)
{
	return ItemStack.GetItemDefinition();
}

const UXInvU_Item* UXInvU_ItemStaticLibrary::GetItem(const FXInvU_ItemStack& ItemStack)
{
	const UXInvU_ItemDefinition* ItemDefinition = ItemStack.GetItemDefinition();
	return IsValid(ItemDefinition) ? ItemDefinition->GetItem<>() : nullptr;
}

int32 UXInvU_ItemStaticLibrary::GetStackCount(const FXInvU_ItemStack& ItemStack)
{
	return ItemStack.GetCount();
}

int32 UXInvU_ItemStaticLibrary::GetStackMaxCount(const FXInvU_ItemStack& ItemStack)
{
	const FXInvU_StackableItemFragmentData* StackableFragment = FindFragmentData<FXInvU_StackableItemFragmentData>(ItemStack, InventoryUtil::Fragment::Stackable);
	return StackableFragment ? StackableFragment->MaxCount : 1;
}

void UXInvU_ItemStaticLibrary::SetStackCount(FXInvU_ItemStack& ItemStack, int32 NewCount)
{
	ItemStack.SetCount(NewCount);
}

const UXInvU_ItemFragmentDefinition* UXInvU_ItemStaticLibrary::GetFragmentDefinition(const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag)
{
	const UXInvU_ItemDefinition* ItemDefinition = ItemStack.GetItemDefinition();
	if (!IsValid(ItemDefinition))
	{
		return nullptr;
	}

	return ItemDefinition->FindFragmentDefinition(FragmentTag);
}

const UXInvU_ItemFragment* UXInvU_ItemStaticLibrary::GetFragment(const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag)
{
	const UXInvU_ItemFragmentDefinition* FragmentDefinition = GetFragmentDefinition(ItemStack, FragmentTag);
	if (!IsValid(FragmentDefinition))
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

const FXInvU_ItemFragmentData* UXInvU_ItemStaticLibrary::FindFragmentData(const UXInvU_ItemDefinition* ItemDefinition, FGameplayTag FragmentTag, const UScriptStruct* StructType)
{
	if (!IsValid(ItemDefinition))
	{
		return nullptr;
	}

	const UXInvU_ItemFragmentDefinition* FragmentDefinition = ItemDefinition->FindFragmentDefinition(FragmentTag);
	if (!IsValid(FragmentDefinition))
	{
		return nullptr;
	}

	const FXInvU_ItemFragmentData* FragmentStaticData = FragmentDefinition->GetFragmentStaticData();
	if (FragmentStaticData && FragmentStaticData->GetScriptStruct()->IsChildOf(StructType))
	{
		return FragmentStaticData;
	}

	const FXInvU_ItemFragmentData* FragmentDynamicData = FragmentDefinition->GetFragmentDynamicData();
	if (FragmentDynamicData && FragmentDynamicData->GetScriptStruct()->IsChildOf(StructType))
	{
		return FragmentDynamicData;
	}

	return nullptr;
}

const FXInvU_ItemFragmentData* UXInvU_ItemStaticLibrary::FindFragmentData(const FXInvU_ItemStack& ItemStack, FGameplayTag FragmentTag, const UScriptStruct* StructType)
{
	const UXInvU_ItemDefinition* ItemDefinition = ItemStack.GetItemDefinition();
	if (!IsValid(ItemDefinition))
	{
		return nullptr;
	}
	
	if (const FXInvU_ItemFragmentData* FragmentDynamicData = ItemStack.FindFragmentDynamicData(FragmentTag, StructType))
	{
		return FragmentDynamicData;
	}

	const UXInvU_ItemFragmentDefinition* FragmentDefinition = ItemDefinition->FindFragmentDefinition(FragmentTag);
	if (!IsValid(FragmentDefinition))
	{
		return nullptr;
	}

	const FXInvU_ItemFragmentData* FragmentStaticData = FragmentDefinition->GetFragmentStaticData();
	if (FragmentStaticData && FragmentStaticData->GetScriptStruct()->IsChildOf(StructType))
	{
		return FragmentStaticData;
	}

	return nullptr;
}
