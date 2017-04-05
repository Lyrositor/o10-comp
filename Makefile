.PHONY: build clean default prepare test.unit test.memory coverage

default: build

prepare:
	rm -rf vendor/googletest && git clone https://github.com/google/googletest.git vendor/googletest
	rm -rf vendor/rapidjson && git clone https://github.com/miloyip/rapidjson.git vendor/rapidjson

clean:
	rm -rf ./build/

build: build/Makefile
	cd build/ && make o10c --no-print-directory

build/Makefile: CMakeLists.txt
	mkdir -p build/ && cd build/ && cmake ..

run: build
	build/o10c

test: test.unit test.memory test.end-to-end

test.unit:
	mkdir -p build/
	cd build/ && cmake .. && make --no-print-directory comp_test && ./comp_test

test.memory:
	mkdir -p build/
	cd build/ && cmake .. && make --no-print-directory comp_test && valgrind --leak-check=full --error-exitcode=1 ./comp_test

test.end-to-end:
	mkdir -p build/
	cd build/ && cmake .. && make --no-print-directory o10c
	python3 end-to-end/test.py

coverage:
	mkdir -p build/
	cd build/ && cmake .. && make --no-print-directory comp_coverage
