// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_ItemFragment.h"
#include "UObject/Object.h"
#include "XInvU_ItemFragmentDefinition.generated.h"

/**
 * Subclass this object and add UPROPERTY UXInvU_ItemFragment members for the static and/or dynamic fragment.
 * Then override the two functions to return your members.
 * We use this method instead of instanced structs so we have access to editor customization.
 */
UCLASS(BlueprintType, Abstract, DefaultToInstanced, EditInlineNew)
class XYLOINVENTORYUTIL_API UXInvU_ItemFragmentDefinition : public UObject
{
	GENERATED_BODY()

public:
	virtual FXInvU_ItemFragment* GetStaticFragment() const { return nullptr; }
	virtual FXInvU_ItemFragment* GetDynamicFragment() const { return nullptr; }
};
