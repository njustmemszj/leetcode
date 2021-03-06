/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 递归解法, 参考了 OJ 上更优雅的写法
 */

#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strncpy() */
#include "c/data-structures/array.h"
#include "c/test.h"

void generate(char **rt, int *returnSize, int l, int r, char *tmp, int index) {
  if (l == 0 && r == 0) {
    tmp[index] = '\0';
    strncpy(rt[(*returnSize)++] = malloc(index + 1), tmp, index + 1);
    return;
  }

  if (l > 0) {
    tmp[index] = '(';
    generate(rt, returnSize, l-1, r, tmp, index+1);
  }

  if (r > 0 && r > l) {
    tmp[index] = ')';
    generate(rt, returnSize, l, r-1, tmp, index+1);
  }
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **generateParenthesis(int n, int *returnSize) {
  char **rt = malloc(sizeof(char*) * 5000);  /* TODO: 如何根据N计算出最大容量 */
  char *tmp = malloc(sizeof(char) * (2*n+1));
  *returnSize = 0;
  generate(rt, returnSize, n, n, tmp, 0);
  free(tmp);
  return rt;
}

void test(const char* expect, int n) {
  int returnSize;
  char** actual = generateParenthesis(n, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(actual, returnSize, ARRAY_STRING));
}

int main(void) {
  test("[((())),(()()),(())(),()(()),()()()]", 3);

  return testOutput();
}
