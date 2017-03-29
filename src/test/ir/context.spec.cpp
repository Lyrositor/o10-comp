#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"
#include <memory>
#include <string>
#include <comp/ir/context.h>
#include <comp/ir/variable.h>
#include <comp/ir/data_type.h>
#include <comp/ir/builtins.h>

TEST(comp__ir__context, registerAndResolveVariable) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::Create();
  std::shared_ptr<comp::ir::Variable> variable =
    comp::ir::Variable::Create(comp::ir::GetInt64Type());
  std::string varName = "varName";
  context->RegisterVariable(varName, variable);
  EXPECT_EQ(variable, context->ResolveVariable(varName));
}

TEST(comp__ir__context, registerAndResolveDataType) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::Create();
  std::shared_ptr<comp::ir::DataType> dataType =
    comp::ir::Int32DataType::Create();
  std::string typeName = "int32_t";
  context->RegisterDataType(typeName, dataType);
  EXPECT_EQ(dataType, context->ResolveDataType(typeName));
}

// TODO: registerAndResolveFunction

TEST(comp__ir__context, throwWhenResolvingUnknownVariable) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::Create();
  ASSERT_THROW(context->ResolveVariable("unknownVariable"), std::runtime_error);
}

TEST(comp__ir__context, throwWhenResolvingUnknownDataType) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::Create();
  ASSERT_THROW(context->ResolveVariable("unknownDataType"), std::runtime_error);
}

TEST(comp__ir__context, throwWhenResolvingUnknownFunction) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::Create();
  ASSERT_THROW(context->ResolveVariable("unknownFunction"), std::runtime_error);
}

TEST(comp__ir__context, registerThenForkAndResolveVariable) {
  std::shared_ptr<comp::ir::Context> parentContext =
    comp::ir::RootContext::Create();
  std::shared_ptr<comp::ir::Variable> parentVariable =
    comp::ir::Variable::Create(comp::ir::GetInt64Type());
  std::string parentVarName = "parentVar";
  parentContext->RegisterVariable(parentVarName, parentVariable);
  std::unique_ptr<comp::ir::Context> childContext = parentContext->Fork();
  std::shared_ptr<comp::ir::Variable> childVariable =
    comp::ir::Variable::Create(comp::ir::GetInt64Type());
  std::string childVarName = "childVar";
  childContext->RegisterVariable(childVarName, childVariable);

  EXPECT_EQ(parentVariable, childContext->ResolveVariable(parentVarName));
  EXPECT_EQ(childVariable, childContext->ResolveVariable(childVarName));
  EXPECT_EQ(parentVariable, parentContext->ResolveVariable(parentVarName));
  ASSERT_THROW(parentContext->ResolveVariable(childVarName), std::runtime_error);
  EXPECT_NE(parentVariable, childVariable);
}

TEST(comp__ir__context, registerWithShadowing) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::Create();
  std::shared_ptr<comp::ir::Variable> variable1 =
    comp::ir::Variable::Create(comp::ir::GetInt64Type());
  std::string varName = "varName";
  context->RegisterVariable(varName, variable1);
  EXPECT_EQ(variable1, context->ResolveVariable(varName));
  std::shared_ptr<comp::ir::Variable> variable2 =
    comp::ir::Variable::Create(comp::ir::GetInt64Type());
  context->RegisterVariable(varName, variable2);
  EXPECT_EQ(variable2, context->ResolveVariable(varName));
  EXPECT_NE(variable1, variable2);
}

TEST(comp__ir__context, registerWithForkedShadowing) {
  std::shared_ptr<comp::ir::Context> parentContext =
    comp::ir::RootContext::Create();
  std::shared_ptr<comp::ir::Variable> parentVariable =
    comp::ir::Variable::Create(comp::ir::GetInt64Type());
  std::string varName = "varName";
  parentContext->RegisterVariable(varName, parentVariable);
  std::unique_ptr<comp::ir::Context> childContext = parentContext->Fork();
  std::shared_ptr<comp::ir::Variable> childVariable =
    comp::ir::Variable::Create(comp::ir::GetInt64Type());
  childContext->RegisterVariable(varName, childVariable);

  EXPECT_EQ(childVariable, childContext->ResolveVariable(varName));
  EXPECT_EQ(parentVariable, parentContext->ResolveVariable(varName));
  EXPECT_NE(parentVariable, childVariable);
}

// Checks that you can collect all the registered variables when performing a fork & join.
TEST(comp__ir__context, forkAndJoin) {
  std::shared_ptr<comp::ir::Context> parentContext =
    comp::ir::RootContext::Create();
  std::shared_ptr<const comp::ir::Variable> parentVariable1 =
    comp::ir::Variable::Create(comp::ir::GetInt64Type(), nullptr);
  std::string parentVarName = "parentVar";
  parentContext->RegisterVariable(parentVarName, parentVariable1);
  std::unique_ptr<comp::ir::ChildContext> childContext = parentContext->Fork();
  std::shared_ptr<const comp::ir::Variable> childVariable =
    comp::ir::Variable::Create(comp::ir::GetInt64Type());
  std::string childVarName = "childVar";
  childContext->RegisterVariable(childVarName, childVariable);
  std::shared_ptr<const comp::ir::Variable> anonymousVar =
    childContext->CreateVariable(comp::ir::GetInt32Type(), nullptr);
  parentContext->Join(std::move(childContext));
  std::shared_ptr<const comp::ir::Variable> parentVariable2 =
    comp::ir::Variable::Create(comp::ir::GetInt32Type());
  parentContext->RegisterVariable(parentVarName, parentVariable2);

  std::set<std::shared_ptr<const comp::ir::Variable>> expectedVariables;
  expectedVariables.insert(parentVariable1);
  expectedVariables.insert(childVariable);
  expectedVariables.insert(anonymousVar);
  expectedVariables.insert(parentVariable2);

  std::set<std::shared_ptr<const comp::ir::Variable>> actualVariables =
    parentContext->GetVariables();

  EXPECT_THAT(actualVariables, testing::ContainerEq(expectedVariables));
}
