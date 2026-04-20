// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "XInvU_Item.h"
#include "Fragment/XInvU_ItemFragmentDefinition.h"
#include "XInvU_ItemStack.h"
#include "Engine/DataAsset.h"
#include "Fragment/XInvU_ItemFragmentData.h"
#include "XInvU_ItemDefinition.generated.h"

class UXInvU_Item;
class UXInvU_ItemFragmentDefinition;

/**
 * 
 */
UCLASS()
class XYLOINVENTORYUTIL_API UXInvU_ItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FName GetItemName() const { return ItemName; }
	
	template <std::derived_from<UXInvU_Item> T = UXInvU_Item>
	const UXInvU_Item* GetItem() const { return Item; }

	UFUNCTION(BlueprintCallable, DisplayName="GetItem", meta = (DeterminesOutputType = "Class"))
	const UXInvU_Item* K2_GetItem(TSubclassOf<UXInvU_Item> Class) const;

	UFUNCTION(BlueprintCallable)
	const TArray<UXInvU_ItemFragmentDefinition*>& GetFragmentDefinitions() const { return Fragments; }

	UFUNCTION(BlueprintCallable)
	const UXInvU_ItemFragmentDefinition* GetFragmentDefinition(FGameplayTag FragmentTag) const;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TObjectPtr<UXInvU_Item> Item;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<TObjectPtr<UXInvU_ItemFragmentDefinition>> Fragments;
};
