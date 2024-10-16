CXX ?= c++
CXX_STANDARD := -std=c++17

INCLUDE_FLAGS := -Iinclude -Ideps/ftxui/include
LINK_FLAGS := -Ldeps/ftxui/build -lftxui-component -lftxui-dom -lftxui-screen

DEBUG_FLAGS := -Wall -Wextra -Wpedantic
OPTIMIZATION_FLAGS := -O2 -march=native -pipe

OBJECT_FILES := build/config.cpp.o build/files.cpp.o build/flags.cpp.o build/help.cpp.o build/init.cpp.o build/main.cpp.o build/run.cpp.o build/utils.cpp.o

define COMPILE
	${CXX} -c $(1) ${CXX_STANDARD} ${INCLUDE_FLAGS} ${DEBUG_FLAGS} -o build/$(notdir $(1)).o

endef

all: build deps/ftxui bikos

build:
	mkdir build

deps:
	mkdir deps

deps/ftxui: deps
	git -C deps clone https://github.com/ArthurSonzogni/ftxui --depth=1
ifneq (,$(wildcard deps/ftxui/build))
	mkdir deps/ftxui/build
endif
	cmake -S deps/ftxui -B deps/ftxui/build
	$(MAKE) -C deps/ftxui/build

build/config.cpp.o: src/config.cpp
	$(call COMPILE,src/config.cpp)

build/files.cpp.o: src/files.cpp
	$(call COMPILE,src/files.cpp)

build/flags.cpp.o: src/flags.cpp
	$(call COMPILE,src/flags.cpp)

build/help.cpp.o: src/help.cpp
	$(call COMPILE,src/help.cpp)

build/init.cpp.o: src/init.cpp
	$(call COMPILE,src/init.cpp)

build/main.cpp.o: src/main.cpp
	$(call COMPILE,src/main.cpp)

build/run.cpp.o: src/run.cpp
	$(call COMPILE,src/run.cpp)

build/utils.cpp.o: src/utils.cpp
	$(call COMPILE,src/utils.cpp)

bikos: ${OBJECT_FILES}
	${CXX} ${OBJECT_FILES} ${LINK_FLAGS} -o bikos
	strip bikos

clean:
ifneq (,$(wildcard build))
	rm -r build
endif
ifneq (,$(wildcard deps))
	rm -r deps
endif
ifneq (,$(wildcard bikos))
	rm bikos
endif
