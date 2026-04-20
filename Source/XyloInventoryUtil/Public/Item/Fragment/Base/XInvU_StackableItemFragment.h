// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item/Fragment/XInvU_ItemFragmentData.h"
#include "XInvU_StackableItemFragment.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct XYLOINVENTORYUTIL_API FXInvU_StackableItemFragment : public FXInvU_ItemFragmentData
{
	GENERATED_BODY()

	virtual const UScriptStruct* GetScriptStruct() const override { return FXInvU_ItemFragmentData::StaticStruct(); }

	UPROPERTY()
	int32 MaxCount = 0;
};
