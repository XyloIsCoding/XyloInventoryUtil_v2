// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Item/XInvU_ItemDefinition.h"

const UXInvU_Item* UXInvU_ItemDefinition::K2_GetItem(TSubclassOf<UXInvU_Item> Class) const
{
	if (!Class || !Class->IsChildOf(Item.GetClass()))
	{
		return nullptr;
	}
	return GetItem<>();
}
