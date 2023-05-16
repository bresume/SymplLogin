// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Determines how the user logs into the game.
 */
UENUM(BlueprintType,Blueprintable)
enum class ESymplLoginBackendType : uint8
{
	ENONE UMETA(DisplayName = "None", Tooltip = "No login will happen."),
	EPLAYFAB UMETA(DisplayName = "Playfab", Tooltip = "Login using playfab"),
	ECUSTOM UMETA(DisplayName = "Custom", Tooltip = "Login using a custom method. Currently not supported.")
};