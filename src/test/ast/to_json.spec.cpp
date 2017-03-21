#include <comp/ast/to_json.h>
#include <comp/ast.h>
#include <comp/eval.h>
#include <gtest/gtest.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace comp {
namespace ast {
TEST(comp__ast__to_json, EmptyProgram) {
  std::unique_ptr<Program> program = Program::Create(std::vector<std::shared_ptr<Declaration>>());

  std::unique_ptr<rapidjson::Document> document = ProgramToJson(*program);
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  document->Accept(writer);
  std::string actual = buffer.GetString();

  std::string expected = "{\"node_type\":\"Program\",\"body\":[]}";

  EXPECT_EQ(expected, actual);
}

TEST(comp__ast__to_json, EmptyMain) {
  std::vector<std::shared_ptr<Declaration>> program_body;
  program_body.push_back(Function::Create(
    Identifier::Create("main"),
    std::vector<std::shared_ptr<Parameter>>(),
    LiteralDataType::Create(Identifier::Create("int64_t")),
    BlockStatement::Create(std::vector<std::shared_ptr<Statement>>())
  ));
  std::unique_ptr<Program> program = Program::Create(program_body);

  std::unique_ptr<rapidjson::Document> document = ProgramToJson(*program);
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  document->Accept(writer);
  std::string actual = buffer.GetString();

  std::string expected = "{\"node_type\":\"Program\",\"body\":[{\"node_type\":\"Function\",\"return_type\":{\"node_type\":\"LiteralDataType\",\"identifier\":{\"node_type\":\"Identifier\",\"name\":\"int64_t\"}},\"parameters\":[],\"body\":{\"node_type\":\"BlockStatement\",\"body\":[]}}]}";

  EXPECT_EQ(expected, actual);
}
}  // namespace ast
}  // namespace comp
