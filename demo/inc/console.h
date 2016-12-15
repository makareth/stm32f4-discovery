#pragma once

#include <stdarg.h>
#include <stdio.h>

#define LOG_MAX_FMT_SIZE    256

int my_log ( int level , char *name, const char *fmt, ... );

