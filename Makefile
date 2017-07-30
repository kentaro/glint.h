CC?=gcc
PROVE?=prove
BUILD_DIR?=build

all:

test: test-bin
	$(PROVE) -v $(BUILD_DIR)/test-bin

test-bin: picotest/picotest.c test.c
	$(CC) -Wall $(CFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/$@ $^

clean:
	rm -f $(BUILD_DIR)/*

.PHONY: test