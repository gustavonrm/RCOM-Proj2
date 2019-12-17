#ifndef FTP_H_
#define FTP_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <string.h>

#include "utils.h"

int connect_ftp(char * ip, int port,int sock_type); 
int login_ftp(int socket_fd,char * username,char * password);
int ftp_pasv(int socket_fd); 
int ftp_retr(int socket_fd,char * file); 
int ftp_download(int data_socket,char * file);
int ftp_close(int socket_fd); 

//aux 
int ftp_read(int socket_fd,char * str, size_t size);


#endif