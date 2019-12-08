#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>

/*====== MACROS =====*/

//bool
#define true 1
#define false 0

//errors
#define ERR_ARG -1
#define ERR_FTP_NAME -2
#define ERR_FTP_CONNECT -3
#define ERR_FTP_SOCKET -4
#define ERR_FTP_RD -5
#define ERR_FTP_WR -6
#define ERR_FTP_CLOSE -7
#define ERR_FTP_RD_DATA -8
#define ERR_FILE_WR -9
#define ERR_FILE_NOT_EXISTS -10

//values

#define PORT_VAL 21
#define BUFFER_SIZE 512

#define TYPE_A 1
#define TYPE_B 0

/*====== STRUCTS ======*/
typedef struct pressets{
    char username[256]; 
    char password[256]; 
    char host[256]; 
    char ip[256];
    char path[256];
    char filename[256]; //todo this is not needed maybe
    int port; 
}pressets;

/*====== FUNCTIONS =====*/

//string manipulation 
void process_string(char* link, pressets* pressets);
void remove_ftp_head(char* link);
char* get_string_until_char(char* link, char c);
void get_file_name(char * link);
//cut string first n elems 
size_t chopN(char *str, size_t n);
void print_usage(int error);
void print_error(int error); 

//ip 
char* getIp(char* hostname);

#endif