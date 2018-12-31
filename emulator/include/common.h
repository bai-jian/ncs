#ifndef __COMMON_H__
#define __COMMON_H__

#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef uint32_t hwaddr_t;
typedef uint32_t swaddr_t;

typedef uint32_t segment_offset_t;
typedef uint32_t lgaddr_t;
typedef uint32_t lnaddr_t;
typedef uint32_t phyaddr_t;
typedef uint16_t ioaddr_t;
typedef uint32_t offset_t;

#define str_temp(x) #x
#define str(x) str_temp(x)

#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)

#define test(cond, ...) \
	do { \
		if(!(cond)) { \
			fflush(stdout); \
			fprintf(stderr, "\33[1;31m"); \
			fprintf(stderr, __VA_ARGS__); \
			fprintf(stderr, "\33[0m\n"); \
			assert(0); \
		} \
	} while(0)

#define Log(format,...) \
	fprintf(stdout, "\33[1;34m%s,%s,%d: " format "\33[0m\n", __FILE__, __func__, __LINE__, ## __VA_ARGS__), \
	fflush(stdout)

#endif