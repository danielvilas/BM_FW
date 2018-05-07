#ifndef REMOTE_PROC_H
#define REMOTE_PROC_H

#include <unistd.h>
#include "proc_common.h"

pid_t startRemoteProc(pProcess proc);
int closeRemoteProc(pProcess proc);

#endif //REMOTE_PROC_H