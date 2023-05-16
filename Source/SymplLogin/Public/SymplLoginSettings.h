// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ESymplLoginBackendType.h"

#include "SymplLoginSettings.generated.h"

/**
 * Setting object used to hold both config settings and editable ones in one place
 * To ensure the settings are saved to the specified config file make sure to add
 * props using the globalconfig or config meta.
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Sympl Login Settings"))
class USymplLoginSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	USymplLoginSettings();

	static const USymplLoginSettings* Get() {return GetDefault<USymplLoginSettings>();}

	/** 
	 * The login backend to use. 
	 * I.E. PlayFab or your own custom backend. 
	*/
	UPROPERTY(EditAnywhere, config, Category = "Settings")
		ESymplLoginBackendType LoginBackendType;

	/** 
	 * PlayFab title ID.
	*/
	UPROPERTY(EditAnywhere, config, Category = "Settings|PlayFab")
		FString PlayFabTitleID;

	/**
	 * PlayFab secret key.
	*/
	UPROPERTY(EditAnywhere, config, Category = "Settings|PlayFab")
		FString PlayFabSecretKey;

	/**
	 * PlayFab Production Environment URL.
	*/
	UPROPERTY(EditAnywhere, config, Category = "Settings|PlayFab")
		FString PlayFabProductionEnvironmentURL;

};