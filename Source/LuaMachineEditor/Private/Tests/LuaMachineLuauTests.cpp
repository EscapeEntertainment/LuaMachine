// Copyright 2025 - Roberto De Ioris

#if WITH_DEV_AUTOMATION_TESTS
#include "Tests/LuaUnitTestState.h"
#include "LuauBlueprintFunctionLibrary.h"
#include "Misc/AutomationTest.h"

#if LUAMACHINE_LUAU

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLuaMachineLuauTest_AnalyzeSimple, "LuaMachine.UnitTests.Luau.AnalyzeSimple", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLuaMachineLuauTest_AnalyzeSimple::RunTest(const FString& Parameters)
{
	TArray<FString> Errors;
	const bool bCodeCheck = ULuauBlueprintFunctionLibrary::LuauAnalyze("slocal actor = require(hey)", "HelloWorld", true, Errors);

	TestTrue(TEXT("bCodeCheck == false"), !bCodeCheck);

	return true;
}

#endif

#endif