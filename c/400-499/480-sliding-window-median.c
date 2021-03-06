/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 维护一个有序的数组, 长度为k
 * 当窗口移动的时候, 移除一个旧了, 插入一个新的
 * 重复计算中位数
 */

#include <stdlib.h> /* malloc(), qsort() */
#include <string.h> /* memcpy() */
#include "c/data-structures/array.h"
#include "c/test.h"
#include "c/tools/compare.h"

void popAndPush(int* nums, int numsSize, int pop, int push) {
  if (pop == push) return;

  int i = 0;
  while (nums[i] != pop) i++;

  if (pop < push) {
    for (; i < numsSize-1; i++) {
      if (nums[i+1] >= push) {
        nums[i] = push;
        return;
      }
      nums[i] = nums[i+1];
    }
    nums[numsSize-1] = push;
  } else {
    for (; i > 0; i--) {
      if (nums[i-1] <= push) {
        nums[i] = push;
        return;
      }
      nums[i] = nums[i-1];
    }
    nums[0] = push;
  }
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
double *medianSlidingWindow(int *nums, int numsSize, int k, int *returnSize) {
  *returnSize = numsSize - k + 1;
  double *rtn = malloc(sizeof(double) * *returnSize);

  int *tmp = malloc(sizeof(int) * k);
  memcpy(tmp, nums, sizeof(int) * k);

  qsort(tmp, k, sizeof(int), compare_ints);

  for (int i = 0; i < *returnSize; i++) {
    if (i != 0) popAndPush(tmp, k, nums[i-1], nums[i+k-1]);
    if (k % 2 == 1) {
      rtn[i] = tmp[k/2];
    } else {
      int a = tmp[k/2 - 1], b = tmp[k/2];
      if ((a >> 31) ^ (b >> 31)) {
        rtn[i] = (a + b) / 2.0;
      } else {
        rtn[i] = a + (b - a) / 2.0;
      }
    }
  }

  free(tmp);
  return rtn;
}

void test(const char* expect, const char *str, int k) {
  arrayEntry *e = arrayParse1D(str, ARRAY_INT);
  int returnSize;
  double *a = medianSlidingWindow(arrayValue(e), arraySize(e), k, &returnSize);
  arrayEntry *rtn = arrayFrom1D(a, returnSize, ARRAY_DOUBLE);
  arraySetPrecision(rtn, 1);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString(rtn));

  arrayFree(e);
  arrayFree(rtn);
}

int main(void) {
  test("[1.0,-1.0,-1.0,3.0,5.0,6.0]",
       "[1,3,-1,-3,5,3,6,7]",
       3);

  return testOutput();
}
