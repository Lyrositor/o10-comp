# o10c

The **o10 compiler** (o10c for short) is a compiler for a subset of the C programming language. Features include:

* Compilation to GNU Assembler (GAS) files, with support for the following architectures:
  * x86-64
* Graphviz intermediate representation graph generation
* Abstract syntax tree export to JSON format
* Optional IR optimization
* Linux and Windows compilation support (OS X should also be supported, but has not been tested)

## Requirements

If you just want to build the project, you will only need the _build dependencies_.
The test dependencies are required for unit tests, coverage analysis and memory leak checks (`make test`).

The project is continuously tested with [this docker image](https://raw.githubusercontent.com/demurgos/docker-cpp/master/insa-gcc-5/Dockerfile).

You can start a session with the environment of the Docker image above by running
the following command in an empty directory:

```shell
# Run as a normal user
docker run --interactive --tty --volume "$(pwd):$(pwd)" demurgos/cpp:insa-gcc-5 /bin/bash
```

Then, you can get the project (`git clone <repo_uri>`) and follow the build steps.

### Build dependencies

- _CMake_ 2.8
- _g++_ 5
- _git_ 2
- _GNU Make_

### Test dependencies

- _lcov_
- _Python_ 3
- _valgrind_
- _clang_ (optional)

## Configure and build

Note: if you are using Windows, you may have to manually specify the paths to the `bison` and `flex` executables on your system.
To do so, specify the `BISON_EXECUTABLE` and `FLEX_EXECUTABLE` variables when running CMake.

```shell
# Run as a normal user
# Install the dependencies
make prepare
# Build all the targets of the project
make
```

Note: on INSA machines, replace all uses of `make` with `./make-insa` (the parameters are unchanged).

You will get the following artifacts:

- **build/o10c**: The compiler executable
- **build/comp_test**: The executable that runs the unit-tests
- **build/src/lib/libcomp.a**: The compiler library, the headers are in **include/**

## Run

To run the compiler, run the `build/o10c` executable from the command-line. You can use the `-h` flag for information about its usage.

If you only want to compile an executable and have GCC installed, run the `o10c.sh` script instead. It takes two parameters:
- a C source file to compile
- the name of the executable file to produce

Example: `./o10c.sh my_program.c my_program`

## Test

```shell
# Run as a normal user
make test
```

This will run the unit-tests once, then run them again with _Valgrind_ and then build
the main executable and run the end-to-end tests.

You can run each step individually with the following commands:

```shell
# Run as a normal user
make test.unit
make test.memory
make test.end-to-end
```

Finally, you can also run the unit tests with test coverage analysis with:

```shell
make coverage
```

Note: on INSA machines, replace all uses of `make` with `./make-insa` (the parameters are unchanged).

## License

[AGPL3](./LICENSE.md)
