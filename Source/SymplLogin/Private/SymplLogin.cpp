// Copyright Epic Games, Inc. All Rights Reserved.

#include "SymplLogin.h"

#define LOCTEXT_NAMESPACE "FSymplLoginModule"

void FSymplLoginModule::StartupModule()
{
	/*
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "SymplLogin",
			LOCTEXT("RuntimeSettingsName", "SymplLogin"),
			LOCTEXT("RuntimeSettingsDescription", "Configure Login Settings"),
			GetMutableDefault<USymplLoginSettings>());
	}
	*/
}

void FSymplLoginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	/*
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "SymplLogin");
	}
	*/
}

bool FSymplLoginModule::HandleSettingsSaved()
{
	USymplLoginSettings* Settings = GetMutableDefault<USymplLoginSettings>();
	bool ResaveSettings = false;

	// You can put any validation code in here and resave the settings in case an invalid
	// value has been entered

	if (ResaveSettings)
	{
		Settings->SaveConfig();
	}

	return true;
}

void FSymplLoginModule::RegisterSettings()
{
	// Registering some settings is just a matter of exposing the default UObject of
	// your desired class, feel free to add here all those settings you want to expose
	// to your LDs or artists.
	/*
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("SymplLogin",
			LOCTEXT("RuntimeWDCategoryName", "SymplLogin"),
			LOCTEXT("RuntimeWDCategoryDescription", "Game configuration for the Sympl Login Settings game module"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "SymplLogin", "General",
			LOCTEXT("RuntimeGeneralSettingsName", "General"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Base configuration for SymplLogin module"),
			GetMutableDefault<USymplLoginSettings>()
		);

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FSymplLoginModule::HandleSettingsSaved);
		}
	}
	*/
}

void FSymplLoginModule::UnregisterSettings()
{
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.
	/*
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "CustomSettings", "General");
	}
	*/
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSymplLoginModule, SymplLogin)