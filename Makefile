CXX ?= c++
CXX_STANDARD := -std=c++20

INCLUDE_FLAGS := -Iinclude -Ideps/ftxui/include -Ideps/jsoncpp/include
LINK_FLAGS := -Ldeps/ftxui/build -lftxui-component -lftxui-dom -lftxui-screen -Ldeps/jsoncpp/build/lib -ljsoncpp

DEBUG_FLAGS := -Wall -Wextra -Wpedantic
OPTIMIZATION_FLAGS := -O2 -march=native -pipe

OBJECT_FILES := build/classes.cpp.o build/config.cpp.o build/flags.cpp.o build/files.cpp.o build/help.cpp.o build/init.cpp.o build/main.cpp.o build/run.cpp.o

define COMPILE
	${CXX} -c $(1) ${CXX_STANDARD} ${INCLUDE_FLAGS} ${DEBUG_FLAGS} ${OPTIMIZATION_FLAGS} -o build/$(notdir $(1)).o

endef

all: build deps deps/ftxui deps/jsoncpp wikos

build:
	mkdir build

deps:
	mkdir deps

deps/ftxui:
	git -C deps clone https://github.com/ArthurSonzogni/ftxui --depth=1 --branch=v5.0.0
	mkdir deps/ftxui/build
	cmake -S deps/ftxui -B deps/ftxui/build
	$(MAKE) -C deps/ftxui/build

deps/jsoncpp:
	git -C deps clone https://github.com/open-source-parsers/jsoncpp --depth=1 --branch=1.9.6
	mkdir deps/jsoncpp/build
	cmake -S deps/jsoncpp -B deps/jsoncpp/build -DJSONCPP_WITH_TESTS=OFF -DBUILD_SHARED_LIBS=OFF
	$(MAKE) -C deps/jsoncpp/build

build/classes.cpp.o: include/classes.hpp src/classes.cpp
	$(call COMPILE,src/classes.cpp)

build/config.cpp.o: include/config.hpp src/config.cpp
	$(call COMPILE,src/config.cpp)

build/flags.cpp.o: include/flags.hpp src/flags.cpp
	$(call COMPILE,src/flags.cpp)

build/files.cpp.o: include/files.hpp src/files.cpp
	$(call COMPILE,src/files.cpp)

build/help.cpp.o: include/help.hpp src/help.cpp
	$(call COMPILE,src/help.cpp)

build/init.cpp.o: include/init.hpp include/utils.hpp src/init.cpp
	$(call COMPILE,src/init.cpp)

build/main.cpp.o: src/main.cpp
	$(call COMPILE,src/main.cpp)

build/run.cpp.o: include/run.hpp src/run.cpp
	$(call COMPILE,src/run.cpp)

wikos: ${OBJECT_FILES}
	${CXX} ${OBJECT_FILES} ${LINK_FLAGS} -o wikos
	strip wikos

clean:
ifneq (,$(wildcard build))
	rm -r build
endif
ifneq (,$(wildcard deps))
	rm -rf deps
endif
ifneq (,$(wildcard wikos))
	rm wikos
endif
