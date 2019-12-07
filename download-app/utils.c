#include "utils.h"

void process_string(char* argv, pressets* pressets){
    
    //todo check url integrity 
    printf("%s\n",argv); 
    remove_ftp_head(argv); 
    printf("%s\n",argv); 

    if(true){ /*credentials*/
    //user anonymous 
    memcpy(pressets->username,"anonymous",strlen("anonymous"));
    memcpy(pressets->password,"something",strlen("something")); //any password works
    } //todo other users? 

    //configs

}

void remove_ftp_head(char* argv){
    chopN(argv,6);
}

//cut string first n elems 
size_t chopN(char *str, size_t n)
{
    assert(n != 0 && str != 0);
    size_t len = strlen(str);
    if (n > len)
        n = len;
    memmove(str, str+n, len - n + 1);
    return(len - n);
}

void print_usage(int error){
    printf("Usage: download [ftp://<host>/<path>]\n host = ftp.up.pt/ \n path = file\n"); 
    exit(error); 
}