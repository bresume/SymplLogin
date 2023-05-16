// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SymplLoginGameInstanceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType,Blueprintable)
class USymplLoginGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for SymplLogin plugin.
 * Should be placed in the Game Instance.
 */
class SYMPLLOGIN_API ISymplLoginGameInstanceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * Set playfab custom ID.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Login")
		bool SetUserPlayfabCustomID(const FString& InCustomID);

	/**
	 * Get playfab custom ID.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Login")
		FString GetUserPlayfabCustomID();


};
