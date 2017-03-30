# This script visits each sub-directory in `end-to-end` and compiles its source file.
# Currently it only compiles with GCC and clang but the goal is to also run our compiler and check
# the output.


import json
import os
import subprocess
from typing import Set, Tuple

END_TO_END_ROOT = os.path.dirname(os.path.realpath(__file__))
PROJECT_ROOT = os.path.join(END_TO_END_ROOT, "..")
CONFIG_FILE_NAME = "test.json"


class Compiler:
    def __init__(self, name, path):
        self.name = name
        self.path = path

    def generate_assembly(self, directory, source_path):
        pass

DEFAULT_O10_COMP_PATH = os.path.join(PROJECT_ROOT, "build", "comp_main")

# Try to get the o10 compiler path from the environment, else use the default value
o10c_path = os.environ["O10_COMP_PATH"] if "O10_COMP_PATH" in os.environ else DEFAULT_O10_COMP_PATH

clang = Compiler("clang", "clang")
gcc = Compiler("gcc", "gcc")
o10c = Compiler("o10c", o10c_path)

DEFAULT_ASSEMBLY_GENERATION_CONFIGURATIONS = {
    "gcc-0": (gcc, ["-S", "-O0", "-fno-asynchronous-unwind-tables"]),
    "gcc-1": (gcc, ["-S", "-O1", "-fno-asynchronous-unwind-tables"]),
    "gcc-2": (gcc, ["-S", "-O2", "-fno-asynchronous-unwind-tables"]),
    "gcc-3": (gcc, ["-S", "-O3", "-fno-asynchronous-unwind-tables"]),
    "clang-0": (clang, ["-S", "-O0", "-fno-asynchronous-unwind-tables", "-Wno-main-return-type"]),
    "clang-1": (clang, ["-S", "-O1", "-fno-asynchronous-unwind-tables", "-Wno-main-return-type"]),
    "clang-2": (clang, ["-S", "-O2", "-fno-asynchronous-unwind-tables", "-Wno-main-return-type"]),
    "clang-3": (clang, ["-S", "-O3", "-fno-asynchronous-unwind-tables", "-Wno-main-return-type"]),
    #"o10c": (o10c, ["-c"])
}

ERRORS_ENUM = {"syntax"}


class TestConfig():
    def __init__(self):
        self.disabled = False
        self.source_path = None
        self.expect_error = None  # One of: {"syntax"}
        self.name = None
        # Only displayed if an error occurs, should explain the goal of test-case
        self.description = None

        self.test_ast = False
        self.expected_ast_path = None
        self.actual_ast_path = None

        self.generate_assembly = False
        self.assembly_generation_configs = []

    def from_json(input, test_dir) -> 'TestConfig':
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
            if config.expect_error == "syntax":
                config.test_ast = True

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
    def __init__(self, dir):
        self.dir = dir
        with open(os.path.join(dir, CONFIG_FILE_NAME), "r") as config_file:
            try:
                self.config = TestConfig.from_json(config_file.read(), dir)
            except:
                raise Exception("Invalid test config: " + os.path.join(dir, CONFIG_FILE_NAME))

    def run(self):
        if self.config.disabled:
            return {
                "ast": ("disabled", None),
                "std-assembly": ("disabled", None)
            }
        else:
            return {
                "ast": self.run_ast(),
                "std-assembly": self.run_assembly()
            }

    def run_ast(self):
        if self.config.disabled:
            return "disabled", None
        if not self.config.test_ast and self.config.actual_ast_path is None:
            return "hidden", None

        completed_process = subprocess.run(
            [o10c.path, "-j", self.config.source_path],
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

        if self.config.expect_error == "syntax":
            if completed_process.returncode == 0:
                msg = ("Expected syntax error, but got zero return code:\n"
                       "Stdout:\n"
                       "{}\n"
                       "Stderr:\n"
                       "{}"
                       ).format(stdout, stderr)
                return "error", msg
            else:
                return "success", None

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
        if self.config.disabled:
            return "disabled", None
        if not self.config.generate_assembly:
            return "hidden", None

        for config_name, (compiler, options) in self.config.assembly_generation_configs.items():
            output_name = "{}.{}.asm".format(self.config.source_path, config_name)
            arguments = [compiler.path] + options + ["--output", output_name, self.config.source_path]

            completed_process = subprocess.run(
                arguments,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE
            )

            stdout = completed_process.stdout.decode('utf-8')
            stderr = completed_process.stderr.decode('utf-8')

            if self.config.expect_error is not None:
                if completed_process.returncode == 0:
                    msg = ("Expected compilation error, but got zero return code for {}:\n"
                           "Stdout:\n"
                           "{}\n"
                           "Stderr:\n"
                           "{}"
                           ).format(config_name, stdout, stderr)
                    return "error", msg
                else:
                    return "success", None

            if completed_process.returncode != 0:
                msg = ("Expected successful compilation, but got non-zero return code for {}:\n"
                       "Stdout:\n"
                       "{}\n"
                       "Stderr:\n"
                       "{}"
                       ).format(config_name, stdout, stderr)
                return "error", msg

        return "success", None


# Returns a set of directories and a set of other FS nodes
def dir_content(dir_path) -> Tuple[Set[str], Set[str]]:
    files = set()
    dirs = set()
    for node_name in os.listdir(dir_path):
        abs_path = os.path.join(dir_path, node_name)
        if os.path.isdir(abs_path):
            dirs.add(abs_path)
        else:
            files.add(abs_path)
    return files, dirs


# Yields the test cases in the provided directory
def discover_tests(tests_dir, recursive = True):
    for fs_node in os.listdir(tests_dir):
        fs_node_path = os.path.join(tests_dir, fs_node)
        if not os.path.isdir(fs_node_path):
            continue
        test_dir_path = fs_node_path
        test_files, test_dirs = dir_content(test_dir_path)
        if os.path.join(test_dir_path, CONFIG_FILE_NAME) in test_files:
            yield TestCase(test_dir_path)
        elif recursive:
            for test_case in discover_tests(test_dir_path, True):
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
        msg += "         "
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
