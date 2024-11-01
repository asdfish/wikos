CXX ?= c++
CXX_FLAGS := -std=c++20 $\
								-Iinclude -Ideps/ftxui/include -Ideps/jsoncpp/include $\
								-Wall -Wextra -Wpedantic -Wno-missing-field-initializers $\
								-O2 -march=native -pipe

LD_FLAGS := -Ldeps/ftxui/build -lftxui-component -lftxui-dom -lftxui-screen -Ldeps/jsoncpp/build/lib -ljsoncpp

PROCESSED_HEADER_FILES := $(subst .hpp,$\
														$(if $(findstring clang++,${CXX}),$\
															.hpp.pch,$\
															.hpp.gch),$\
														$(shell find include -name '*.hpp'))
OBJECT_FILES := $(patsubst src/%.cpp,$\
									build/%.o,$\
									$(shell find src -name '*.cpp'))

INSTALL_DIRECTORY := /usr/local/bin

FTXUI_LIBS := deps/ftxui/build/libftxui-component.a deps/ftxui/build/libftxui-dom.a deps/ftxui/build/libftxui-screen.a

define REMOVE_LIST
	$(foreach ITEM,$\
		$(1),$\
		$(if $(wildcard ${ITEM}),$\
			$(shell rm ${ITEM})))

endef

all: ${FTXUI_LIBS} deps/jsoncpp/build/lib/libjsoncpp.a wikos

${FTXUI_LIBS}:
	mkdir deps/ftxui/build
	cmake -S deps/ftxui -B deps/ftxui/build
	$(MAKE) -C deps/ftxui/build

deps/jsoncpp/build/lib/libjsoncpp.a:
	mkdir deps/jsoncpp/build
	cmake -S deps/jsoncpp -B deps/jsoncpp/build -DJSONCPP_WITH_TESTS=OFF -DBUILD_SHARED_LIBS=OFF -DBUILD_OBJECT_LIBS=OFF
	$(MAKE) -C deps/jsoncpp/build

build/%.o: src/%.cpp
	${CXX} -c $< ${CXX_FLAGS} -o $@

%.pch: %
	${CXX} -c $< ${CXX_FLAGS}

%.gch: %
	${CXX} -c $< ${CXX_FLAGS}

wikos: ${PROCESSED_HEADER_FILES} ${OBJECT_FILES}
	${CXX} ${OBJECT_FILES} ${LD_FLAGS} -o wikos
	strip wikos

clean:
	$(call REMOVE_LIST,$\
		${PROCESSED_HEADER_FILES})
	$(call REMOVE_LIST,$\
		${OBJECT_FILES})
ifneq (,$(wildcard wikos))
	rm wikos
endif

install: all ${INSTALL_DIRECTORY} uninstall
	cp wikos ${INSTALL_DIRECTORY}

uninstall:
ifneq (, $(wildcard ${INSTALL_DIRECTORY}/wikos))
	rm ${INSTALL_DIRECTORY}/wikos
endif

.PHONY: all clean install uninstall
