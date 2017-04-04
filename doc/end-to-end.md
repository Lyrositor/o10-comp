# End-to-End

This script runs the end-to-end tests for the compiler.
It traverses a directory recursively to find test suites tests and then runs them.
A test-suite consists of a directory with a configuration file called `test.json`.
See the description of the configuration file below.

## Usage

```shell
python3 test.py [options]
```

### Options

- `--clang-path CLANG_PATH`: Set the path for _clang_ to `CLANG_PATH`. Default: `clang`.

- `--dot-path DOT_PATH`: Set the path for _dot_ to `DOT_PATH`. Default: `dot`.

- `--gcc-path GCC_PATH`: Set the path for _gcc_ to `GCC_PATH`. Default: `gcc`.

- `--no-ast-test`: Do not test the AST.

- `--no-clang`: Do not use _clang_.

- `--no-dot`: Do not render Dot files as PNG. This will disable `ir.actual-png`.

- `--no-gcc`: Do not use _gcc_.

- `--no-ir-test`: Do not test the IR.

## Configuration file

Each test is configured by a `test.json` file. The only required field is `source`.

### `skip`

- Type: boolean`
- Optional, default value: `false`

Do not run this test suite, but add its tests to the report with the `SKIPPED` status.

### `hidden`

- Type: **boolean**
- Optional, default value: `false`

Do not run this test suite. It will not appear in the report.

### `source`

- **Required**
- Type: `string`

The path to the C source file relative to the configuration file. Usually it is `main.c`.
This file is used as the source for the tests of the current test-suite.

### `ast`

- Type: `JsonDocument`
- Optional, default value: `{"hidden": true}`

### `ast.disabled`

- Type: boolean`
- Optional, default value: `false`

Do not test the AST, but report it with the `SKIPPED` status.

### `ast.hidden`

- Type: **boolean**
- Optional, default value: `false`

Do not test the AST.

### `ast.actual`

- Type: **string**
- Optional

Path to the file containing the actual AST, relative to the configuration file.
If this value is defined, the result of the AST will be written in the supplied file.
This will be a valid JSON file.
The conventional value is `ast.actual.json`.

### `ast.expected`

- Type: **string**
- Optional

Path to the file containing the expected AST, relative to the configuration file.
If this value is defined, the result of the AST will be compared with the one in this file.
If the content does not match, the test will fail.
This should be a valid JSON file.
The conventional value is `ast.expected.json`.

### `ast.return-code`

- Type: **number**
- Optional, default value: `0`

Expected return code. The AST test will fail if the code is different.
Change this value to `1` to expect errors.

### `ir`

- Type: `JsonDocument`
- Optional, default value: `{"hidden": true}`

Run the compiler with the `--ir` option.

### `ir.actual-dot`

- Type: **string**
- Optional

Path to the file containing the actual IR, relative to the configuration file.
If this value is defined, the result of the IR will be written in the supplied file.
This will be a valid Dot file.
The conventional value is `ast.actual.json`.

### `ir.actual-png`

- Type: **string**
- Optional

Path to the file containing a PNG rendering of the actual IR, relative to the
configuration file.
If this value is defined, the result of the IR will rendered as PNG and written in the
supplied file.
This will be a valid PNG file.
The conventional value is `ast.actual.png`.

### `ir.disabled`

- Type: boolean`
- Optional, default value: `false`

Do not test the IR, but report it with the `SKIPPED` status.

### `ast.expected-dot`

- Type: **string**
- Optional

Path to the file containing the expected IR, relative to the configuration file.
If this value is defined, the result of the IR will be compared with the one in this file.
If the content does not match, the test will fail.
This should be a valid Dot file.
The conventional value is `ast.expected.json`.

### `ir.hidden`

- Type: **boolean**
- Optional, default value: `false`

Do not test the IR.

### `ir.return-code`

- Type: **number**
- Optional, default value: `0`

Expected return code. The IR test will fail if the code is different.
Change this value to `1` to expect errors.

### `run`

- Type: `JsonDocument`
- Optional, default value: `{"hidden": true}`

Compile the source to assembly with `o10c` and then build an executable with `gcc`.
Test this compiled program.

### `run.actual-stdout`

- Type: **string**
- Optional

Path to the file containing the actual standard output, relative to the configuration file.
If this value is defined, the standard output will be written to the supplied file.
The conventional value is `stdout.actual`.

### `run.disabled`

- Type: boolean`
- Optional, default value: `false`

Do not test the compiled program, but report it with the `SKIPPED` status.

### `run.hidden`

- Type: **boolean**
- Optional, default value: `false`

Do not test the compiled program.

### `run.expected-stdout`

- Type: **string**
- Optional

Path to the file containing the expected standard output, relative to the configuration file.
If this value is defined, the standard output will be compared to this file.
If the content does not match, the test will fail.
The conventional value is `stdout.expected`.

### `run.return-code`

- Type: **number**
- Optional, default value: `0`

Expected return code.
