CUR_DIR := $(shell pwd)
BIN_DIR := $(CUR_DIR)/bin
BUILD_DIR := $(CUR_DIR)/build_dir

LIBC := $(CUR_DIR)/libc
LIBC_HEADER := $(LIBC)/include
LIBC_OBJECT := $(LIBC)/libc.a

CC := gcc
LD := ld
MAKE := make
INSTALL := install
CP := cp -afu
RM := rm -rf

export CC LD LIBC_HEADER LIBC_OBJECT

build/prepare:
	$(INSTALL) -d $(BIN_DIR) $(BUILD_DIR)

build/emulator: build/prepare load
	$(CP) emulator $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR)/emulator all
	$(INSTALL) $(BUILD_DIR)/emulator/emulator $(BIN_DIR)

build/loader: build/prepare
	$(CP) loader $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR)/loader all
	$(INSTALL) $(BUILD_DIR)/loader/loader $(BIN_DIR)

build/cases: build/prepare
	$(CP) testcase/cases $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR)/cases all
	$(RM) $(BIN_DIR)/cases/ && $(INSTALL) -d $(BIN_DIR)/cases
	$(INSTALL) $(BUILD_DIR)/cases/*.out $(BIN_DIR)/cases
	rename 's/.out//' $(BIN_DIR)/cases/*.out
	$(INSTALL) $(BUILD_DIR)/cases/runall.sh $(BIN_DIR)

build/typing: build/prepare
	$(CP) testcase/typing $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR)/typing all
	$(INSTALL) $(BUILD_DIR)/typing/typing $(BIN_DIR)

load: build/loader
	objcopy -S -O binary $(BIN_DIR)/loader $(BIN_DIR)/loader
	cd $(BIN_DIR) && xxd -i loader > ../emulator/loader/loader.c
	rm $(BIN_DIR)/loader

clean/emulator:
	$(RM) $(BUILD_DIR)/emulator $(BIN_DIR)/emulator

clean/loader:
	$(RM) $(BUILD_DIR)/loader $(BIN_DIR)/loader

clean/cases:
	$(RM) $(BUILD_DIR)/cases $(BIN_DIR)/cases

clean/typing:
	$(RM) $(BUILD_DIR)/typing $(BIN_DIR)/typing

clean:
	$(RM) $(BIN_DIR) $(BUILD_DIR)

.PHONY: build/prepare build/emulator build/loader build/cases build/typing load clean/emulator clean/loader clean/cases clean/typing clean
