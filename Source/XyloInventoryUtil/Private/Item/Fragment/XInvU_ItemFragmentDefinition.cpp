// Copyright (c) 2026, XyloIsCoding. All rights reserved.


#include "Item/Fragment/XInvU_ItemFragmentDefinition.h"

#include "Item/Fragment/XInvU_ItemFragment.h"

UXInvU_ItemFragmentDefinition::UXInvU_ItemFragmentDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const UXInvU_ItemFragment* UXInvU_ItemFragmentDefinition::K2_GetFragment(TSubclassOf<UXInvU_ItemFragment> Class) const
{
	if (!Class || !Class->IsChildOf(Fragment.GetClass()))
	{
		return nullptr;
	}
	return GetFragment<>();
}

void UXInvU_ItemFragmentDefinition::SetFragmentTag(FGameplayTag InFragmentTag)
{
	FragmentTag = InFragmentTag;
}

const FXInvU_ItemFragmentData* UXInvU_BlueprintItemFragmentDefinition::GetFragmentDataByName(FName FragmentDataName) const
{
	FProperty* Property = GetClass()->FindPropertyByName(FragmentDataName);
	if (FStructProperty* StructProp = CastField<FStructProperty>(Property))
	{
		if (StructProp->Struct->IsChildOf(FXInvU_ItemFragmentData::StaticStruct()))
		{
			return StructProp->ContainerPtrToValuePtr<FXInvU_ItemFragmentData>(this);
		}
	}
	return nullptr;
}

FName UXInvU_BlueprintItemFragmentDefinition::FragmentStaticDataName = FName(TEXT("FragmentStaticData"));

FName UXInvU_BlueprintItemFragmentDefinition::FragmentDynamicDataName = FName(TEXT("FragmentDynamicData"));
