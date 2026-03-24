// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_ItemFragment.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct XYLOINVENTORYUTIL_API FXInvU_ItemFragment
{
	GENERATED_BODY()

	FXInvU_ItemFragment() {}
	virtual ~FXInvU_ItemFragment() {}
	
	/** @remark: MUST override in child classes. */
	virtual const UScriptStruct* GetScriptStruct() const { return FXInvU_ItemFragment::StaticStruct(); }
};
