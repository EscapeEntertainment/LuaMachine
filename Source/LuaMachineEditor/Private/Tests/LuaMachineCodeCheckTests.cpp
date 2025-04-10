// Copyright 2025 - Roberto De Ioris

#if WITH_DEV_AUTOMATION_TESTS
#include "Tests/LuaUnitTestState.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLuaMachineCodeCheckTest_Simple, "LuaMachine.UnitTests.CodeCheck.Simple", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLuaMachineCodeCheckTest_Simple::RunTest(const FString& Parameters)
{
	UWorld* TestWorld = UWorld::CreateWorld(EWorldType::Inactive, false);

	ULuaUnitTestState* UnitTestState = ULuaState::CreateDynamicLuaState<ULuaUnitTestState>(TestWorld);

	TArray<FString> Errors;
	const bool bCodeCheck = UnitTestState->LuaCodeCheck("local actor = require(hey)", "HelloWorld", Errors);

	TestTrue(TEXT("bCodeCheck == false"), !bCodeCheck);

	return true;
}

#endif