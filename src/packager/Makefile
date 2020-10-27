CXXFLAGS = -std=c++11

BUILD_DIR ?= $(shell pwd)/out
OBJ_DIR ?= $(BUILD_DIR)/cache/packager

SRC = $(wildcard *.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: build clean

build: $(OBJECTS)
	mkdir -p $(@D)
	# TODO: Find a way to make libraries portable
	$(CXX) -o $(BUILD_DIR)/packager $(OBJECTS) thirdparty/zipper/bin/libZipper.a thirdparty/libarchive/bin/libarchive.a -lz -liconv -lxml2 -llzma -lbz2

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
