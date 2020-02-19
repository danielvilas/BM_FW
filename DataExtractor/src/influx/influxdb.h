#ifndef INFLUXDB_H
#define INFLUXDB_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/*
  Usage:
    send_udp/post_http(c,
            INFLUX_MEAS("foo"),
            INFLUX_TAG("k", "v"), INFLUX_TAG("k2", "v2"),
            INFLUX_F_STR("s", "string"), INFLUX_F_FLT("f", 28.39, 2),

            INFLUX_MEAS("bar"),
            INFLUX_F_INT("i", 1048576), INFLUX_F_BOL("b", 1),
            INFLUX_TS(1512722735522840439),

            INFLUX_END);

  **NOTICE**: For best performance you should sort tags by key before sending them to the database.
              The sort should match the results from the [Go bytes.Compare function](https://golang.org/pkg/bytes/#Compare).
 */

#define INFLUX_MEAS(m)        IF_TYPE_MEAS, (m)
#define INFLUX_TAG(k, v)      IF_TYPE_TAG, (k), (v)
#define INFLUX_F_STR(k, v)    IF_TYPE_FIELD_STRING, (k), (v)
#define INFLUX_F_FLT(k, v, p) IF_TYPE_FIELD_FLOAT, (k), (double)(v), (int)(p)
#define INFLUX_F_INT(k, v)    IF_TYPE_FIELD_INTEGER, (k), (long long)(v)
#define INFLUX_F_BOL(k, v)    IF_TYPE_FIELD_BOOLEAN, (k), ((v) ? 1 : 0)
#define INFLUX_TS(ts)         IF_TYPE_TIMESTAMP, (long long)(ts)
#define INFLUX_END            IF_TYPE_ARG_END

typedef struct _influx_client_t
{
    char* host;
    int   port;
    char* db;  // http only
    char* usr; // http only [optional for auth]
    char* pwd; // http only [optional for auth]
} influx_client_t;

int format_line(char **buf, int *len, size_t used, ...);
int post_http(influx_client_t* c, ...);
int send_udp(influx_client_t* c, ...);

#define IF_TYPE_ARG_END       0
#define IF_TYPE_MEAS          1
#define IF_TYPE_TAG           2
#define IF_TYPE_FIELD_STRING  3
#define IF_TYPE_FIELD_FLOAT   4
#define IF_TYPE_FIELD_INTEGER 5
#define IF_TYPE_FIELD_BOOLEAN 6
#define IF_TYPE_TIMESTAMP     7

int _escaped_append(char** dest, size_t* len, size_t* used, const char* src, const char* escape_seq);
int _begin_line(char **buf);
int _format_line(char** buf, va_list ap);
int _format_line2(char** buf, va_list ap, size_t *, size_t);
int post_http_send_line(influx_client_t *c, char *buf, int len);
int send_udp_line(influx_client_t* c, char *line, int len);

#endif