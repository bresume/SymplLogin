#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayFab.h"
#include "Core/PlayFabError.h"
#include "Core/PlayFabClientDataModels.h"
#include "AuthenticationBase.generated.h"

/**
 * Wrapper for authentication errors.
*/
USTRUCT(BlueprintType,Blueprintable)
struct FAuthenticationHandler
{

    GENERATED_BODY()

public: 

    UPROPERTY()
        FString Error;

    UPROPERTY()
        int32 ErrorCode;

    UPROPERTY()
        bool bWasSuccessful;

    FString ToString()
    {
        FString str = bWasSuccessful ? "Authentication Success! \n    " : "Authentication Failed! \n    ";
        str += Error;
        str += "\n  Error Code = " + FString::FromInt(ErrorCode);
        return str;
    }

    FAuthenticationHandler()
    {
        Error = "Success!";
        ErrorCode = 0;
        bWasSuccessful = true;
    }

    FAuthenticationHandler(FString InError, int32 InCode, bool InSuccess)
    {
        Error = InError;
        ErrorCode = InCode;
        bWasSuccessful = InSuccess;
    }

    FAuthenticationHandler(int32 InCode)
    {
        ErrorCode = InCode;
        switch (ErrorCode)
        {
        case 0 :
            Error = "Success!";
            bWasSuccessful = true;
        case 1:
            Error = "Success!";
            bWasSuccessful = false;
        case 2:
            Error = "Success!";
            bWasSuccessful = false;
        case 3:
            Error = "Success!";
            bWasSuccessful = false;
        case 4:
            Error = "Success!";
            bWasSuccessful = false;
        case 5:
            Error = "Failed to get OnlineSubsystem module.";
            bWasSuccessful = false;
        case 6:
            Error = "Failed to get Steam subsystem.";
            bWasSuccessful = false;
        case 7:
            Error = "Failed to get identity interface.";
            bWasSuccessful = false;
        case 8:
            Error = "Failed to get user id.";
            bWasSuccessful = false;
        case 9:
            Error = "Failed to get Steam authentication ticket.";
            bWasSuccessful = false;
        case 10:
            Error = "Failed to get PlayFab subsystem.";
            bWasSuccessful = false;
        }
    }

    FAuthenticationHandler(const PlayFab::ClientModels::FLoginResult& PlayFabResult)
    {
        bWasSuccessful = true;
        ErrorCode = 0;
        Error = "PlayFab Login Successful!\n    ";
        //Error += "Last Login Time = " + PlayFabResult.LastLoginTime.ToIso8601() + "\n    ";
        Error += PlayFabResult.NewlyCreated ? "Is Newly Created\n    " : "Not Newly Created\n    ";
        //Error += "PlayFabID = " + PlayFabResult.PlayFabID + "\n    ";
        Error += "SessionTicket = " + PlayFabResult.SessionTicket;
    }

    FAuthenticationHandler(const PlayFab::FPlayFabCppError& PlayFabError)
    {
        ErrorCode = PlayFabError.ErrorCode;
        bWasSuccessful = false;
        Error = "PlayFab Login Failed!\n    ";
        //Error += "HttpCode = " + PlayFabError.HttpCode + "\n    ";
        Error += "ErrorName: " + PlayFabError.ErrorName + "\n    ";
        Error += "ErrorMessage = " + PlayFabError.ErrorMessage + "\n    ";
        Error += "ErrorDetails = \n    ";
        /*
        for (auto It = PlayFabError.ErrorDetails.CreateConstIterator(); It; ++It)
        {
            Error += It->Key + ":" + It->Value + "\n    ";
        }
        */
    }

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyOnLoginSuccessDelegate,const FAuthenticationHandler&, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyOnLoginFailedDelegate,const FAuthenticationHandler&, Response);


/**
 * Base object for handling authentication.
*/
UCLASS(Blueprintable, BlueprintType)
class SYMPLLOGIN_API UAuthenticationBase : public UObject
{
    GENERATED_BODY()

public:
    virtual void Login(FString Username = "", FString Password = "") {}

    UPROPERTY(BlueprintAssignable, Category = "Authentication|Event")
        FNotifyOnLoginSuccessDelegate NotifyOnLoginSuccess;

    UPROPERTY(BlueprintAssignable, Category = "Authentication|Event")
        FNotifyOnLoginFailedDelegate NotifyOnLoginFailed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Authentication")
        FAuthenticationHandler AuthHandle;

protected:

    virtual void OnPlayFabLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result);
    virtual void OnPlayFabLoginFailure(const PlayFab::FPlayFabCppError& Error);
};

