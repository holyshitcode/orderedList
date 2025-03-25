#include "unitTest.h"

jmp_buf jump;

// 문자열 비교
int assertEqualString(char *input, char *expected) {
    if (strcmp(input, expected) == 0) {
        printf("✅ PASS: \"%s\" == \"%s\"\n", input, expected);
        return 1;
    } else {
        printf("❌ FAIL: Expected \"%s\" but got \"%s\"\n", expected, input);
        return 0;
    }
}

// 정수 비교
int assertEqualInt(int input, int expected) {
    if (input != expected) {
        printf("❌ FAIL: Expected %d but got %d\n", expected, input);
        return 0;
    }
    printf("✅ PASS: %d == %d\n", input, expected);
    return 1;
}

// 문자열 길이 비교
int assertEqualCharLen(char *input, char *expected) {
    if (input == NULL || expected == NULL) {
        printf("❌ FAIL: One of the inputs is NULL\n");
        return 0;
    }
    int inputLen = strlen(input);
    int expectedLen = strlen(expected);
    if (inputLen != expectedLen) {
        printf("❌ FAIL: Expected length %d but got %d\n", expectedLen, inputLen);
        return 0;
    }
    printf("✅ PASS: Length %d == %d\n", inputLen, expectedLen);
    return 1;
}

// 배열 비교
int assertEqualIntArray(int input[], int inputLen, int expected[], int expectedLen) {
    if (inputLen != expectedLen) {
        printf("❌ FAIL: Expected length %d but got %d\n", expectedLen, inputLen);
        return 0;
    }
    for (int i = 0; i < inputLen; i++) {
        if (input[i] != expected[i]) {
            printf("❌ FAIL: Arrays differ at index %d (expected %d, got %d)\n", i, expected[i], input[i]);
            return 0;
        }
    }
    printf("✅ PASS: Arrays match\n");
    return 1;
}

// 특정 값 포함 여부
int assertCharContaining(char *input, char expected) {
    int i = 0;
    while (input[i] != '\0') {
        if (input[i] == expected) {
            printf("✅ PASS: Expected %c is in Index %d\n", expected, i);
            return 1;
        }
        i++;
    }
    printf("❌ FAIL: Expected char %c doesn't exist\n", expected);
    return 0;
}

// 예외 처리
void try() {
    printf("🚨 에러 발생!\n");
    longjmp(jump, 1);
}

int assertMallocIsNotNull(void *input) {
    if (input == NULL) {
        printf("❌ FAIL: Memory Allocation has been failed\n");
        return 0;
    }
    printf("✅ PASS: Expected Location %p exist\n",&input);
    return 1;
}


// 테스트 실행
void runTests() {
    if (setjmp(jump) == 0) {
        assertEqualString("hello", "hello");
        assertEqualString("hello", "world");

        assertEqualInt(10, 10);
        assertEqualInt(10, 5);

        assertEqualCharLen("hello", "world");
        assertEqualCharLen("hi", "hello");
        assertEqualCharLen(NULL, "test");

        int intArray[3] = {1, 2, 3};
        int intArray2[3] = {1, 2, 3};
        assertEqualIntArray(intArray, 3, intArray2, 3);

        assertCharContaining("hello", 'o');
        assertCharContaining("hello", 'q');

        int *test = malloc(sizeof(int));
        assertMallocIsNotNull(test);
        free(test);
        try();
    }
}