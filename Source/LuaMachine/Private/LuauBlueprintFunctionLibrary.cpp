// Copyright 2018-2025 - Roberto De Ioris


#include "LuauBlueprintFunctionLibrary.h"

#if LUAMACHINE_LUAU
#undef check
#include "ThirdParty/luau/Analysis.h"
#define check(expr) UE_CHECK_IMPL(expr)
#endif

bool ULuauBlueprintFunctionLibrary::LuauAnalyze(const FString& Code, const FString& ModuleName, const bool bLint, TArray<FString>& Messages)
{
#if LUAMACHINE_LUAU
	return true;
#else
	UE_LOG(LogLuaMachine, Error, TEXT("The current Lua VM is not Luau, Analyzer cannot be used"));
	return false;
#endif
}

bool ULuauBlueprintFunctionLibrary::LuauAnalyzeLuaCode(ULuaCode* LuaCode, const FString& ModuleName, const bool bLint, TArray<FString>& Messages)
{
#if LUAMACHINE_LUAU
	return true;
#else
	UE_LOG(LogLuaMachine, Error, TEXT("The current Lua VM is not Luau, Analyzer cannot be used"));
	return false;
#endif
}