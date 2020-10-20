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
	$(CXX) -o $(BUILD_DIR)/packager $(OBJECTS) thirdparty/zipper/bin/libZipper.a -lz

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
