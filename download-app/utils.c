#include "utils.h"

//todo swap void to int and make error control 

void process_string(char* link, pressets* pressets){
    
    //todo check url integrity 
    printf("%s\n",link); 
    remove_ftp_head(link); 
    printf("%s\n",link); 

    if(true){ /*credentials*/
    //user anonymous 
    memcpy(pressets->username,"anonymous",strlen("anonymous"));
    memcpy(pressets->password,"something",strlen("something")); //any password works
    } //todo other users? 

    //host
    char c = '/'; 
    char* host = get_string_until_char(link,c);
    memcpy(pressets->host,host,strlen(host)); 
    printf("%s\n",link); 

    //path 
    char *path = link;  
    memcpy(pressets->path,path,strlen(path)); 

    //filename
    get_file_name(link);
    memcpy(pressets->filename,link,strlen(link)); 
    
    //ip 
    char *ip = getIp(pressets->host);
    memcpy(pressets->ip, ip, strlen(ip));

    //create port
    pressets->port = PORT_VAL;  //default port value 'telnet ftp.fe.up.pt 21'
}
char* get_string_until_char(char* link, char c){
    int i = 0; 
    char * ret = (char *) malloc(strlen(link)); 
    for(i=0; i < (int)strlen(link); i++){
        if(link[i] == c)
            break;
        ret[i]=link[i];
    }
    chopN(link,i+1); 
    return ret; 
}

void get_file_name(char * link){
    int pos = 0; 
    for(int i = 0; i < (int) strlen(link); i++){
        if(link[i] == '/')
            pos = i; 
    }
    chopN(link, pos+1); 
}

void remove_ftp_head(char* link){
    chopN(link,6);
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

char* getIp(char * hostname){
    struct hostent *h;

    if ((h=gethostbyname(hostname)) == NULL) {  
        herror("gethostbyname");
        exit(1);
    }
    char* ret = inet_ntoa(*((struct in_addr *)h->h_addr));
    printf("Host name  : %s\n", h->h_name);
    printf("IP Address : %s\n",ret);

    return ret; 
}
