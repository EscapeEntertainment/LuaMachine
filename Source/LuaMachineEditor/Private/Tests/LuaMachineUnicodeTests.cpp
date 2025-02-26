// Copyright 2025 - Roberto De Ioris

#if WITH_DEV_AUTOMATION_TESTS
#include "Tests/LuaUnitTestState.h"
#include "LuaBlueprintFunctionLibrary.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLuaMachineUnicodeTest_Simple, "LuaMachine.UnitTests.Unicode.Simple", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLuaMachineUnicodeTest_Simple::RunTest(const FString& Parameters)
{
	UWorld* TestWorld = UWorld::CreateWorld(EWorldType::Inactive, false);

	ULuaUnitTestState* UnitTestState = ULuaState::CreateDynamicLuaState<ULuaUnitTestState>(TestWorld);

	FLuaValue LuaValue = UnitTestState->RunString("return utf8.char(8704, 8712)", "");

	TestTrue(TEXT("LuaValue.String == 17"), ULuaBlueprintFunctionLibrary::LuaValueToUTF8(LuaValue) == TEXT("\u2200\u2208"));

	return true;
}

#endif