/*
*  In some other file, make the following a global variable:
*  "
*  FILE *gel_dbg_stream = NULL;
*  "
*  And somewhere else define (non-global):
*  "
    gel_dbg_stream = stdout;
    "
    or desired output file of choice instead of stdout.
*/


#ifndef GEL_DBG_H
#define GEL_DBG_H
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


extern FILE *gel_dbg_stream;

#define RESET "\x1b[0m"
#define MSG_COLOR "\x1b[96m"
#define DIR_COLOR "\x1b[90m"
#define RED_COLOR "\x1b[31m"
#define GREEN_COLOR "\x1b[32m"

#define DIR_TERM_FORMAT DIR_COLOR "[%s/%s:%d] " MSG_COLOR "%s" RESET "\n\r" RESET
#define DIR_FILE_FORMAT  "[%s/%s:%d] %s \n"
#define DIR_TERMS __FILE_NAME__, __func__, __LINE__


void die(const char *msg);


/** General dbg **/
#ifndef NDEBUG
#define dbg(fmt, ...)\
do{\
if (gel_dbg_stream != stdout){\
fprintf(gel_dbg_stream,  "[%s/%s:%d] " fmt "\n", DIR_TERMS, __VA_ARGS__);\
}else{\
fprintf(gel_dbg_stream,  DIR_COLOR "[%s/%s:%d] " MSG_COLOR fmt "\n\r", DIR_TERMS, __VA_ARGS__);\
}\
fprintf(gel_dbg_stream, RESET);\
fflush(gel_dbg_stream);\
}while (0)
#endif
#ifdef NDEBUG
#define dbg(msg, ...) {}
#endif

/** die errors **/
#define dbgCheck(x)\
int rawSuccess = x;\
if (rawSuccess){\
dbg(RED_COLOR "[ERROR] %d", rawSuccess);\
die(#x);\
}else{\
dbg( "[PASS] %d", rawSuccess);\
}



/** Message debug **/
#ifndef NDEBUG
#define dbgm(msg)\
do{\
if (gel_dbg_stream != stdout){\
fprintf(gel_dbg_stream, DIR_FILE_FORMAT ,DIR_TERMS ,msg  );\
fflush(gel_dbg_stream);\
}else{\
fprintf(gel_dbg_stream, DIR_TERM_FORMAT ,DIR_TERMS ,msg  );\
}\
} while (0)
#endif
#ifdef NDEBUG
#define dbgm(msg) {}
#endif


void die(const char *msg) {
    perror(msg);
    exit(-1);
}


#endif //GEL_DBG_H
