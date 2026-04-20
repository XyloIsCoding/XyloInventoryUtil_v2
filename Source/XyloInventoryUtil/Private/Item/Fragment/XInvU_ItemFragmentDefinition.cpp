// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Item/Fragment/XInvU_ItemFragmentDefinition.h"

#include "Item/Fragment/XInvU_ItemFragment.h"

const UXInvU_ItemFragment* UXInvU_ItemFragmentDefinition::K2_GetFragment(TSubclassOf<UXInvU_ItemFragment> Class) const
{
	if (!Class || !Class->IsChildOf(Fragment.GetClass()))
	{
		return nullptr;
	}
	return GetFragment<>();
}
