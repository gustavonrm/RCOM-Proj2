#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main(int argc, char* argv[]){
    
    if( argc != 2 )
        print_usage(ERR_ARG); 

    printf("DOWNLOAD FTP - anonymous user\n"); 
    //VARS
    pressets pressets; 
    char link[256];
    strcpy(link,argv[1]);  
    chopN(argv[1], 1); 

    process_string(link,&pressets);
 
    printf("host: %s\n",pressets.host);
    printf("path: %s\n",pressets.path);
    printf("filename: %s\n",pressets.filename);
    // parse arguments build structures 

    //login 

    //pasv 

    //login onthe other side with the X*256+Y

    //retr file path 

    //DOWNLOAD 

    //close 

    return 0; 

}