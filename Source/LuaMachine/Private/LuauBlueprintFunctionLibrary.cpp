// Copyright 2018-2025 - Roberto De Ioris


#include "LuauBlueprintFunctionLibrary.h"

#if LUAMACHINE_LUAU
#undef check
#include "ThirdParty/luau/Luau/Frontend.h"
#define check(expr) UE_CHECK_IMPL(expr)
#include "ThirdParty/luau/Luau/BuiltinDefinitions.h"
#endif

bool ULuauBlueprintFunctionLibrary::LuauAnalyze(const FString& Code, const FString& ModuleName, const bool bLint, TArray<FString>& Messages)
{
#if LUAMACHINE_LUAU
	Luau::FrontendOptions FrontendOptions;
	FrontendOptions.runLintChecks = true;

	Luau::NullConfigResolver NullConfigResolver;

	struct LuaMachineLuauFileResolver : Luau::FileResolver
	{
		LuaMachineLuauFileResolver(const FString& InCode) : Code(InCode)
		{
		}

		std::optional<Luau::SourceCode> readSource(const Luau::ModuleName& Name) override
		{
			return Luau::SourceCode{TCHAR_TO_UTF8(*Code), Luau::SourceCode::Script};
		}

		const FString Code;
	};

	LuaMachineLuauFileResolver FileResolver(Code);

	Luau::Frontend Frontend(&FileResolver, &NullConfigResolver, FrontendOptions);
	Luau::registerBuiltinGlobals(Frontend, Frontend.globals);
	Luau::freeze(Frontend.globals.globalTypes);

	Frontend.parse(TCHAR_TO_UTF8(*ModuleName));
#undef check
	Luau::CheckResult Result = Frontend.check(TCHAR_TO_UTF8(*ModuleName));
#define check(expr) UE_CHECK_IMPL(expr)

	for (const Luau::TypeError& LuaTypeError : Result.errors)
	{
		UE_LOG(LogTemp, Error, TEXT("ULuaState::LuaCodeCheck %d %d %d %d [%s]"), LuaTypeError.location.begin.line, LuaTypeError.location.begin.column,
			   LuaTypeError.location.end.line,
			   LuaTypeError.location.end.column, UTF8_TO_TCHAR(Luau::toString(LuaTypeError, Luau::TypeErrorToStringOptions{Frontend.fileResolver}).c_str()));
	}
	return Messages.Num() == 0;
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