// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/DeveloperSettings.h"

#include "ESymplLoginBackendType.h"
#include "SymplLoginSettings.h"
#include "AuthenticationBase.h"
#include "SteamworksAuthentication.h"
#include "PlayFabAuthentication.h"

#include "SymplLoginFunctions.generated.h"

/**
 * Functions for the sympl login plugin.
 */
UCLASS(BlueprintType,Blueprintable)
class SYMPLLOGIN_API USymplLoginFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	 * Return the Sympl Login Settings.
	*/
	UFUNCTION(BlueprintPure, Category = "Login", meta = (CompactNodeTitle = "Settings"))
		static const USymplLoginSettings* GetLoginSettings() {return USymplLoginSettings::Get();}

	/**
	 * Return the Sympl Login Settings' backend type.
	*/
	UFUNCTION(BlueprintPure, Category = "Login", meta = (CompactNodeTitle = "Backend"))
		static ESymplLoginBackendType GetLoginBackendType() { return GetLoginSettings()->LoginBackendType; }

	/**
	 * Return the Sympl Login Settings' title ID for playfab.
	*/
	UFUNCTION(BlueprintPure, Category = "Login|PlayFab", meta = (CompactNodeTitle = "TitleID"))
		static FString GetPlayFabTitleID() { return GetLoginSettings()->PlayFabTitleID; }

	/**
	 * Return the Sympl Login Settings' secret key for playfab.
	*/
	UFUNCTION(BlueprintPure, Category = "Login|PlayFab", meta = (CompactNodeTitle = "Key"))
		static FString GetPlayFabSecretKey() { return GetLoginSettings()->PlayFabSecretKey; }

	/**
	 * Return the Sympl Login Settings' production environment URL.
	*/
	UFUNCTION(BlueprintPure, Category = "Login|PlayFab", meta = (CompactNodeTitle = "ProdEnvURL"))
		static FString GetPlayFabProductionEnvironmentURL(){ return GetLoginSettings()->PlayFabProductionEnvironmentURL; }

	/**
	 * Return a series of random string elements for generating a guest username and/or password.
	*/
	UFUNCTION(BlueprintPure, Category = "Login", meta = (CompactNodeTitle = "RandomStringParams"))
		static FString GetRandomStringParams(bool bIncludeUppercaseLetters = true, bool bIncludeLowercaseLetters = true, 
			bool bIncludeDigits = true, bool bIncludeSpecialCharacters = true, bool bRandomize = true, int32 Length = 10);

	/**
	 * Return a series of random string elements for generating a guest username and/or password.
	*/
	UFUNCTION(BlueprintPure, Category = "Login", meta = (CompactNodeTitle = "RandUser"))
		static FString GenerateRandomUsername(int32 UsernameLength = 10) { return GetRandomStringParams(true,true,true,true,true,UsernameLength); }

	/**
	 * Return a series of random string elements for generating a guest username and/or password.
	*/
	UFUNCTION(BlueprintPure, Category = "Login", meta = (CompactNodeTitle = "RandPass"))
		static FString GenerateRandomPassword(int32 PasswordLength = 25) { return GetRandomStringParams(true, true, true, true, true, PasswordLength); }

	/**
	 * Login with steamworks.
	 * For now, requires playfab.
	*/
	UFUNCTION(BlueprintCallable, Category = "Authentication")
		static UAuthenticationBase* SteamworksLogin();

	/**
	 * Platform agnostic playfab login.
	 * Also takes Username and Password as a final fallback if Auth ticket or other settings are not gathered.
	*/
	UFUNCTION(BlueprintCallable, Category = "Authentication")
		static UAuthenticationBase* PlayFabLogin(FString Username = "", FString Password = "");

	/**
	 * Platform agnostic playfab login.
	 * Also takes Username and Password as a final fallback if Auth ticket or other settings are not gathered.
	*/
	UFUNCTION(BlueprintCallable, Category = "Authentication")
		static UAuthenticationBase* PlayFabLogin_CustomID(FString CustomID);

	/**
	 * Call this function to initialize PlayFab with the plugin settings.
	 * If you do not call this at some point (I.E. on GameInstance->Init() then your API calls will fail.
	*/
	UFUNCTION(BlueprintCallable, Category = "PlayFab")
		static void InitializePlayFab();

	/**
	 * Convert a auth response to a string.
	*/
	UFUNCTION(BlueprintPure,Category = "Authentication", meta = (CompactNodeTitle = "->", BlueprintAutocast))
		static FString AuthenticationHandlerToString(FAuthenticationHandler A) { return A.ToString(); }
};
