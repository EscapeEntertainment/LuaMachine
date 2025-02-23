// Copyright 2025 - Roberto De Ioris

#if WITH_DEV_AUTOMATION_TESTS
#include "Tests/LuaUnitTestState.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLuaMachineStateTest_Integer, "LuaMachine.UnitTests.State.Integer", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLuaMachineStateTest_Integer::RunTest(const FString& Parameters)
{
	UWorld* TestWorld = UWorld::CreateWorld(EWorldType::Inactive, false);

	ULuaUnitTestState* UnitTestState = ULuaState::CreateDynamicLuaState<ULuaUnitTestState>(TestWorld);

	FLuaValue LuaValue = UnitTestState->RunString("return 1 + 1", "");

	TestTrue(TEXT("LuaValue.Integer == 2"), LuaValue.Integer == 2);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLuaMachineStateTest_String, "LuaMachine.UnitTests.State.String", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLuaMachineStateTest_String::RunTest(const FString& Parameters)
{
	UWorld* TestWorld = UWorld::CreateWorld(EWorldType::Inactive, false);

	ULuaUnitTestState* UnitTestState = ULuaState::CreateDynamicLuaState<ULuaUnitTestState>(TestWorld);

	FLuaValue LuaValue = UnitTestState->RunString("return \"lua\"", "");

	TestTrue(TEXT("LuaValue.String == \"lua\""), LuaValue.String == "lua");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLuaMachineStateTest_Call, "LuaMachine.UnitTests.State.Call", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLuaMachineStateTest_Call::RunTest(const FString& Parameters)
{
	UWorld* TestWorld = UWorld::CreateWorld(EWorldType::Inactive, false);

	ULuaUnitTestState* UnitTestState = ULuaState::CreateDynamicLuaState<ULuaUnitTestState>(TestWorld);

	UnitTestState->RunString("testtable = { testfunction = function() return \"lua\" end }", "");

	FLuaValue LuaTestFunction = UnitTestState->GetLuaValueFromGlobalName("testtable.testfunction");

	TestTrue(TEXT("LuaValue.String == \"lua\""), UnitTestState->LuaValueCall(LuaTestFunction, {}).String == "lua");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLuaMachineStateTest_UObject, "LuaMachine.UnitTests.State.UObject", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLuaMachineStateTest_UObject::RunTest(const FString& Parameters)
{
	UWorld* TestWorld = UWorld::CreateWorld(EWorldType::Inactive, false);

	ULuaUnitTestState* UnitTestState = ULuaState::CreateDynamicLuaState<ULuaUnitTestState>(TestWorld);

	FLuaValue ComparisonFunction = UnitTestState->RunString("return function(a, b) return a == b; end", "");

	TestTrue(TEXT("LuaValue.Bool == true"), UnitTestState->LuaValueCall(ComparisonFunction, { FLuaValue(TestWorld), FLuaValue(TestWorld) }).Bool);

	return true;
}

#if LUAMACHINE_LUAU
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLuaMachineStateTest_CallTyped, "LuaMachine.UnitTests.State.CallTyped", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLuaMachineStateTest_CallTyped::RunTest(const FString& Parameters)
{
	UWorld* TestWorld = UWorld::CreateWorld(EWorldType::Inactive, false);

	ULuaUnitTestState* UnitTestState = ULuaState::CreateDynamicLuaState<ULuaUnitTestState>(TestWorld);

	UnitTestState->RunString("--!strict\ntesttable = { testfunction = function(a: number, b: number) : number return a + b end }", "");

	FLuaValue LuaTestFunction = UnitTestState->GetLuaValueFromGlobalName("testtable.testfunction");

	TestTrue(TEXT("LuaValue.String == \"lua\""), UnitTestState->LuaValueCall(LuaTestFunction, { 1, 2 }).Integer == 3);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLuaMachineStateTest_MaxMemoryUsage, "LuaMachine.UnitTests.State.MaxMemoryUsage", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLuaMachineStateTest_MaxMemoryUsage::RunTest(const FString& Parameters)
{
	UWorld* TestWorld = UWorld::CreateWorld(EWorldType::Inactive, false);

	ULuaUnitTestState* UnitTestState = ULuaState::CreateDynamicLuaState<ULuaUnitTestState>(TestWorld);

	UnitTestState->bLogError = false;

	UnitTestState->MaxMemoryUsage = 1;

	FLuaValue ReturnValue = UnitTestState->RunString("return \"xyz\"", "");

	TestTrue(TEXT("LuaState Error"), UnitTestState->LastError.Contains("MaxMemoryUsage reached"));

	return true;
}
#endif

#endif