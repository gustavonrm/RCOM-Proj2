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

#define true 1
#define false 2

#define ERR_ARG 1
#define ERR_FTP_NAME 2

#define PORT_VAL 21

/*====== STRUCTS ======*/
typedef struct pressets{
    char username[256]; 
    char password[256]; 
    char host[256]; 
    char ip[256];
    char path[256];
    char filename[256];
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

//ip 
char* getIp(char* hostname);

#endif