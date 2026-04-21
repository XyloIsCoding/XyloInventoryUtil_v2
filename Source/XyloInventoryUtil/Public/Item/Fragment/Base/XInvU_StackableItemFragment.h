// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item/Fragment/XInvU_ItemFragmentData.h"
#include "Item/Fragment/XInvU_ItemFragmentDefinition.h"
#include "XInvU_StackableItemFragment.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct XYLOINVENTORYUTIL_API FXInvU_StackableItemFragmentData : public FXInvU_ItemFragmentData
{
	GENERATED_BODY()

	virtual const UScriptStruct* GetScriptStruct() const override { return FXInvU_StackableItemFragmentData::StaticStruct(); }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxCount = 0;
};


/**
 * 
 */
UCLASS(DisplayName="Stackable Fragment Definition")
class XYLOINVENTORYUTIL_API UXInvU_StackableItemFragmentDefinition : public UXInvU_ItemFragmentDefinition
{
	GENERATED_BODY()

public:
	UXInvU_StackableItemFragmentDefinition(const FObjectInitializer& ObjectInitializer);

public:
	virtual const FXInvU_ItemFragmentData* GetFragmentStaticData() const override { return &StaticData; }

protected:
	UPROPERTY(Category="Fragment", EditDefaultsOnly, BlueprintReadOnly)
	FXInvU_StackableItemFragmentData StaticData;
};
