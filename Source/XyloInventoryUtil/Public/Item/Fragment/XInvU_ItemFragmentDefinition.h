// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "XInvU_ItemFragmentData.h"
#include "UObject/Object.h"
#include "XInvU_ItemFragmentDefinition.generated.h"

class UXInvU_ItemFragment;

/**
 * After subclassing this object you must call SetFragmentTag in constructor passing the tag to associate univocally
 * with this fragment.
 * You can optionally and add member UPROPERTY derived from FXInvU_ItemFragmentData to contain the static and/or
 * dynamic data of this fragment. If you do, remember to override the two getter functions to return your members.
 */
UCLASS(DisplayName="Fragment Definition", BlueprintType, DefaultToInstanced, EditInlineNew, Abstract)
class XYLOINVENTORYUTIL_API UXInvU_ItemFragmentDefinition : public UObject
{
	GENERATED_BODY()

public:
	UXInvU_ItemFragmentDefinition(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable)
	FGameplayTag GetFragmentTag() const { return FragmentTag; }

	/** Set the tag univocally defines this fragment. */
	UFUNCTION(BlueprintCallable)
	void SetFragmentTag(FGameplayTag InFragmentTag);
	
	template <std::derived_from<UXInvU_ItemFragment> T = UXInvU_ItemFragment>
	const T* GetFragment() const { return Cast<T>(Fragment); }

	UFUNCTION(BlueprintCallable, DisplayName="GetFragment", meta = (DeterminesOutputType="Class"))
	const UXInvU_ItemFragment* K2_GetFragment(TSubclassOf<UXInvU_ItemFragment> Class) const;
	
	virtual const FXInvU_ItemFragmentData* GetFragmentStaticData() const { return nullptr; }
	
	virtual const FXInvU_ItemFragmentData* GetFragmentDynamicData() const { return nullptr; }

protected:
	UPROPERTY(Category="Fragment", VisibleAnywhere, meta = (DisplayPriority="0"))
	FGameplayTag FragmentTag;
	
	UPROPERTY(Category="Fragment", EditDefaultsOnly, Instanced, meta = (DisplayPriority="1"))
	TObjectPtr<UXInvU_ItemFragment> Fragment;
};


/**
 * Subclass in blueprint, call SetFragmentTag in construction script, and optionally add two properties derived from
 * FXInvU_ItemFragmentData named FragmentStaticData and FragmentDynamicData.
 */
UCLASS(DisplayName="Blueprint Fragment Definition", Blueprintable)
class XYLOINVENTORYUTIL_API UXInvU_BlueprintItemFragmentDefinition : public UXInvU_ItemFragmentDefinition
{
	GENERATED_BODY()

public:
	virtual const FXInvU_ItemFragmentData* GetFragmentStaticData() const override { return GetFragmentDataByName(FragmentStaticDataName); }

	virtual const FXInvU_ItemFragmentData* GetFragmentDynamicData() const override { return GetFragmentDataByName(FragmentDynamicDataName); }

protected:
	const FXInvU_ItemFragmentData* GetFragmentDataByName(FName FragmentDataName) const;

	static FName FragmentStaticDataName;
	
	static FName FragmentDynamicDataName;
};
