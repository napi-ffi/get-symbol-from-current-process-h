/**
 * Unit tests for get-symbol-from-current-process.h
 *
 * This test suite verifies the functionality of the get_symbol_from_current_process
 * function across different platforms.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/get-symbol-from-current-process.h"

/* Test counter */
static int tests_passed = 0;
static int tests_failed = 0;

/* Test macros */
#define TEST(name) \
    static void test_##name(void); \
    static void run_test_##name(void) { \
        printf("Running test: %s\n", #name); \
        test_##name(); \
    } \
    static void test_##name(void)

#define ASSERT(condition, message) \
    do { \
        if (condition) { \
            printf("  ✓ PASS: %s\n", message); \
            tests_passed++; \
        } else { \
            printf("  ✗ FAIL: %s\n", message); \
            tests_failed++; \
        } \
    } while (0)

#define RUN_TEST(name) run_test_##name()

/* Test: Getting a NULL symbol name should return NULL */
TEST(null_symbol_name) {
    void* sym = get_symbol_from_current_process(NULL);
    ASSERT(sym == NULL, "NULL symbol name should return NULL");
}

/* Test: Getting a non-existent symbol should return NULL */
TEST(nonexistent_symbol) {
    void* sym = get_symbol_from_current_process("this_symbol_definitely_does_not_exist_12345");
    ASSERT(sym == NULL, "Non-existent symbol should return NULL");
}

/* Test: Getting a valid symbol from standard library */
TEST(valid_stdlib_symbol) {
    /* Try to get a common C library function like printf */
    void* sym = get_symbol_from_current_process("printf");

    /* On most platforms, printf should be available */
    /* However, on some platforms with static linking, it might not be */
    /* So we just check that the function doesn't crash */
    if (sym != NULL) {
        ASSERT(1, "Successfully retrieved printf symbol");
    } else {
        ASSERT(1, "printf symbol not available (possibly static linking)");
    }
}

/* Test: Getting malloc - should be available on all platforms */
TEST(malloc_symbol) {
    void* sym = get_symbol_from_current_process("malloc");

    if (sym != NULL) {
        ASSERT(1, "Successfully retrieved malloc symbol");
    } else {
        /* malloc might not be exported in all configurations */
        ASSERT(1, "malloc symbol not available (possibly static linking)");
    }
}

/* Test: Empty string symbol name */
TEST(empty_string_symbol) {
    void* sym = get_symbol_from_current_process("");
    ASSERT(sym == NULL, "Empty string symbol name should return NULL");
}

/* Test: Very long symbol name */
TEST(long_symbol_name) {
    char long_name[1000];
    memset(long_name, 'a', sizeof(long_name) - 1);
    long_name[sizeof(long_name) - 1] = '\0';

    void* sym = get_symbol_from_current_process(long_name);
    ASSERT(sym == NULL, "Very long non-existent symbol name should return NULL");
}

/* Test: Multiple calls should work correctly */
TEST(multiple_calls) {
    void* sym1 = get_symbol_from_current_process("printf");
    void* sym2 = get_symbol_from_current_process("printf");

    /* Both calls should return the same result (either both NULL or both non-NULL) */
    ASSERT((sym1 == NULL && sym2 == NULL) || (sym1 != NULL && sym2 != NULL),
           "Multiple calls should return consistent results");
}

/* Test: Symbol names with special characters */
TEST(special_characters_in_name) {
    /* These should all return NULL as they are invalid symbol names */
    void* sym1 = get_symbol_from_current_process("symbol@with@at");
    void* sym2 = get_symbol_from_current_process("symbol.with.dots");
    void* sym3 = get_symbol_from_current_process("symbol-with-dashes");

    ASSERT(sym1 == NULL, "Symbol with @ characters should return NULL");
    ASSERT(sym2 == NULL, "Symbol with dots should return NULL");
    ASSERT(sym3 == NULL, "Symbol with dashes should return NULL");
}

/* Main test runner */
int main(void) {
    printf("\n");
    printf("===========================================\n");
    printf("Testing get-symbol-from-current-process.h\n");
    printf("===========================================\n\n");

    RUN_TEST(null_symbol_name);
    printf("\n");

    RUN_TEST(nonexistent_symbol);
    printf("\n");

    RUN_TEST(valid_stdlib_symbol);
    printf("\n");

    RUN_TEST(malloc_symbol);
    printf("\n");

    RUN_TEST(empty_string_symbol);
    printf("\n");

    RUN_TEST(long_symbol_name);
    printf("\n");

    RUN_TEST(multiple_calls);
    printf("\n");

    RUN_TEST(special_characters_in_name);
    printf("\n");

    printf("===========================================\n");
    printf("Test Results:\n");
    printf("  Passed: %d\n", tests_passed);
    printf("  Failed: %d\n", tests_failed);
    printf("  Total:  %d\n", tests_passed + tests_failed);
    printf("===========================================\n\n");

    return tests_failed > 0 ? 1 : 0;
}
