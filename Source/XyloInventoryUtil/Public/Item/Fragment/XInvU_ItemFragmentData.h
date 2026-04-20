// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_ItemFragmentData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct XYLOINVENTORYUTIL_API FXInvU_ItemFragmentData
{
	GENERATED_BODY()

	FXInvU_ItemFragmentData() {}
	virtual ~FXInvU_ItemFragmentData() {}
	
	/** @remark: MUST override in child classes. */
	virtual const UScriptStruct* GetScriptStruct() const { return FXInvU_ItemFragmentData::StaticStruct(); }
};
