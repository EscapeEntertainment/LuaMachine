// Copyright 2018-2025 - Roberto De Ioris

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LuaCode.h"
#include "LuauBlueprintFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FLuauAnalysisResult
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Luau")
	int32 StartLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Luau")
	int32 StartColumn;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Luau")
	int32 EndLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Luau")
	int32 EndColumn;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Luau")
	FString Message;
};

/**
 * 
 */
UCLASS()
class LUAMACHINE_API ULuauBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Luau")
	static bool LuauAnalyze(const FString& Code, const FString& ModuleName, const bool bLint, TArray<FLuauAnalysisResult>& Results);
	
	UFUNCTION(BlueprintCallable, Category="Luau")
	static bool LuauAnalyzeLuaCode(ULuaCode* LuaCode, const FString& ModuleName, const bool bLint, TArray<FLuauAnalysisResult>& Results);
};
