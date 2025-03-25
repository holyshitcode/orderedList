#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <setjmp.h>
#include <stdlib.h>

// 문자열 비교
int assertEqualString(char *input, char *expected);

// 정수 비교
int assertEqualInt(int input, int expected);

// 문자열 길이 비교
int assertEqualCharLen(char *input, char *expected);

// 배열 비교
int assertEqualIntArray(int input[], int inputLen, int expected[], int expectedLen);
int assertEqualDoubleArray(double input[], double inputLen, double expected[], double expectedLen);
int assertEqualLongArray(long input[], long inputLen, long expected[], long expectedLen);

// 특정 값 포함 여부
int assertCharContaining(char *input, char expected);
int assertStrContainingStr(char *input, char *expected);
int assertIntArrayContainingInt(int input[], int inputLen, int expected);
int assertDoubleArrayContainingDouble(double input[], int inputLen, double expected);
int assertLongArrayContainingLong(long input[], int inputLen, long expected);

// 메모리 할당 확인
int assertMallocIsNotNull(void *input);

// 예외 처리
extern jmp_buf jump;
void try();

// 테스트 실행
void runTests();

#endif // UNIT_TEST_H