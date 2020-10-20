BUILD_DIR ?= $(shell pwd)/out
OBJ_DIR ?= $(BUILD_DIR)/cache

.SILENT: all clean packager $(BUILD_DIR)/packager
.PHONY: all clean packager

all: packager
	echo "Done!"

packager:
	echo "Building packager..."
	$(MAKE) -s -C src/packager BUILD_DIR=$(BUILD_DIR) OBJ_DIR=$(OBJ_DIR)/packager

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
