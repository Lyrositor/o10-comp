#include <comp/ast/to_json.h>

namespace comp {
namespace ast {
std::unique_ptr<rapidjson::Document> ProgramToJson(const Program &node) {
  std::unique_ptr<rapidjson::Document> result(new rapidjson::Document());
  rapidjson::Document &document = *result;
  document.SetObject();
  document.AddMember("node_type", "program", document.GetAllocator());
  return result;
}
}  // namespace ast
}  // namespace comp
