#pragma once
#include <stdio.h>
#include <stdarg.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

void ñustValidatedInput(const char* premise, int argsCount, const char* format, ...);