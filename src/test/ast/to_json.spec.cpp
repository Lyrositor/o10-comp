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

  std::string expected = "{\"node_type\":\"Program\",\"body\":[]}";
  std::string actual = buffer.GetString();

  EXPECT_EQ(expected, actual);
}
}  // namespace ast
}  // namespace comp
