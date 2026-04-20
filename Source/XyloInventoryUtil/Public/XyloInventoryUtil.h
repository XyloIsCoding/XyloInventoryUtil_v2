// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

XYLOINVENTORYUTIL_API DECLARE_LOG_CATEGORY_EXTERN(LogXyloInventoryUtil, Log, All);

class FXyloInventoryUtilModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
