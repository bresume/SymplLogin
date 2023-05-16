#include "AuthenticationBase.h"

void UAuthenticationBase::OnPlayFabLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result)
{
    NotifyOnLoginSuccess.Broadcast(FAuthenticationHandler(Result));
}

void UAuthenticationBase::OnPlayFabLoginFailure(const PlayFab::FPlayFabCppError& Error)
{
    NotifyOnLoginFailed.Broadcast(FAuthenticationHandler(Error));
}
