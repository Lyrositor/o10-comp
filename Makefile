.PHONY: build clean default prepare test

default: build

prepare:
	rm -rf vendor/googletest && git clone https://github.com/google/googletest.git vendor/googletest

clean:
	rm -rf ./build/

build: build/Makefile
	cd build/ && make comp_main VERBOSE=1

build/Makefile: CMakeLists.txt
	mkdir -p build/ && cd build/ && cmake ..

build/comp_main: build

run: build/comp_main
	build/comp_main

test:
	mkdir -p build/
	cd build/ && cmake .. && make comp_test && ./comp_test && valgrind --leak-check=full --error-exitcode=1 ./comp_test && make comp_coverage
