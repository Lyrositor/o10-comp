# This script visits each sub-directory in `end-to-end` and compiles its source file.
# Currently it only compiles with GCC and clang but the goal is to also run our compiler and check
# the output.


import json
import os
import subprocess
from typing import Set, Tuple

END_TO_END_ROOT: str = os.path.dirname(os.path.realpath(__file__))
PROJECT_ROOT: str = os.path.join(END_TO_END_ROOT, "..")
CONFIG_FILE_NAME = "test.json"


class Compiler:
    def __init__(self, name: str, path: str):
        self.name = name
        self.path = path

    def generate_assembly(self, directory, source_path):
        pass


clang: Compiler = Compiler("clang", "clang")
gcc: Compiler = Compiler("g++", "g++")
o10: Compiler = Compiler("o10", os.path.join(PROJECT_ROOT, "build", "comp_main"))

DEFAULT_ASSEMBLY_GENERATION_CONFIGURATIONS = {
    "gcc-0": (gcc, ["-S", "-O0"]),
    "gcc-1": (gcc, ["-S", "-O1"]),
    "gcc-2": (gcc, ["-S", "-O2"]),
    "gcc-3": (gcc, ["-S", "-O3"]),
    "clang-0": (clang, ["-S", "-O0", "-Wno-main-return-type"]),
    "clang-1": (clang, ["-S", "-O1", "-Wno-main-return-type"]),
    "clang-2": (clang, ["-S", "-O2", "-Wno-main-return-type"]),
    "clang-3": (clang, ["-S", "-O3", "-Wno-main-return-type"]),
}

ERRORS_ENUM = {"syntax"}


class TestConfig():
    def __init__(self):
        self.disabled: bool = False
        self.source_path: str = None
        self.expect_error: str = None  # One of: {"syntax"}
        self.name: str = None
        # Only displayed if an error occurs, should explain the goal of test-case
        self.description: str = None

        self.test_ast: bool = False
        self.expected_ast_path: str = None
        self.actual_ast_path: str = None

        self.generate_assembly: bool = False
        self.assembly_generation_configs = []

    def from_json(input: str, test_dir: str) -> 'TestConfig':
        doc = json.loads(input)
        config = TestConfig()

        config.disabled = "disabled" in doc and doc["disabled"]
        if "source" in doc:
            config.source_path = os.path.join(test_dir, doc["source"])
        else:
            raise Exception("Missing required property `source`")
        if "error" in doc and doc["error"] is not None:
            config.expect_error = doc["error"]
            if config.expect_error not in ERRORS_ENUM:
                raise Exception("Invalid value for `error` ({}), expected one of: {}"
                                .format(doc["error"], ", ".join(ERRORS_ENUM)))

        if "expected-ast" in doc and doc["expected-ast"] is not None:
            config.test_ast = True
            config.expected_ast_path = os.path.join(test_dir, doc["expected-ast"])
        if "actual-ast" in doc:
            config.actual_ast_path = os.path.join(test_dir, doc["actual-ast"])

        if "assembly" in doc:
            if type(doc["assembly"]) == bool and doc["assembly"]:
                config.generate_assembly = True
                config.assembly_generation_configs = DEFAULT_ASSEMBLY_GENERATION_CONFIGURATIONS
            elif type(doc["assembly"]) == list:
                config.generate_assembly = True
                raise NotImplementedError("Custom assembly generation options")

        return config


class TestCase:
    def __init__(self, dir: str):
        self.dir = dir
        with open(os.path.join(dir, CONFIG_FILE_NAME), "r") as config_file:
            self.config = TestConfig.from_json(config_file.read(), dir)

    def run(self):
        if self.config.disabled:
            return {"ast": ("disabled", None)}
        else:
            return {"ast": self.run_ast()}

    def run_ast(self):
        if self.config.disabled:
            return "disabled", None
        if not self.config.test_ast and self.config.actual_ast_path is None:
            return "hidden", None

        completed_process = subprocess.run(
            [o10.path, self.config.source_path],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )

        stdout = completed_process.stdout.decode('utf-8')
        stderr = completed_process.stderr.decode('utf-8')

        if completed_process.returncode != 0:
            if self.config.expect_error == "syntax":
                return "success", None
            else:
                msg = ("Unable to generate AST:\n"
                       "stdout:\n"
                       "{}\n"
                       "stderr:\n"
                       "{}"
                       ).format(stdout, stderr)
                return "error", msg

        try:
            actual_ast_doc = json.loads(stdout)
        except json.decoder.JSONDecodeError as err:
            msg = ("Unable to parse compiler output:\n"
                   "stdout:\n"
                   "{}\n"
                   "stderr:\n"
                   "{}\n"
                   "Parse error:\n"
                   "{}"
                   ).format(stdout, stderr, err)
            return "error", msg

        if self.config.actual_ast_path is not None:
            with open(self.config.actual_ast_path, "w") as actual_ast_file:
                actual_ast_file.write(stdout)

        if self.config.test_ast:
            with open(self.config.expected_ast_path, "r") as expected_ast_file:
                expected_ast_doc = json.loads(expected_ast_file.read())
                if expected_ast_doc != actual_ast_doc:
                    msg = ("Actual AST does not match the expected AST:\n"
                           "Expected AST:\n"
                           "{}\n"
                           "Actual AST:\n"
                           "{}"
                           ).format(expected_ast_doc, actual_ast_doc)
                    return "error", msg

        return "success", None

    def run_assembly(self):
        if self.config.disabled or not self.config.generate_assembly:
            return "disabled", None


