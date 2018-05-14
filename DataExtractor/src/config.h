#ifndef CONFIG_H
#define CONFIG_H
typedef struct sName tName;
typedef tName* pName;

struct sName{
    char* name;
    pName next;
};


struct sConfig{
    int cycles;
    int interval;
    pName firstPlatform;
    pName firstProtocol;
    pName firstLang;
};

typedef struct sConfig tConfig;
typedef tConfig* pConfig;

int readYaml(char filename[], pConfig cfgM);
void printConfig(pConfig cfg);
#endif //CONFIG_H