/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef __STACK_H
#define __STACK_H

#include <string.h>  /* memcpy() */

#ifndef STACK_INIT_SIZE
#define STACK_INIT_SIZE 64
#endif

#define PUTC(c, ch)      do { *(char*)stackPush(c, sizeof(char)) = (ch); } while (0)
#define PUTCP(c, p)      memcpy(stackPush(c, sizeof(char*)), p, sizeof(char*))
#define PUTS(c, s, len)  do { if (len > 0) memcpy(stackPush(c, len), s, len); } while (0)
#define PUTI(c, i)       memcpy(stackPush(c, sizeof(int)), i, sizeof(int))
#define PUTIP(c, p)      memcpy(stackPush(c, sizeof(int*)), p, sizeof(int*))

typedef struct {
  char *stack;
  size_t size, top;
} context;

context stackMake(void);
void* stackPush(context* c, size_t size);

#endif  /* __STACK_H */
