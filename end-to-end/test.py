# This script visits each sub-directory in `end-to-end` and compiles its source file.
# Currently it only compiles with GCC and clang but the goal is to also run our compiler and check
# the output.


import json
import os
import subprocess
import sys


END_TO_END_ROOT = os.path.dirname(os.path.realpath(__file__))
CONFIG_FILE = "test.json"
GCC_PATH = "gcc"
CLANG_PATH = "clang"
COMP_PATH = os.path.join(END_TO_END_ROOT, "..", "build", "comp_main")


for test_dir_name in os.listdir(END_TO_END_ROOT):
    test_dir_path = os.path.join(END_TO_END_ROOT, test_dir_name)
    if not os.path.isdir(test_dir_path):
        continue
    nodes = {os.path.join(test_dir_path, node_name) for node_name in os.listdir(test_dir_path)}
    files = set(filter(os.path.isfile, nodes))

    abs_config_path = os.path.join(test_dir_path, "test.json")
    if abs_config_path not in files:
        # Ignore directories without `test.json`
        continue

    with open(abs_config_path, "r") as config_file:
        config_json = config_file.read()
        config_data = json.loads(config_json)

        source_path = config_data["source"]
        should_error = "error" in config_data and config_data["error"]

        abs_source_path = os.path.join(test_dir_path, source_path)

        if "expected-ast" in config_data:
            expected_ast_path = os.path.join(test_dir_path, config_data["expected-ast"])
            completed_process = subprocess.run([COMP_PATH, abs_source_path], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            # TODO: use sys.stout.encoding
            actual_ast = json.loads(completed_process.stdout.decode('utf-8'))
            with open(expected_ast_path, "r") as expected_ast_file:
                expected_ast = json.loads(expected_ast_file.read())
                if expected_ast != actual_ast:
                    print("EXPECT AST:")
                    print(expected_ast)
                    print("ACTUAL AST:")
                    print(actual_ast)
                    raise Exception("Unexpected AST!")

        if abs_source_path not in files:
            raise Exception("File not found: {}".format(abs_source_path))

        for compiler_path in [GCC_PATH, CLANG_PATH]:
            for optimization_level in range(0, 3 + 1):
                arguments = [
                    compiler_path,
                    "-S",
                    "-O{}".format(optimization_level),
                    "-o", "{}.gcc-{}.a".format(abs_source_path, optimization_level)
                ]
                if compiler_path == CLANG_PATH:
                    arguments += ["-Wno-main-return-type"]
                arguments += [abs_source_path]

                completed_process = subprocess.run(arguments, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

                if should_error:
                    if completed_process.returncode == 0:
                        sys.stderr.buffer.write(completed_process.stdout)
                        raise Exception("Expected non-zero return code")
                elif completed_process.returncode != 0:
                    sys.stderr.buffer.write(completed_process.stdout)
                    raise Exception("Expected zero return code")
