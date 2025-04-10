// Copyright 2018-2025 - Roberto De Ioris

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LuaCode.h"
#include "LuauBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LUAMACHINE_API ULuauBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Luau")
	static bool LuauAnalyze(const FString& Code, const FString& ModuleName, const bool bLint, TArray<FString>& Messages);
	
	UFUNCTION(BlueprintCallable, Category="Luau")
	static bool LuauAnalyzeLuaCode(ULuaCode* LuaCode, const FString& ModuleName, const bool bLint, TArray<FString>& Messages);
};
