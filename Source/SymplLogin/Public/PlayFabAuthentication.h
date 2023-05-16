#pragma once

#include "CoreMinimal.h"
#include "AuthenticationBase.h"

#if WITH_PLAYFAB

#include "PlayFab.h"
#include "Core/PlayFabError.h"
#include "Core/PlayFabClientDataModels.h"

class FPlayFabAuthentication : public UAuthenticationBase
{
public:

    virtual void Login(FString Username = "", FString Password = "") override;

    void LoginWithCustomID(FString CustomID);

private:

    bool LoginWithPlatform(const FString& Platform);
    void LoginWithUsernamePassword(const FString& Username = "", const FString& Password = "");
};

#endif // WITH_PLAYFAB
