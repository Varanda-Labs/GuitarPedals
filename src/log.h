#pragma once

#ifdef PLATFORM_ARM_QEMU
  #include "rtdbg.h"
  #define LOG LOG_D
#else
  #include "logger.h"
#endif