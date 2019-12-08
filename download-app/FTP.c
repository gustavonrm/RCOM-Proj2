#include "FTP.h"

void connect_ftp(char * ip, int port){
    int	sockfd;
	struct sockaddr_in server_addr;
	char buf[] = "Mensagem de teste na travessia da pilha TCP/IP\n";  
	int	bytes;
	
    //*remove the stupid blank at the end
    ip[strlen(ip)-1] = 0;
	/*server address handling*/
	bzero((char*)&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);/*32 bit Internet address network byte ordered*/
	server_addr.sin_port = htons(port);/*server TCP port must be network byte ordered */\
    
	/*open an TCP socket*/
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
    	perror("socket()");
        exit(0);
    }
	/*connect to the server*/
    if(connect(sockfd, (struct sockaddr *)&server_addr,sizeof(server_addr)) < 0){
    	perror("connect()");
        exit(0);
	}
    //todo add further
    /*send a string to the server*/
	bytes = write(sockfd, buf, strlen(buf));
	printf("Bytes escritos %d\n", bytes);

	close(sockfd);
	exit(0);
}