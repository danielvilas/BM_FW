#ifndef CONFIG_H
#define CONFIG_H
typedef struct sPlatform tPlatform;
typedef tPlatform* pPlatform;

struct sPlatform{
    char* name;
    char* host;
    char* user;
    char* key;
    pPlatform next;
};

typedef struct sProtocol tProtocol;
typedef tProtocol* pProtocol;

struct sProtocol{
    char* name;
    char* param;
    pProtocol next;
};
typedef struct sLang tLang;
typedef tLang* pLang;

struct sLang{
    char* name;
    char* dir;
    char* cmd;
    pLang next;
};

struct sConfig{
    char* sshCmd;
    char* datalogerCmd;
    pPlatform firstPlatform;
    pProtocol firstProtocol;
    pLang firstLang;
};

typedef struct sConfig tConfig;
typedef tConfig* pConfig;

int readYaml(char filename[], pConfig cfgM);
void printConfig(pConfig cfg);
#endif //CONFIG_H