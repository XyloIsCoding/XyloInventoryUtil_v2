// Copyright (c) 2026, XyloIsCoding. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "XInvU_Item.h"
#include "Fragment/XInvU_ItemFragmentDefinition.h"
#include "XInvU_ItemStack.h"
#include "Engine/DataAsset.h"
#include "Fragment/XInvU_ItemFragment.h"
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
	const UXInvU_Item* GetItem() const { return ItemClass ? ItemClass->GetDefaultObject<T>() : nullptr; }

	UFUNCTION(BlueprintCallable, DisplayName="GetItem", meta = (DeterminesOutputType = "Class"))
	const UXInvU_Item* K2_GetItem(TSubclassOf<UXInvU_Item> Class) const;

	const FXInvU_ItemFragment* FindDefaultFragment(const UScriptStruct* FragmentClass) const;
	
	template<std::derived_from<FXInvU_ItemFragment> T>
	const T* FindDefaultFragment() const { return static_cast<const T*>(FindDefaultFragment(T::StaticStruct())); }

	UFUNCTION(BlueprintCallable)
	const TArray<UXInvU_ItemFragmentDefinition*>& GetDefaultFragments() const { return Fragments; }
	
protected:
	UPROPERTY(EditAnywhere)
	FName ItemName;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UXInvU_Item> ItemClass;

	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UXInvU_ItemFragmentDefinition>> Fragments;
};
