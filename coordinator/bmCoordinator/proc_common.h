#ifndef PROC_COMMON_H
#define PROC_COMMON_H

#include <unistd.h>
#include <stdbool.h>

bool isStarted(pid_t pid);
int waitForPid(pid_t);
#endif //PROC_COMMON_H