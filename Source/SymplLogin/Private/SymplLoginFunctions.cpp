// Fill out your copyright notice in the Description page of Project Settings.


#include "SymplLoginFunctions.h"

FString USymplLoginFunctions::GetRandomStringParams(bool bIncludeUppercaseLetters, bool bIncludeLowercaseLetters, bool bIncludeDigits, bool bIncludeSpecialCharacters, bool bRandomize, int32 Length)
{
    FString chars = "";
    FString output = "";

    // Add uppercase letters to available chars
    if (bIncludeUppercaseLetters)
    {
        chars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }

    // Add lowercase letters to available chars
    if (bIncludeLowercaseLetters)
    {
        chars += "abcdefghijklmnopqrstuvwxyz";
    }

    // Add digits to available chars
    if (bIncludeDigits)
    {
        chars += "0123456789";
    }

    // Add special chars to available chars
    if (bIncludeSpecialCharacters)
    {
        chars += "!@#$%^&*()_+-={}[]\\|;:'\",.<>/?";
    }

    // Generate random string of specified length
    for (int32 i = 0; i < Length; i++)
    {
        int32 index = FMath::RandRange(0, chars.Len() - 1);
        output += chars.Mid(index, 1);
    }

    return output;
}

UAuthenticationBase* USymplLoginFunctions::SteamworksLogin()
{
#if WITH_STEAMWORKS && WITH_PLAYFAB
    FSteamworksAuthentication* SteamworksAuth = NewObject<FSteamworksAuthentication>();
    SteamworksAuth->Login();
    return SteamworksAuth;
#endif // WITH_STEAMWORKS && WITH_PLAYFAB
}

UAuthenticationBase* USymplLoginFunctions::PlayFabLogin(FString Username, FString Password)
{
#if WITH_PLAYFAB
    FPlayFabAuthentication* PlayFabAuth = NewObject<FPlayFabAuthentication>();
    PlayFabAuth->Login(Username, Password);
    return PlayFabAuth;
#endif // WITH_PLAYFAB
}

UAuthenticationBase* USymplLoginFunctions::PlayFabLogin_CustomID(FString CustomID)
{
#if WITH_PLAYFAB
    FPlayFabAuthentication* PlayFabAuth = NewObject<FPlayFabAuthentication>();
    PlayFabAuth->LoginWithCustomID(CustomID);
    return PlayFabAuth;
#endif // WITH_PLAYFAB
}

void USymplLoginFunctions::InitializePlayFab()
{
    UPlayFabRuntimeSettings* settings = GetMutableDefault<UPlayFabRuntimeSettings>();

    //Set the PlayFab Title ID.
    settings->TitleId = USymplLoginFunctions::GetPlayFabTitleID();

    // Set the server URL to use.
    FString url = USymplLoginFunctions::GetPlayFabProductionEnvironmentURL();
    if (!url.IsEmpty())
        settings->ProductionEnvironmentURL = url;

    //settings->SecretKey = GetPlayFabSecretKey();

    //PlayFabClientPtr clientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

    //clientAPI->SetCredentials(GetPlayFabTitleID(), GetPlayFabSecretKey());

}
