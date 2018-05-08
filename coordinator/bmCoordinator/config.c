#include "config.h"
#include <yaml.h>

#define STR_PLATFORMS "platforms"
#define STR_SSH_CMD "sshCmd"
#define STR_DATALOGGER_CMD "dataloggerCmd"
#define STR_NAME_PAR "name"
#define STR_HOST_PAR "host"
#define STR_USER_PAR "user"
#define STR_KEY_PAR "key"

void debug(yaml_token_t token){
        switch(token.type)
    {
    /* Stream start/end */
    case YAML_STREAM_START_TOKEN: puts("STREAM START"); break;
    case YAML_STREAM_END_TOKEN:   puts("STREAM END");   break;
    /* Token types (read before actual token) */
    case YAML_KEY_TOKEN:   printf("(Key token)   "); break;
    case YAML_VALUE_TOKEN: printf("(Value token) "); break;
    /* Block delimeters */
    case YAML_BLOCK_SEQUENCE_START_TOKEN: puts("<b>Start Block (Sequence)</b>"); break;
    case YAML_BLOCK_ENTRY_TOKEN:          puts("<b>Start Block (Entry)</b>");    break;
    case YAML_BLOCK_END_TOKEN:            puts("<b>End block</b>");              break;
    /* Data */
    case YAML_BLOCK_MAPPING_START_TOKEN:  puts("[Block mapping]");            break;
    case YAML_SCALAR_TOKEN:  printf("scalar %s \n", token.data.scalar.value); break;
    /* Others */
    default:
      printf("Got token of type %d\n", token.type);
    }
}

enum {NONE, SSH_CMD, DL_CMD,NAME_PAR, HOST_PAR, USER_PAR, KEY_PAR} lastParam;
enum {KEY,VALUE} lastToken;
enum eMode {
    MODE_START=0,
    MODE_GLOBAL,
    MODE_PLATFORMS,
    MODE_UNKNOWK
} parser_mode;

char* strClone(yaml_char_t* in){
    int s= strlen((const char*)in);
    char* ret = malloc((s+1)*sizeof(char));
    memcpy(ret,in,s);
    return ret;
}

void parseGlobal(yaml_token_t token, pConfig cfg){
    if(token.type==YAML_BLOCK_MAPPING_START_TOKEN ||
    token.type==YAML_KEY_TOKEN || token.type==YAML_VALUE_TOKEN)return;
    
    if(token.type==YAML_SCALAR_TOKEN){
        if(strcmp(STR_PLATFORMS,(const char*)token.data.scalar.value)==0){
            parser_mode=MODE_PLATFORMS;
            lastParam=NONE;
            return;
        }
        if(lastToken==KEY){
            if(strcmp(STR_SSH_CMD,(const char*)token.data.scalar.value)==0){
                lastParam=SSH_CMD;
            }else if(strcmp(STR_DATALOGGER_CMD,(const char*)token.data.scalar.value)==0){
                lastParam=DL_CMD;
            }
            return;
        }
        if(lastToken==VALUE){
            if(lastParam==SSH_CMD){
                cfg->sshCmd=strClone(token.data.scalar.value);
            }else if(lastParam==DL_CMD){
                cfg->datalogerCmd=strClone(token.data.scalar.value);
            }
            return;
        }
        printf("scalar %s \n", token.data.scalar.value);
        
        return;
    }
    debug(token);
}
enum{PLAT_NONE,PLAT_START,PLAT_DATA} platform_mode;
pPlatform lastPlatform;

