#include "utils.h"

//todo swap void to int and make error control 

void process_string(char* link, pressets* pressets){
    
    //todo check url integrity 
    printf("%s\n",link); 
    remove_ftp_head(link); 
    printf("%s\n",link); 

    char anonymous[]= "anonymous"; 
    char password[] = " "; 

    if((strchr(link,':') == NULL) && (strchr(link,'@') == NULL)){ /*credentials*/ //todo if uses brackes chagne for them
     //user anonymous 
        memset(pressets->username, 0,strlen(anonymous)); 
        memcpy(pressets->username,anonymous,strlen(anonymous)+1);
        memset(pressets->password, 0,strlen(password)); 
        memcpy(pressets->password,password,strlen(password)+1); //any password works
    }else {
        puts("login");
        //chopN(link,1);  //erase open bracket
        puts(link);
        char* username = get_string_until_char(link,':');
        memset(pressets->username, 0,strlen(username)); 
        memcpy(pressets->username,username,strlen(username)+1);
        char* password = get_string_until_char(link,'@');
        memset(pressets->password, 0,strlen(password)); 
        memcpy(pressets->password,password,strlen(password)+1); //any password works
        //chopN(link,1); //erase close bracket 
        puts(link);
    }

    //host
    char c = '/'; 
    char* host = get_string_until_char(link,c);
    memset(pressets->host, 0,strlen(host)+1); 
    memcpy(pressets->host,host,strlen(host)); 
    printf("%s\n",link); 

    //path 
    char *path = link; 
    memset(pressets->path, 0,strlen(path));  
    memcpy(pressets->path,path,strlen(path)+1); 

    //filename
    get_file_name(link);
    memset(pressets->filename, 0,strlen(link)); 
    memcpy(pressets->filename,link,strlen(link)+1); 
    
    //ip 
puts(host);
puts(pressets->host);
    char *ip = getIp(pressets->host);
    memset(pressets->ip, 0,strlen(ip)); 
    memcpy(pressets->ip, ip, strlen(ip)+1);

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

void print_error(int error){
    printf("ERROR: %d\n",error); 
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
