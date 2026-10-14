CC = gcc
AR = ar
COPY = cp
RM = rm -rf
RM_FILE = rm -f

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
    CFLAGS = -Wall -Wextra -Werror -std=c11
else
    CFLAGS = -Wall -Wextra -Werror -std=c11 -I/opt/homebrew/opt/check/include
endif

LDFLAGS =

FORMATTER = clang-format
LEAK_CHECKER = valgrind
LEAK_CHECKER_FLAGS = --leak-check=full --show-leak-kinds=all --error-exitcode=1

SRC_DIR = .
TEST_DIR = ./tests
FUNC_DIR = ./functions
BUILD_DIR = ../build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
REPORT_DIR = ../report

LIB_NAME = s21_matrix.a
TEST_BIN = $(BIN_DIR)/test

LIB_SRCS = $(shell find $(FUNC_DIR) -type f -name '*.c' | sed 's|^\./||' | sort) s21_helpers.c
LIB_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))

ifeq ($(UNAME),Darwin)
    TEST_SRCS = $(shell find $(TEST_DIR) -type f -name '*.c' ! -name 'alloc_mock.c' | sed 's|^\./||' | sort)
else
    TEST_SRCS = $(shell find $(TEST_DIR) -type f -name '*.c' | sed 's|^\./||' | sort)
    LDFLAGS += -Wl,--wrap=calloc
endif
TEST_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))

ifeq ($(UNAME),Linux)
    CHECK_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
else
    CHECK_LIBS = -lcheck -lm -lpthread -L/opt/homebrew/opt/check/lib
endif

ifeq ($(GCOV),1)
	CFLAGS += -fprofile-arcs -ftest-coverage -O0
	LDFLAGS += -fprofile-arcs -ftest-coverage
endif

ifeq ($(UNAME),Darwin)
    MOCK_DYLIB = $(BIN_DIR)/liballoc_mock.dylib
    MOCK_CFLAGS = -Wall -Wextra -Werror -std=c11 -I/opt/homebrew/opt/check/include -dynamiclib \
                  -install_name @executable_path/liballoc_mock.dylib
    MOCK_LINK = -L$(BIN_DIR) -lalloc_mock -Wl,-rpath,@executable_path
endif

.PHONY: all clean test gcov_report style format leak_check

all: $(LIB_NAME)

$(LIB_NAME): $(LIB_OBJS)
	$(AR) rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

ifeq ($(UNAME),Darwin)
$(MOCK_DYLIB): tests/alloc_mock.c tests/alloc_mock.h
	@mkdir -p $(BIN_DIR)
	$(CC) $(MOCK_CFLAGS) tests/alloc_mock.c -o $(MOCK_DYLIB)

test: $(TEST_BIN) $(MOCK_DYLIB)
	$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS) $(LIB_NAME) $(MOCK_DYLIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIB_NAME) -o $@ $(CHECK_LIBS) $(LDFLAGS) $(MOCK_LINK)
else
test: $(TEST_BIN)
	$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS) $(LIB_NAME)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIB_NAME) -o $@ $(CHECK_LIBS) $(LDFLAGS)
endif

gcov_report: clean
	$(MAKE) GCOV=1 test
	lcov --capture --directory $(OBJ_DIR) --base-directory . --output-file $(BUILD_DIR)/coverage.info --ignore-errors unsupported
	lcov --ignore-errors unused,unsupported --remove $(BUILD_DIR)/coverage.info '/usr/*' '*/tests/*' '*/s21_helpers.c' '*/s21_helpers.h' --output-file $(BUILD_DIR)/coverage.filtered.info
	genhtml $(BUILD_DIR)/coverage.filtered.info --output-directory $(REPORT_DIR)

style:
	$(COPY) ../materials/linters/.clang-format .
	$(FORMATTER) -n $(shell find $(SRC_DIR) $(TEST_DIR) -name '*.c' -o -name '*.h')
	$(RM_FILE) .clang-format

format:
	$(COPY) ../materials/linters/.clang-format .
	$(FORMATTER) -i $(shell find $(SRC_DIR) $(TEST_DIR) -name '*.c' -o -name '*.h')
	$(RM_FILE) .clang-format

leak_check: $(TEST_BIN)
	$(LEAK_CHECKER) $(LEAK_CHECKER_FLAGS) $(TEST_BIN) 2>&1 | grep "ERROR SUMMARY" || true

clean:
	$(RM) $(BUILD_DIR) $(REPORT_DIR) $(LIB_NAME) *.gcno *.gcda *.info
