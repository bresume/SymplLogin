// Fill out your copyright notice in the Description page of Project Settings.


#include "SymplLoginSettings.h"

USymplLoginSettings::USymplLoginSettings()
{
	LoginBackendType = ESymplLoginBackendType::EPLAYFAB;
	PlayFabTitleID = "000";
	PlayFabSecretKey = "000";
	PlayFabProductionEnvironmentURL = "https://<Your Title ID>.playfabapi.com";
}