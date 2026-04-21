// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Item/Fragment/Base/XInvU_StackableItemFragment.h"

#include "Item/Fragment/Base/XInvU_FragmentTags.h"

UXInvU_StackableItemFragmentDefinition::UXInvU_StackableItemFragmentDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetFragmentTag(InventoryUtil::Fragment::Stackable);
}
