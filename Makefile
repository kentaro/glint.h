CC?=gcc
PROVE?=prove
BUILD_DIR?=build

all:

test: test-bin test-server
	$(PROVE) -v $(BUILD_DIR)/test-bin

test-bin: picotest/picotest.c tests/test.c
	$(CC) -Wall $(CFLAGS) $(LDFLAGS) -I. -o $(BUILD_DIR)/test-bin $^

test-server: tests/test-server.c
	$(CC) -Wall $(CFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/test-server $^

clean:
	rm -f $(BUILD_DIR)/*

.PHONY: test