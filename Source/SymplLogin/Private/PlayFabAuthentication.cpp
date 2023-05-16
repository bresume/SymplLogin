#include "PlayFabAuthentication.h"
#include "Kismet/GameplayStatics.h"
#include "SymplLoginFunctions.h"
#include "SteamworksAuthentication.h"
#include "Delegates/Delegate.h"

#if WITH_PLAYFAB

#include "Core/PlayFabClientAPI.h"
#include "Core/PlayFabSettings.h"
#include "PlayFabAuthenticationContext.h"

void FPlayFabAuthentication::Login(FString Username, FString Password)
{

    //Get the platform name.
    FString platform = UGameplayStatics::GetPlatformName();

    // Try to log in with the appropriate platform authentication method, or fallback to username and password.
    bool loggedIn = false;
    if (platform.ToLower().Contains("windows") || platform.ToLower().Contains("mac") || platform.ToLower().Contains("linux"))
    {
        loggedIn = LoginWithPlatform(TEXT("Steam"));
    }
    else
    {
        loggedIn = LoginWithPlatform(platform);
    }

    if (!loggedIn)
    {
        LoginWithUsernamePassword(Username, Password);
    }
}

bool FPlayFabAuthentication::LoginWithPlatform(const FString& Platform)
{
    PlayFabClientPtr clientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
    FString device = FGenericPlatformMisc::GetDeviceId();
    if (clientAPI)
    {
        if (Platform == "Steam")
        {
            FSteamworksAuthentication* steam_auth = NewObject<FSteamworksAuthentication>();
            steam_auth->Login();
            return true;
        }
        else if (Platform.ToLower().Contains("playstation"))
        {
            PlayFab::ClientModels::FLoginWithPSNRequest Request;
            Request.CreateAccount = true;
            Request.TitleId = USymplLoginFunctions::GetPlayFabTitleID();

            PlayFab::UPlayFabClientAPI::FLoginWithPSNDelegate SuccessDelegate;
            SuccessDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginSuccess);

            PlayFab::FPlayFabErrorDelegate ErrorDelegate;
            ErrorDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginFailure);

            clientAPI->LoginWithPSN(Request, SuccessDelegate, ErrorDelegate);
            return true;
        }
        else if (Platform.ToLower().Contains("android"))
        {
            PlayFab::ClientModels::FLoginWithAndroidDeviceIDRequest Request;
            Request.CreateAccount = true;
            Request.TitleId = USymplLoginFunctions::GetPlayFabTitleID();
            Request.AndroidDeviceId = device;

            // Call the PlayFab API to log in with the platform's authentication method.
            PlayFab::UPlayFabClientAPI::FLoginWithAndroidDeviceIDDelegate SuccessDelegate;
            SuccessDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginSuccess);

            PlayFab::FPlayFabErrorDelegate ErrorDelegate;
            ErrorDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginFailure);

            clientAPI->LoginWithAndroidDeviceID(Request, SuccessDelegate, ErrorDelegate);
            return true;
        }
        else if (Platform.ToLower().Contains("ios"))
        {
            PlayFab::ClientModels::FLoginWithAppleRequest Request;
            Request.CreateAccount = true;
            Request.TitleId = USymplLoginFunctions::GetPlayFabTitleID();

            // Call the PlayFab API to log in with the platform's authentication method.
            PlayFab::UPlayFabClientAPI::FLoginWithAppleDelegate SuccessDelegate;
            SuccessDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginSuccess);

            PlayFab::FPlayFabErrorDelegate ErrorDelegate;
            ErrorDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginFailure);

            clientAPI->LoginWithApple(Request, SuccessDelegate, ErrorDelegate);
            return true;
        }
        else if (Platform.ToLower().Contains("xbox"))
        {
            PlayFab::ClientModels::FLoginWithXboxRequest Request;
            Request.CreateAccount = true;
            Request.TitleId = USymplLoginFunctions::GetPlayFabTitleID();

            // Call the PlayFab API to log in with the platform's authentication method.
            PlayFab::UPlayFabClientAPI::FLoginWithXboxDelegate SuccessDelegate;
            SuccessDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginSuccess);

            PlayFab::FPlayFabErrorDelegate ErrorDelegate;
            ErrorDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginFailure);

            clientAPI->LoginWithXbox(Request, SuccessDelegate, ErrorDelegate);
            return true;
        }
        else
        {
            return false;
        }
        return false;
    }
    return false;
}

void FPlayFabAuthentication::LoginWithUsernamePassword(const FString& Username, const FString& Password)
{
    PlayFabClientPtr PlayFabClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
    if (PlayFabClientAPI)
    {
        PlayFab::ClientModels::FLoginWithPlayFabRequest Request;
        Request.Username = Username;
        Request.Password = Password;
        Request.TitleId = USymplLoginFunctions::GetPlayFabTitleID();

        PlayFab::UPlayFabClientAPI::FLoginWithEmailAddressDelegate SuccessDelegate;
        //SuccessDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginSuccess);

        PlayFab::FPlayFabErrorDelegate ErrorDelegate;
        //ErrorDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginFailure);

        PlayFabClientAPI->LoginWithPlayFab(Request, SuccessDelegate, ErrorDelegate);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get PlayFab subsystem."));
        NotifyOnLoginFailed.Broadcast(FAuthenticationHandler(10));
    }
}

void FPlayFabAuthentication::LoginWithCustomID(FString CustomID)
{
    // Create a PlayFab Client API instance
    PlayFabClientPtr clientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

    // Set up the login request
    PlayFab::ClientModels::FLoginWithCustomIDRequest Request;
    Request.CustomId = TCHAR_TO_UTF8(*CustomID);
    Request.CreateAccount = true;
    Request.TitleId = USymplLoginFunctions::GetPlayFabTitleID();

    // Call the PlayFab API to log in with the platform's authentication method.
    PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate SuccessDelegate;
    SuccessDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginSuccess);

    PlayFab::FPlayFabErrorDelegate ErrorDelegate;
    ErrorDelegate.BindUObject(this, &FPlayFabAuthentication::OnPlayFabLoginFailure);

    // Send the login request to PlayFab
    clientAPI->LoginWithCustomID(Request, SuccessDelegate, ErrorDelegate);
}

#endif
