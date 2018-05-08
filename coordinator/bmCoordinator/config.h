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

struct sConfig{
    char* sshCmd;
    char* datalogerCmd;
    pPlatform firstPlatform;
};

typedef struct sConfig tConfig;
typedef tConfig* pConfig;

int readYaml(char filename[], pConfig cfgM);
void printConfig(pConfig cfg);
#endif //CONFIG_H