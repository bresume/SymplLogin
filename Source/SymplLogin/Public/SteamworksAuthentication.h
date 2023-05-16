#pragma once

#include "CoreMinimal.h"
#include "AuthenticationBase.h"

UENUM(BlueprintType)
enum class ESteamAuthResponseCode : uint8
{
    Success,
    Failed,
    Canceled
};

#if WITH_STEAMWORKS

#include "steam/steam_api.h"

class FSteamworksAuthentication : public UAuthenticationBase
{
public:
    virtual void Login(FString Username = "", FString Password = "") override;

private:
    FDelegateHandle AuthTicketResponseHandle;
};

#endif // WITH_STEAMWORKS
