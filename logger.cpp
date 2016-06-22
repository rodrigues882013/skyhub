#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG "DEBUG"
#define ERROR "ERROR"
#define WARNING "WARNING"
#define INFO "INFO"
#define ASSERTION_ERROR "ASSERTION_ERROR"
#define SUCCESS "SUCCESS"

void logger(const char* tag, const char* message) {
   time_t now;
   time(&now);
   printf("[%s]: %s\n", tag, message);
}
