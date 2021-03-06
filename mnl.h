#ifndef MNL_H_GUARD
#define MNL_H_GUARD
#ifndef BUFFER_H
#define BUFFER_H
#include <stddef.h>
//structures
typedef struct Buffer{
unsigned char *data;
short mode;
size_t size;
size_t at;
}BUFFER,Buffer;
#define BLOCK_DOUBLE 1
#define BLOCK_DYNAMIC 2

//External Functions
Buffer *buffer_init(size_t chunkSize , short mode);
short buffer_grow(Buffer *buffer,size_t growBy);
short buffer_cat(Buffer *buffer, unsigned char *data , size_t dataSize);
void buffer_destroy(Buffer *buffer , short clear);
unsigned char *buffer_getRaw(Buffer *buffer);
short buffer_shrink(Buffer *buffer,size_t shrinkBy);
short buffer_scrape(Buffer *buffer, char *startIdent , char *endIdent , char **res , size_t *size);
//This function is built with the idea of parsing C-Strings , or any other string for that matter, It can parse binary data though.


//Internal Functions
size_t _buffer_find(Buffer *buffer , char *ident ,size_t identLen, short *err);
//This function is built with the idea of parsing C-Strings , or any other string for that matter, It can parse binary data though.

#endif
#ifndef CHTTP_HEADER_GUARD
#define CHTTP_HEADER_GUARD
// Includes
#include <stdlib.h>
#include <math.h>
#include <string.h>
// #include <bsd/string.h>
#include <stdio.h>
// Defines
#define CHTTPE_OK 0
#define CHTTPE_GROW 1
#define CHTTPE_LOOKUP 2
// Structures
typedef struct chttp{
	char *buffer;
	size_t size;
	}custom_http, *p_custom_http;
// Functions
void *chttp_init();
void chttp_destroy(p_custom_http chttp);
const short chttp_add_header(p_custom_http chttp, const char *data, const size_t size);
const short chttp_add(p_custom_http chttp, const char *data, const size_t size);
const short chttp_grow(const p_custom_http chttp, const size_t size);
char *chttp_lookup(const p_custom_http chttp, const char *key);
const short chttp_finalise(const p_custom_http chttp , const char *data, const size_t size);
char *chttp_getData(const p_custom_http chttp);
const char *_chttp_find(const char *buffer, const size_t bufferSize, const char *find, const size_t findSize);
#endif
/*
	Stores thread id's using vvectors.
*/

#ifndef CONTROLLER
#define CONTROLLER
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../lib/vVector.h"
// DEFINES
#define THREAD_SIGNAL_READY 0

// STRUCTURES
typedef struct signalStruct{
	unsigned short thread_signal;
	unsigned short master_signal;
	pthread_mutex_t *_mutex_thread_signal;
	pthread_mutex_t *_mutex_master_signal;
}signalStruct, *p_signalStruct;

typedef struct threadController{
	p_vvector threads;
}threadController , *p_threadController;

// FUNCTIONS (THREAD CONTROLLER)
threadController *threadController_init();
void threadController_destroy(threadController *tc);
short threadController_pushback(const threadController *tc,const pthread_t id);
void threadController_stopAll(const threadController *tc);

// FUNCTIONS (SIGNALS)
p_signalStruct signal_init();
void signal_destroy(p_signalStruct signalStruct);
void signal_set_thread(const p_signalStruct signalStruct,const unsigned short value);
void signal_set_master(const p_signalStruct signalStruct,const unsigned short value);
const unsigned short signal_get_thread(const p_signalStruct signalStruct);
const unsigned short signal_get_master(const p_signalStruct signalStruct);


#endif
#ifndef C_DEBUG_H
#define C_DEBUG_H
#include <stddef.h>
// DEFINES
#define DEBUG_PORT 14

// FUNCTIONS
void debugMsg( const char *msg , short critical );
const char *_genDbgMsg( const char *msg );

char *genData( char Char , size_t Size );
char *genData_addDelim( char Char , char Delim , size_t Size );
char *genData_complicatedStr(size_t Size);
short genData_evalComplicatedStr(char *Data , size_t Size );
#endif
#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <pthread.h>
// DEFINES
#define CHUNK_SIZE 265

// STRUCTURES
typedef struct logger{
	FILE *file;
	pthread_mutex_t *mutex_stdOut;
	pthread_mutex_t *mutex_logOut;
}logger;

// FUNCTIONS
logger *logger_init(const char *file);
void logger_destroy(logger *log);
void logIt(logger* log , const char *string);

#endif
#ifndef NETWORKING_H
#define NETWORKING_H
#include <sys/socket.h>
//DEFINES
#define SOCKET_MAGIC_NUMBER 1


// FUNCTIONS
#ifdef __linux__
/**
 * Returns the first ipv4/ipv6 address associated with a hostname.
 * @param  Hostname The hostname to resolve.
 * @param  strIP    The buffer to write the ip to.
 * @param  AI_FAM   AF_INET / AF_INET6
 * @return          Returns 1 on success.
 */
short getAddrP(const char *Hostname,char *strIP,const int AI_FAM);
#endif

/**
 * Receives all incoming data on a BLOCKING socket.
 * @param  Socket Socket to receive on.
 * @param  Buffer Buffer to receive to (preallocated).
 * @param  Size   The amount of bytes to receive
 * @param  Flags  Socket Flags
 * @return        The amount of bytes returned / or -1 for an error
 */
ssize_t recvAllFixed(int Socket , char *Buffer , const size_t Size , const int Flags);

/**
 * Sends all incoming data on a BLOCKING socket ( This function may be redundant).
 * @param  Socket Socket to send to.
 * @param  Buffer Buffer to send to (preallocated).
 * @param  Size   The amount of bytes to receive
 * @param  Flags  Socket Flags
 * @return        The amount of bytes returned / or -1 for an error
 */
ssize_t sendAllFixed(int Socket , char *Buffer , const size_t Size , int Flags);
#endif
#ifndef VVECTOR_H_GUARD
#define VVECTOR_H_GUARD
// Includes
#include <stdlib.h>

// Constants
#define VVECTOR_CHUNK_SIZE 250

// Error Constants
#define VVECTORE_OK 0
#define VVECTORE_GROW 1


// Structures
typedef struct vvector{
	void **data;
	size_t chunkSize; // Chunk size will be doubled every time it's reached.
	size_t elements;
	} *p_vvector , vvector;

// Functions
p_vvector vvector_init();
p_vvector vvector_init_adv(const size_t chunkSize);
void vvector_free(p_vvector vector);

short _vvector_grow(const p_vvector vector); // _because it's an internal function.
short vvector_push(const p_vvector vector, const void *element);
void *vvector_pop(const p_vvector vector);
void *vvector_at(const p_vvector vector, const size_t i);


#endif
#endif