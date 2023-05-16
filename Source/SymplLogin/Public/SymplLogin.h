// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
//#include "ISettingsModule.h"
//#include "ISettingsSection.h"
//#include "ISettingsContainer.h"

#include "SymplLoginSettings.h"

#include "Modules/ModuleManager.h"

class FSymplLoginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	// Callback for when the settings were saved.
	bool HandleSettingsSaved();

	void RegisterSettings();

	void UnregisterSettings();

};
