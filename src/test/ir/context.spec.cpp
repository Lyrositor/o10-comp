#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"
#include <memory>
#include <string>
#include <comp/ir/context.h>
#include <comp/ir/variable.h>
#include <comp/ir/data_type.h>

TEST(comp__ir__context, registerAndResolveVariable) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::create();
  std::shared_ptr<comp::ir::Variable> variable = comp::ir::Variable::create(comp::ir::int64Type);
  std::string varName = "varName";
  context->registerVariable(varName, variable);
  EXPECT_EQ(variable, context->resolveVariable(varName));
}

TEST(comp__ir__context, registerAndResolveDataType) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::create();
  std::shared_ptr<comp::ir::DataType> dataType = comp::ir::PrimitiveDataType::create(2);
  std::string typeName = "int16_t";
  context->registerDataType(typeName, dataType);
  EXPECT_EQ(dataType, context->resolveDataType(typeName));
}

// TODO: registerAndResolveFunction

TEST(comp__ir__context, throwWhenResolvingUnknownVariable) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::create();
  ASSERT_THROW(context->resolveVariable("unknownVariable"), std::runtime_error);
}

TEST(comp__ir__context, throwWhenResolvingUnknownDataType) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::create();
  ASSERT_THROW(context->resolveVariable("unknownDataType"), std::runtime_error);
}

TEST(comp__ir__context, throwWhenResolvingUnknownFunction) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::create();
  ASSERT_THROW(context->resolveVariable("unknownFunction"), std::runtime_error);
}

TEST(comp__ir__context, registerThenForkAndResolveVariable) {
  std::shared_ptr<comp::ir::Context> parentContext = comp::ir::RootContext::create();
  std::shared_ptr<comp::ir::Variable> parentVariable = comp::ir::Variable::create(comp::ir::int64Type);
  std::string parentVarName = "parentVar";
  parentContext->registerVariable(parentVarName, parentVariable);
  std::unique_ptr<comp::ir::Context> childContext = parentContext->fork();
  std::shared_ptr<comp::ir::Variable> childVariable = comp::ir::Variable::create(comp::ir::int64Type);
  std::string childVarName = "childVar";
  childContext->registerVariable(childVarName, childVariable);

  EXPECT_EQ(parentVariable, childContext->resolveVariable(parentVarName));
  EXPECT_EQ(childVariable, childContext->resolveVariable(childVarName));
  EXPECT_EQ(parentVariable, parentContext->resolveVariable(parentVarName));
  ASSERT_THROW(parentContext->resolveVariable(childVarName), std::runtime_error);
  EXPECT_NE(parentVariable, childVariable);
}

TEST(comp__ir__context, registerWithShadowing) {
  std::unique_ptr<comp::ir::Context> context = comp::ir::RootContext::create();
  std::shared_ptr<comp::ir::Variable> variable1 = comp::ir::Variable::create(comp::ir::int64Type);
  std::string varName = "varName";
  context->registerVariable(varName, variable1);
  EXPECT_EQ(variable1, context->resolveVariable(varName));
  std::shared_ptr<comp::ir::Variable> variable2 = comp::ir::Variable::create(comp::ir::int64Type);
  context->registerVariable(varName, variable2);
  EXPECT_EQ(variable2, context->resolveVariable(varName));
  EXPECT_NE(variable1, variable2);
}

TEST(comp__ir__context, registerWithForkedShadowing) {
  std::shared_ptr<comp::ir::Context> parentContext = comp::ir::RootContext::create();
  std::shared_ptr<comp::ir::Variable> parentVariable = comp::ir::Variable::create(comp::ir::int64Type);
  std::string varName = "varName";
  parentContext->registerVariable(varName, parentVariable);
  std::unique_ptr<comp::ir::Context> childContext = parentContext->fork();
  std::shared_ptr<comp::ir::Variable> childVariable = comp::ir::Variable::create(comp::ir::int64Type);
  childContext->registerVariable(varName, childVariable);

  EXPECT_EQ(childVariable, childContext->resolveVariable(varName));
  EXPECT_EQ(parentVariable, parentContext->resolveVariable(varName));
  EXPECT_NE(parentVariable, childVariable);
}

// Checks that you can collect all the registered variables when performing a fork & join.
TEST(comp__ir__context, forkAndJoin) {
  std::shared_ptr<comp::ir::Context> parentContext = comp::ir::RootContext::create();
  std::shared_ptr<comp::ir::Variable> parentVariable1 = comp::ir::Variable::create(comp::ir::int64Type);
  std::string parentVarName = "parentVar";
  parentContext->registerVariable(parentVarName, parentVariable1);
  std::unique_ptr<comp::ir::ChildContext> childContext = parentContext->fork();
  std::shared_ptr<comp::ir::Variable> childVariable = comp::ir::Variable::create(comp::ir::int64Type);
  std::string childVarName = "childVar";
  childContext->registerVariable(childVarName, childVariable);
  std::shared_ptr<comp::ir::Variable> anonymousVar = childContext->createVariable(comp::ir::int32Type);
  parentContext->join(std::move(childContext));
  std::shared_ptr<comp::ir::Variable> parentVariable2 = comp::ir::Variable::create(comp::ir::int32Type);
  parentContext->registerVariable(parentVarName, parentVariable2);

  std::set<std::shared_ptr<comp::ir::Variable>> expectedVariables;
  expectedVariables.insert(parentVariable1);
  expectedVariables.insert(childVariable);
  expectedVariables.insert(anonymousVar);
  expectedVariables.insert(parentVariable2);

  std::set<std::shared_ptr<comp::ir::Variable>> actualVariables = parentContext->getVariables();

  EXPECT_THAT(actualVariables, testing::ContainerEq(expectedVariables));
}