# Returns a set of directories and a set of other FS nodes
def dir_content(dir_path: str) -> Tuple[Set[str], Set[str]]:
    files: Set[str] = set()
    dirs: Set[str] = set()
    for node_name in os.listdir(dir_path):
        abs_path: str = os.path.join(dir_path, node_name)
        if os.path.isdir(abs_path):
            dirs.add(abs_path)
        else:
            files.add(abs_path)
    return files, dirs


# Yields the test cases in the provided directory
def discover_tests(tests_dir: str, recursive: bool = True):
    for fs_node in os.listdir(tests_dir):
        fs_node_path = os.path.join(tests_dir, fs_node)
        if not os.path.isdir(fs_node_path):
            continue
        test_dir_path = fs_node_path
        test_files, test_dirs = dir_content(test_dir_path)
        if os.path.join(test_dir_path, CONFIG_FILE_NAME) in test_files:
            yield TestCase(test_dir_path)
        if recursive:
            for test_dir in test_dirs:
                for test_case in discover_tests(test_dir, recursive):
                    yield test_case


test_report = []
test_messages = []

# Discover and run the tests
test_cases = list(discover_tests(END_TO_END_ROOT))
for test_case in test_cases:
    for name, (status, message) in test_case.run().items():
        if status == "hidden":
            continue

        full_name = "{} + {}".format(test_case.dir[len(END_TO_END_ROOT):], name)
        if message is not None:
            test_report.append((status, full_name, len(test_messages)))
            test_messages.append(message)
        else:
            test_report.append((status, full_name, None))

count = {"total": 0, "skipped": 0, "error": 0, "ok": 0}

# Print the report
print("====================================")
for status, name, message_id in test_report:
    count["total"] += 1
    msg = ""
    if status == "disabled":
        count["skipped"] += 1
        msg += "[SKIPPED]"
    elif status == "error":
        count["error"] += 1
        msg += "[ERROR  ]"
    elif status == "success":
        count["ok"] += 1
        msg += "[OK     ]"
    else:
        raise RuntimeError("Unknown test status: {}".format(status))

    if message_id is None:
        msg += "        "
    else:
        msg += " < {0: 3d} > ".format(message_id)

    msg += name

    print(msg)

if len(test_messages) > 0:
    print("====================================")
    print("MESSAGES:")
    for id, message in enumerate(test_messages):
        if id > 0:
            print("")
        print("< {0: 3d} >".format(id))
        print(message)

print("====================================")
print("     ok: {}".format(count["ok"]))
print("  error: {}".format(count["error"]))
if count["skipped"] > 0:
    print("skipped: {}".format(count["skipped"]))
print("  total: {}".format(count["total"]))

if count["error"] > 0:
    exit(1)

# for test_dir_name in os.listdir(END_TO_END_ROOT):
#     test_dir_path = os.path.join(END_TO_END_ROOT, test_dir_name)
#     if not os.path.isdir(test_dir_path):
#         continue
#     nodes = {os.path.join(test_dir_path, node_name) for node_name in os.listdir(test_dir_path)}
#     files = set(filter(os.path.isfile, nodes))
#
#     abs_config_path = os.path.join(test_dir_path, "test.json")
#     if abs_config_path not in files:
#         # Ignore directories without `test.json`
#         continue
#
#     with open(abs_config_path, "r") as config_file:
#         config_json = config_file.read()
#         config_data = json.loads(config_json)
#
#         source_path = config_data["source"]
#         should_error = "error" in config_data and config_data["error"]
#
#         abs_source_path = os.path.join(test_dir_path, source_path)
#
#         for compiler_path in [GCC_PATH, CLANG_PATH]:
#             for optimization_level in range(0, 3 + 1):
#                 arguments = [
#                     compiler_path,
#                     "-S",
#                     "-O{}".format(optimization_level),
#                     "-o", "{}.gcc-{}.a".format(abs_source_path, optimization_level)
#                 ]
#                 if compiler_path == CLANG_PATH:
#                     arguments += ["-Wno-main-return-type"]
#                 arguments += [abs_source_path]
#
#                 completed_process = subprocess.run(arguments, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
#
#                 if should_error:
#                     if completed_process.returncode == 0:
#                         sys.stderr.buffer.write(completed_process.stdout)
#                         raise Exception("Expected non-zero return code")
#                 elif completed_process.returncode != 0:
#                     sys.stderr.buffer.write(completed_process.stdout)
#                     raise Exception("Expected zero return code")
