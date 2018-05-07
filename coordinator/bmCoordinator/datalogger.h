#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <unistd.h>
#include "proc_common.h"
pid_t startDataLogger(pProcess proc);
int closeDataLogger(pProcess proc);

#endif //DATALOGGER_H