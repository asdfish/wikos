CXX := clang++
CXX_STANDARD := -std=c++20

INCLUDE_FLAGS := -Iinclude -Ideps/ftxui/include -Ideps/jsoncpp/include
LINK_FLAGS := -Ldeps/ftxui/build -lftxui-component -lftxui-dom -lftxui-screen -Ldeps/jsoncpp/build/lib -ljsoncpp

DEBUG_FLAGS := -Wall -Wextra -Wpedantic -Wno-missing-field-initializers
OPTIMIZATION_FLAGS := -O2 -march=native -pipe

OBJECT_FILES := build/commands/config.cpp.o build/commands/help.cpp.o build/commands/init.cpp.o build/commands/run.cpp.o $\
								build/flags/checkbox_base.cpp.o build/flags/checkbox_array_flag.cpp.o build/flags/checkbox_separated_flag.cpp.o build/flags/input_flag.cpp.o build/flags/radiobox_flag.cpp.o build/flags/source_files_flag.cpp.o $\
								build/utils/files.cpp.o build/utils/flag_definitions.cpp.o $\
								build/main.cpp.o

INSTALL_DIRECTORY := /usr/local/bin

define COMPILE
	${CXX} -c $(1) ${CXX_STANDARD} ${INCLUDE_FLAGS} ${DEBUG_FLAGS} ${OPTIMIZATION_FLAGS} -o $(2)

endef

all: build build/commands build/flags build/utils deps deps/ftxui deps/jsoncpp wikos

build:
	mkdir build

build/commands:
	mkdir build/commands

build/flags:
	mkdir build/flags

build/utils:
	mkdir build/utils

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
	cmake -S deps/jsoncpp -B deps/jsoncpp/build -DJSONCPP_WITH_TESTS=OFF -DBUILD_SHARED_LIBS=OFF -DBUILD_OBJECT_LIBS=OFF
	$(MAKE) -C deps/jsoncpp/build

build/commands/config.cpp.o: include/commands/config.hpp include/utils/flag_definitions.hpp src/commands/config.cpp
	$(call COMPILE,src/commands/config.cpp,build/commands/config.cpp.o)
build/commands/help.cpp.o: src/commands/help.cpp
	$(call COMPILE,src/commands/help.cpp,build/commands/help.cpp.o)
build/commands/init.cpp.o: include/commands/init.hpp include/utils/flag_definitions.hpp include/utils/files.hpp include/utils/vectors.hpp src/commands/init.cpp
	$(call COMPILE,src/commands/init.cpp,build/commands/init.cpp.o)
build/commands/run.cpp.o: include/commands/run.hpp include/utils/flag_definitions.hpp src/commands/run.cpp
	$(call COMPILE,src/commands/run.cpp,build/commands/run.cpp.o)

build/flags/checkbox_array_flag.cpp.o: include/flags/checkbox_array_flag.hpp src/flags/checkbox_array_flag.cpp
	$(call COMPILE,src/flags/checkbox_array_flag.cpp,build/flags/checkbox_array_flag.cpp.o)
build/flags/checkbox_base.cpp.o: include/flags/checkbox_base.hpp src/flags/checkbox_base.cpp
	$(call COMPILE,src/flags/checkbox_base.cpp,build/flags/checkbox_base.cpp.o)
build/flags/checkbox_separated_flag.cpp.o: include/flags/checkbox_separated_flag.hpp src/flags/checkbox_separated_flag.cpp
	$(call COMPILE,src/flags/checkbox_separated_flag.cpp,build/flags/checkbox_separated_flag.cpp.o)
build/flags/input_flag.cpp.o: include/flags/input_flag.hpp src/flags/input_flag.cpp
	$(call COMPILE,src/flags/input_flag.cpp,build/flags/input_flag.cpp.o)
build/flags/radiobox_flag.cpp.o: include/flags/radiobox_flag.hpp src/flags/radiobox_flag.cpp
	$(call COMPILE,src/flags/radiobox_flag.cpp,build/flags/radiobox_flag.cpp.o)
build/flags/source_files_flag.cpp.o: include/flags/source_files_flag.hpp include/utils/files.hpp src/flags/source_files_flag.cpp
	$(call COMPILE,src/flags/source_files_flag.cpp,build/flags/source_files_flag.cpp.o)

build/utils/files.cpp.o: include/utils/files.hpp include/utils/vectors.hpp src/utils/files.cpp
	$(call COMPILE,src/utils/files.cpp,build/utils/files.cpp.o)
build/utils/flag_definitions.cpp.o: include/flags/checkbox_array_flag.hpp include/flags/checkbox_separated_flag.hpp include/flags/radiobox_flag.hpp include/flags/source_files_flag.hpp src/utils/flag_definitions.cpp
	$(call COMPILE,src/utils/flag_definitions.cpp,build/utils/flag_definitions.cpp.o)

build/main.cpp.o: include/commands/config.hpp include/commands/help.hpp include/commands/init.hpp include/commands/run.hpp src/main.cpp
	$(call COMPILE,src/main.cpp,build/main.cpp.o)

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

install: all ${INSTALL_DIRECTORY}
	cp wikos ${INSTALL_DIRECTORY}

uninstall:
ifneq (, $(wildcard ${INSTALL_DIRECTORY}/wikos))
	rm ${INSTALL_DIRECTORY}/wikos
endif
