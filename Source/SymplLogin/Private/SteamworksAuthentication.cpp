#include "SteamworksAuthentication.h"
#include "OnlineSubsystemUtils.h"

#include "SymplLoginFunctions.h"

#if WITH_STEAMWORKS && WITH_PLAYFAB


#include "Core/PlayFabClientAPI.h"
#include "PlayFabAuthentication.h"

void FSteamworksAuthentication::Login(FString Username, FString Password)
{
    // Get the OnlineSubsystem module
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get OnlineSubsystem module."));
        NotifyOnLoginFailed.Broadcast(FAuthenticationHandler(5));
        return;
    }

    // Get the Steam subsystem
    IOnlineSubsystem* SteamSubsystem = OnlineSubsystem->Get(FName("Steam"));
    if (SteamSubsystem == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get Steam subsystem."));
        NotifyOnLoginFailed.Broadcast(FAuthenticationHandler(6));
        return;
    }

    // Get the user login state
    IOnlineIdentityPtr IdentityInterface = SteamSubsystem->GetIdentityInterface();
    if (IdentityInterface == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get identity interface."));
        NotifyOnLoginFailed.Broadcast(FAuthenticationHandler(7));
        return;
    }

    TSharedPtr<const FUniqueNetId> UserId = IdentityInterface->GetUniquePlayerId(0);
    if (!UserId.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get user id."));
        NotifyOnLoginFailed.Broadcast(FAuthenticationHandler(8));
        return;
    }

    // Get the Steam authentication ticket
    FString AuthTicket = IdentityInterface->GetAuthToken(0);

    if (AuthTicket.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get Steam authentication ticket."));
        NotifyOnLoginFailed.Broadcast(FAuthenticationHandler(9));
        return;
    }

    // Use the PlayFab Client API to authenticate the user

    PlayFabClientPtr clientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

    PlayFab::ClientModels::FLoginWithSteamRequest Request;
    Request.CreateAccount = true;
    Request.TitleId = USymplLoginFunctions::GetPlayFabTitleID();
    Request.SteamTicket = TCHAR_TO_UTF8(*AuthTicket);

    if (clientAPI)
    {
        PlayFab::UPlayFabClientAPI::FLoginWithSteamDelegate SuccessDelegate;
        SuccessDelegate.BindUObject(this, &FSteamworksAuthentication::OnPlayFabLoginSuccess);

        PlayFab::FPlayFabErrorDelegate ErrorDelegate;
        ErrorDelegate.BindUObject(this, &FSteamworksAuthentication::OnPlayFabLoginFailure);

        clientAPI->LoginWithSteam(Request, SuccessDelegate, ErrorDelegate);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get PlayFab subsystem."));
        NotifyOnLoginFailed.Broadcast(FAuthenticationHandler(10));
    }
}

#endif // WITH_STEAMWORKS && WITH_PLAYFAB

