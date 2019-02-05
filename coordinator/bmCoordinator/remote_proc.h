#ifndef REMOTE_PROC_H
#define REMOTE_PROC_H

#include <unistd.h>
#include "proc_common.h"
#include "config.h"

pid_t startRemoteProc(pProcess proc,pConfig cfg, pPlatform plat, pLang lang, pProtocol proto,int i);
int getRemoteProc(pProcess proc,pConfig cfg, pPlatform plat, pLang lang, pProtocol proto,int i);
int closeRemoteProc(pProcess proc);

#endif //REMOTE_PROC_H