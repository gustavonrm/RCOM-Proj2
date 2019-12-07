#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main(int argc, char* argv[]){
    
    if( argc != 2 )
        print_usage(ERR_ARG); 

    printf("DOWNLOAD FTP - anonymous user\n"); 

    pressets pressets; 
    process_string(argv[1],&pressets);
    // parse arguments build structures 

    //login 

    //pasv 

    //login onthe other side with the X*256+Y

    //retr file path 

    //DOWNLOAD 

    //close 

    return 0; 

}