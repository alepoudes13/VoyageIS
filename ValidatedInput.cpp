#include "ValidatedInput.h"

void ñustValidatedInput(const char* premise, int argsCount, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result;
    do {
        printf(premise);
        result = vscanf(format, args);
        scanf("%*[^\n]");
    } while (result < argsCount);
    va_end(args);
}