// Copyright 2025 - Roberto De Ioris

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"
#include "LuaUnitTestState.generated.h"

/**
 *
 */
UCLASS()
class ULuaUnitTestState : public ULuaState
{
	GENERATED_BODY()

	ULuaUnitTestState()
	{
		MaxMemoryUsage = 8192;
		bLogError = true;
	}
};
