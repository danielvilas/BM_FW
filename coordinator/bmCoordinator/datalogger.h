#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <unistd.h>
#include "proc_common.h"
#include "config.h"
pid_t startDataLogger(pProcess proc,pConfig cfg, pPlatform plat, pLang lang, pProtocol proto,int i);
int closeDataLogger(pProcess proc);

#endif //DATALOGGER_H