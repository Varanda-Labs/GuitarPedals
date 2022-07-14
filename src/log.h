#pragma once
#include <stdio.h>

#if 1
#define LOG         printf
#define LOG_E       printf
#define LOG_I       printf
#define LOG_W       printf
#else
#define LOG(...)         do {/* dummy */} while(0)
#define LOG_E(...)       do {/* dummy */} while(0)
#define LOG_I (...)       do {/* dummy */} while(0)
#define LOG_W(...)       do {/* dummy */} while(0)
#endif
