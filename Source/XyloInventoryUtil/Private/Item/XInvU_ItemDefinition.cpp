// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Item/XInvU_ItemDefinition.h"

const UXInvU_Item* UXInvU_ItemDefinition::K2_GetItem(TSubclassOf<UXInvU_Item> Class) const
{
	if (!Class || !Class->IsChildOf(ItemClass))
	{
		return nullptr;
	}
	return GetItem<>();
}

const FXInvU_ItemFragment* UXInvU_ItemDefinition::FindDefaultFragment(const UScriptStruct* FragmentClass) const
{
	if (!FragmentClass)
	{
		return nullptr;
	}
	
	for (const UXInvU_ItemFragmentDefinition* FragmentDefinition : Fragments)
	{
		if (IsValid(FragmentDefinition))
		{
			FXInvU_ItemFragment* StaticFragment = FragmentDefinition->GetStaticFragment();
			if (StaticFragment && StaticFragment->GetScriptStruct() == FragmentClass)
			{
				return StaticFragment;
			}

			FXInvU_ItemFragment* DynamicFragment = FragmentDefinition->GetDynamicFragment();
			if (DynamicFragment && DynamicFragment->GetScriptStruct() == FragmentClass)
			{
				return DynamicFragment;
			}
		}
	}

	return nullptr;
}
