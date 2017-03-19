# This script visits each sub-directory in `end-to-end` and compiles its source file.
# Currently it only compiles with GCC and clang but the goal is to also run our compiler and check
# the output.


import json
import os
import subprocess

END_TO_END_ROOT = os.path.dirname(os.path.realpath(__file__))
CONFIG_FILE = "test.json"
GCC_PATH = "gcc"
CLANG_PATH = "clang"


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
        abs_source_path = os.path.join(test_dir_path, source_path)

        if abs_source_path not in files:
            raise Exception("File not found: {}".format(abs_source_path))

        # Run gcc
        for optimization_level in range(0, 3 + 1):
            subprocess.call([
                GCC_PATH,
                "-S",
                "-O{}".format(optimization_level),
                "-o", "{}.gcc-{}.a".format(abs_source_path, optimization_level),
                abs_source_path
            ])

        # Run clang
        for optimization_level in range(0, 3 + 1):
            subprocess.call([
                CLANG_PATH,
                "-S",
                "-O{}".format(optimization_level),
                "-o", "{}.clang-{}.a".format(abs_source_path, optimization_level),
                "-Wno-main-return-type",
                abs_source_path
            ])
