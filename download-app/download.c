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
    int ftp_socket =0; //ftp socket fd
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
    if((ftp_socket = connect_ftp(pressets.ip,pressets.port)) < 0){
        print_error(ftp_socket); 
    }

    //login 
    if((ret = login_ftp(ftp_socket,pressets.username,pressets.password)) != 0 ){
        print_error(ret); 
    }

    //pasv 
    //todo
    
    //login onthe other side with the X*256+Y
    //todo

    //retr file path 
    //todo

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