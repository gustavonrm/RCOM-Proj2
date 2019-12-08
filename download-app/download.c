#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "FTP.h"

int main(int argc, char* argv[]){
    
    if( argc != 2 )
        print_usage(ERR_ARG); 

    printf("DOWNLOAD FTP - anonymous user\n"); 
    //VARS
    pressets pressets; 
    char link[256];
    int ftp_socket =0; //ftp socket fd - terminal window A
    int ftp_data_socket =0; //ftp socket to tranfer the data - terminal window B 
    int ret = 0; //error control  

    strcpy(link,argv[1]);  
    chopN(argv[1], 1); 

    process_string(link,&pressets);
    
    //debug
    printf("host: %s\n",pressets.host);
    printf("path: %s\n",pressets.path);
    printf("filename: %s\n",pressets.filename);
    // parse arguments build structures 

    //connect ftp 
    if((ftp_socket = connect_ftp(pressets.ip,pressets.port,TYPE_A)) < 0){
        print_error(ftp_socket); 
    }

    //login 
    if((ret = login_ftp(ftp_socket,pressets.username,pressets.password)) != 0 ){
        print_error(ret); 
    }

    //change directory
    //todo 

    //pasv - passive mode - and open socket on the other side 
    if((ftp_data_socket = ftp_pasv(ftp_socket)) <= 0 ){
        print_error(ftp_data_socket); 
    }

    //retr file path 
    if((ret = ftp_retr(ftp_socket,pressets.path)) != 0 ){
        print_error(ret); 
    }

    //DOWNLOAD 
    //todo

    //close 
    /*
    if((ret = ftp_close(ftp_socket)) != 0){
        print_error(ret);
    }
    */

    return 0; 
}