//
// Created by Daniel Vilas Perulan on 2019-07-31.
//

#ifndef DATAEXTRACTOR_PROCESSINFLUX_H
#define DATAEXTRACTOR_PROCESSINFLUX_H

#include "../process.h"
#include "influxdb.h"

#define ENV_INFLUXDB_HOST "INFLUXDB_HOST"
#define ENV_INFLUXDB_PORT "INFLUXDB_PORT"
#define ENV_INFLUXDB_DB "INFLUXDB_DB"
#define ENV_INFLUXDB_USR "INFLUXDB_USR"
#define ENV_INFLUXDB_PWD "INFLUXDB_PWD"

pExecuteInfo executeOneInflux(char* dir, pConfig cfg, pName plat, pName lang, pName proto );
influx_client_t getClient();

#endif //DATAEXTRACTOR_PROCESSINFLUX_H