void parsePlatform(yaml_token_t token, pConfig cfg){
    if(token.type==YAML_KEY_TOKEN 
    || token.type==YAML_VALUE_TOKEN
    || token.type==YAML_BLOCK_END_TOKEN
    || token.type==YAML_BLOCK_MAPPING_START_TOKEN)return;
    
    if(token.type==YAML_BLOCK_SEQUENCE_START_TOKEN){
        platform_mode=PLAT_START;
        return;
    }
    if(token.type==YAML_BLOCK_ENTRY_TOKEN){
        pPlatform newPlatform = malloc(sizeof(tPlatform));
        newPlatform->next=NULL;
        if(platform_mode==PLAT_START){
            cfg->firstPlatform=newPlatform;
            platform_mode=PLAT_DATA;
        }else if(platform_mode==PLAT_DATA){
            lastPlatform->next=newPlatform;
        }
        lastPlatform=newPlatform;
        return;
    }
    if(token.type==YAML_SCALAR_TOKEN){
        if(platform_mode!=PLAT_DATA){
            printf("Error Scalar %s \n", token.data.scalar.value);
            return;    
        }
        if(lastToken==KEY){
            if(strcmp(STR_NAME_PAR,(const char*)token.data.scalar.value)==0){
                lastParam=NAME_PAR;
            }else if(strcmp(STR_HOST_PAR,(const char*)token.data.scalar.value)==0){
                lastParam=HOST_PAR;
            }else if(strcmp(STR_USER_PAR,(const char*)token.data.scalar.value)==0){
                lastParam=USER_PAR;
            }else if(strcmp(STR_KEY_PAR,(const char*)token.data.scalar.value)==0){
                lastParam=KEY_PAR;
            }
            return;
        }
         if(lastToken==VALUE){
            if(lastParam==NAME_PAR){
                lastPlatform->name=strClone(token.data.scalar.value);
            }else if(lastParam==HOST_PAR){
                lastPlatform->host=strClone(token.data.scalar.value);
            }else if(lastParam==USER_PAR){
                lastPlatform->user=strClone(token.data.scalar.value);
            }else if(lastParam==KEY_PAR){
                lastPlatform->key=strClone(token.data.scalar.value);
            }
            return;
        }
        printf("Scalar %s \n", token.data.scalar.value);
        return;
    }
    debug(token);
}

int readYaml (char filename[], pConfig cfg){
    FILE *fh = fopen(filename, "r");
  yaml_parser_t parser;
  yaml_token_t token;
  parser_mode=MODE_START;
  platform_mode=PLAT_NONE;

  /* Initialize parser */
  if(!yaml_parser_initialize(&parser))
    fputs("Failed to initialize parser!\n", stderr);
  if(fh == NULL)
    fputs("Failed to open file!\n", stderr);

  /* Set input file */
  yaml_parser_set_input_file(&parser, fh);

  /* CODE HERE */
  do {
    yaml_parser_scan(&parser, &token);
    if(token.type==YAML_KEY_TOKEN){
        lastToken=KEY;
    }
    if(token.type==YAML_VALUE_TOKEN){
        lastToken=VALUE;
    }
    if(parser_mode==MODE_START){
        if(token.type==YAML_STREAM_START_TOKEN){
            parser_mode=MODE_GLOBAL;
        }else{
            debug(token);
        }
    }else if(parser_mode==MODE_GLOBAL){
        parseGlobal(token, cfg);
    }else if(parser_mode==MODE_PLATFORMS){
        parsePlatform(token, cfg);
    }else{
        debug(token);
    }
    if(token.type != YAML_STREAM_END_TOKEN)
      yaml_token_delete(&token);
  } while(token.type != YAML_STREAM_END_TOKEN);
  yaml_token_delete(&token);
  /* END new code */
  /* Cleanup */
  yaml_parser_delete(&parser);
  fclose(fh);
  return 0;
}

void printConfig(pConfig cfg){
    printf(STR_SSH_CMD": %s\n",cfg->sshCmd);
    printf(STR_DATALOGGER_CMD": %s\n",cfg->datalogerCmd);
    printf(STR_PLATFORMS":\n");
    pPlatform ptr = cfg->firstPlatform;
    while(ptr!=NULL){
        printf(" - "STR_NAME_PAR": %s\n",ptr->name);
        printf("   "STR_HOST_PAR": %s\n",ptr->host);
        printf("   "STR_USER_PAR": %s\n",ptr->user);
        printf("   "STR_KEY_PAR": %s\n",ptr->key);
        ptr=ptr->next;
    }
}