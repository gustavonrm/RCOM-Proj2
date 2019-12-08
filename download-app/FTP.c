#include "FTP.h"

int connect_ftp(char * ip, int port){
    int	sockfd;
	struct sockaddr_in server_addr;
	char buf[256]; 
	
    //*remove the stupid blank at the end
    ip[strlen(ip)-1] = 0;

	/*server address handling*/
	bzero((char*)&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);/*32 bit Internet address network byte ordered*/
	server_addr.sin_port = htons(port);/*server TCP port must be network byte ordered */
    
	/*open an TCP socket*/
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
         return ERR_FTP_SOCKET; 
    }
	/*connect to the server*/
    if(connect(sockfd, (struct sockaddr *)&server_addr,sizeof(server_addr)) < 0){
        return ERR_FTP_SOCKET; 
	}

	if(ftp_read(sockfd,buf,strlen(buf)) != 0 ){
		return ERR_FTP_RD; 
	}

	return sockfd;
    //todo add further
	
	/*

	bytes = write(sockfd, buf, strlen(buf));
	printf("Bytes escritos %d\n", bytes);

	close(sockfd);
	*/

}

int login_ftp(int socket_fd,char * username,char * password){

	//vars
	int bytes; 
	char buf[256]; 

	//first write username 

	//>user <username>
	sprintf(buf, "user %s\r\n", username);

	if((bytes = write(socket_fd, buf, strlen(buf)))<=0 ){
		return ERR_FTP_WR;
	}

	printf("\nUSERNAME - Bytes written %d\n", bytes);

	if(ftp_read(socket_fd,buf,strlen(buf)) != 0 ){
		return ERR_FTP_RD; 
	}

	//clear buffer 
	memset(buf, 0,strlen(buf)); 

	//second write password
	//>pass <password>	
	sprintf(buf, "pass %s\r\n",password);

	if((bytes = write(socket_fd,buf, strlen(buf)))<=0 ){
			return ERR_FTP_WR;
	}
	printf("\nPASSWORD - Bytes written %d\n", bytes);

	if(ftp_read(socket_fd,buf,strlen(buf)) != 0 ){
		return ERR_FTP_RD; 
	}

	//clear buffer
	memset(buf, 0,strlen(buf)); 

	return 0; 
}

//todo 

int ftp_close(int socket_fd){
	int bytes; 
	char buf[256];

	if (ftp_read(socket_fd, buf, sizeof(buf)) != 0 ) {
		return ERR_FTP_RD;
	}

	sprintf(buf, "quit\r\n");

	if((bytes = write(socket_fd,buf, strlen(buf)))<=0 ){
			return ERR_FTP_WR;
	}
	printf("\nCLOSE - Bytes written %d\n", bytes);

	close(socket_fd);
	return 0; 
}

int ftp_read(int socket_fd,char * str, size_t size){
    FILE * f = fdopen(socket_fd,"r"); 

    do {
		memset(str, 0, size);
		str = fgets(str, size, f);
		printf("%s", str);
	} while (!('1' <= str[0] && str[0] <= '5') || str[3] != ' ');

	return 0;
}