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
public:

	ULuaUnitTestState()
	{
		MaxMemoryUsage = 8192;
		bLogError = true;
		StepCount = 0;
	}

	void ReceiveLuaSingleStepHook_Implementation(const FLuaDebug& LuaDebug) override
	{
		StepCount++;
	}

	int32 StepCount;
};
