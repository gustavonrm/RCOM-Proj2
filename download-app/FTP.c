#include "FTP.h"

int connect_ftp(char * ip, int port,int sock_type){
    int	sockfd;
	struct sockaddr_in server_addr;
	char buf[BUFFER_SIZE]; 
	
    //*remove the stupid blank at the en
	if(sock_type)
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

	if(sock_type){
		if(ftp_read(sockfd,buf,sizeof(buf)) != 0 ){
			return ERR_FTP_RD; 
		}
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
	char buf[BUFFER_SIZE]; 

	//first write username 
	printf("user: %s\n",username); 
	//>user <username>
	sprintf(buf, "user %s\r\n", "anonymous");

	if((bytes = write(socket_fd, buf, strlen(buf)))<=0 ){
		return ERR_FTP_WR;
	}

	printf("\nUSERNAME - Bytes written %d\n", bytes);

	if(ftp_read(socket_fd,buf,sizeof(buf)) != 0 ){
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

	if(ftp_read(socket_fd,buf,sizeof(buf)) != 0 ){
		return ERR_FTP_RD; 
	}

	//clear buffer
	memset(buf, 0,strlen(buf)); 

	return 0; 
}

int ftp_pasv(int socket_fd){
	int bytes;
	char buf[BUFFER_SIZE]; 
	char ip[BUFFER_SIZE]; 
	char port[BUFFER_SIZE]; 
	int ret; 

	//pasv
	sprintf(buf, "pasv\r\n"); 

	if((bytes = write(socket_fd,buf, strlen(buf)))<=0 ){
		return ERR_FTP_WR;
	}
	printf("\nPASV - Bytes written %d\n", bytes);

	if(ftp_read(socket_fd,buf,sizeof(buf)) != 0 ){
		return ERR_FTP_RD; 
	}
	//erase first "227 Entering Passive Mode (" 
	chopN(buf,27); 

	printf("buf: %s\n",buf);

	//decompose ip
	char * ip1 = get_string_until_char(buf,',');
	char * ip2 = get_string_until_char(buf,',');
	char * ip3 = get_string_until_char(buf,',');
	char * ip4 = get_string_until_char(buf,',');
	char * ip5 = get_string_until_char(buf,',');
	char * ip6 = get_string_until_char(buf,')');

	//reset buf
	memset(buf,0,strlen(buf));

	//make ip adress string
	sprintf(ip,"%d.%d.%d.%d",atoi(ip1),atoi(ip2),atoi(ip3),atoi(ip4)); 
	printf("ip: %s\n",ip);

	//get port num 
	int int_port = atoi(ip5)*256+atoi(ip6); 
	sprintf(port,"%d",int_port); 
	printf("port: %s\n",port);

	//open the data port 

	if((ret = connect_ftp(ip,int_port,TYPE_B)) < 0){
        print_error(ret); 
    }

	return ret; 
}

int ftp_close(int socket_fd){
	int bytes; 
	char buf[BUFFER_SIZE];

	if (ftp_read(socket_fd, buf, sizeof(buf)) != 0 ) {
		return ERR_FTP_RD;
	}
	//>quit
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