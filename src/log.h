#pragma once

#ifdef PLATFORM_ARM_QEMU
  #include "rtdbg.h"
  #define LOG LOG_D
#else
  //#include "logger.h"
#include "lv_log.h"
#define LOG LV_LOG_TRACE
#define LOG_I LV_LOG_INFO
#define LOG_W LV_LOG_WARN
#define LOG_E LV_LOG_ERROR
#endif
