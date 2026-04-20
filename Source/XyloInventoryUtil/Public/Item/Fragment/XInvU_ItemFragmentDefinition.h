// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "XInvU_ItemFragmentData.h"
#include "UObject/Object.h"
#include "XInvU_ItemFragmentDefinition.generated.h"

class UXInvU_ItemFragment;

/**
 * Subclass this object and add UPROPERTY FXInvU_ItemFragmentData members for the static and/or dynamic fragment.
 * Then override the two functions to return your members.
 * We use this method instead of instanced structs so we have access to editor customization.
 */
UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew, Abstract)
class XYLOINVENTORYUTIL_API UXInvU_ItemFragmentDefinition : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	
	template <std::derived_from<UXInvU_ItemFragment> T = UXInvU_ItemFragment>
	const UXInvU_ItemFragment* GetFragment() const { return Fragment; }

	UFUNCTION(BlueprintCallable, DisplayName="GetFragment", meta = (DeterminesOutputType = "Class"))
	const UXInvU_ItemFragment* K2_GetFragment(TSubclassOf<UXInvU_ItemFragment> Class) const;
	
	virtual FXInvU_ItemFragmentData* GetFragmentStaticData() const { return nullptr; }
	
	virtual FXInvU_ItemFragmentData* GetFragmentDynamicData() const { return nullptr; }

protected:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag FragmentTag;
	
	UPROPERTY(EditDefaultsOnly, Instanced)
	TObjectPtr<UXInvU_ItemFragment> Fragment;
};
