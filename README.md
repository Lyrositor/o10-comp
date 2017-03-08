# TP COMP

## Requirements

If you just want to build the project, you will only need the _build dependencies_.
The test dependencies are required for unit tests, coverage analysis and memory leak checks (`make test`).

The project is continuously tested with [this docker image](https://raw.githubusercontent.com/demurgos/docker-cpp/master/insa/Dockerfile).

### Build dependencies

- _CMake_ 2.8
- _g++_ 4.7
- _git_ 2
- _GNU Make_

### Test dependencies

- _lcov_
- _Python_ 3
- _valgrind_

## Configure and build

Note: if you are using Windows, you may have to manually specify the paths to the `bison` and `flex` executables on your system.
To do so, specify the `BISON_EXECUTABLE` `FLEX_EXECUTABLE` variables when running CMake.

```shell
# Run as a normal user
make
# You can also run it manually:
# make prepare && make build
```

## Test

```shell
# Run as a normal user
make test
```

## License

[AGPL3](./LICENSE.md)
