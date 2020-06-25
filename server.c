/* 
   A simple server in the internet domain using TCP
   Usage:./server port (E.g. ./server 10000 )
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#define DATA_SIZE 1024*1024*10
#define MAXLINE 409600
//2016003736 이민수 소프트웨어학부 컴퓨터전공 3학년
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd; //descriptors rturn from socket and accept system calls
     int portno; // port number
     socklen_t clilen;

     int GorP = 0;  // GET=1, POST=2
     char *GParray[3];     
     GParray[1] = "GET";	
     GParray[2] = "POST";
     
     /*sockaddr_in: Structure Containing an Internet Address*/
     struct sockaddr_in serv_addr, cli_addr;
     
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     
     /*Create a new socket
       AF_INET: Address Domain is Internet 
       SOCK_STREAM: Socket Type is STREAM Socket */
     sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
     if (sockfd < 0) 
        error("ERROR opening socket");
     
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]); //atoi converts from String to Integer
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //for the server the IP address is always the address that the server is running on
     serv_addr.sin_port = htons(portno); //convert from host to network byte order
     
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) //Bind the socket to the server address
              error("ERROR on binding");
     
     listen(sockfd,5); // Listen for socket connections. Backlog queue (connections to wait) is 5
     
     clilen = sizeof(cli_addr);
     /*accept function: 
       1) Block until a new connection is established
       2) the new socket descriptor will be used for subsequent communication with the newly connected client.
     */
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     
	
	int recv_len = 0;
	unsigned char newbuf[1024];	 // ex) GET /file.txt
	unsigned char newpath[1024]; // ex) /file.txt
	unsigned char newfile[1024]; // ex) file.txt
	int sockaddr_in_size = sizeof(struct sockaddr_in);	

	memset(newpath, 0, 1024);
	memset(newfile, 0, 1024);

	recv_len = recvfrom(newsockfd, newbuf, 1024, 0, (struct sockaddr *) &cli_addr, &sockaddr_in_size); // 받은 파일명과 GET or POST를 newbuf에 저장함 받은 recv_len은 받은 파일의 크기 'GET /filename' 형식으로 받아짐
	newbuf[recv_len - 1] = 0;
	if(newbuf[0] == '\0')
		strcpy(newbuf, NULL);

	printf("%s \n",newbuf);

	for(int i=0;i<strlen(newbuf);i++){ // GET인지 POST인지 판별하고 newbuf에서 GET이나 POST를 떼어내고 파일이름만 newpath에 저장함
		printf("%d\n",i);
		if(newbuf[i] == 'G' && newbuf[i+1] == 'E' && newbuf[i+2] == 'T' && newbuf[i+3] == ' '){ // GET 일때
			for(int j=0;newbuf[i+4+j] != ' ';j++){
				newpath[j] = newbuf[i+4+j];
			}		
			GorP = 1; // GET이면 1을 GorP에 저장 
			break;
		}	
		else if(newbuf[i] == 'P' && newbuf[i+1] == 'A' && newbuf[i+2] == 'T' && newbuf[i+3] == 'H' && newbuf[i+4] == ' '){ // POST 일때 
			for(int j=0;newbuf[i+4+j] != ' ';j++){
				newpath[j] = newbuf[i+4+j];
			}	
			GorP = 2; // POST이면 2를 GorP에 저장 
			break;	

		}
	}
	printf("request: %s \n", newpath);

	for(int i=0 ;i<strlen(newpath)-1;i++){	// newpath에서 앞의 /를 떼어내고 뒷부분을 newfile에 저장
		newfile[i] = newpath[i+1];
	}

	int pos = 0; //확장자와 파일명을 구분짓는 '.'의 위치
	unsigned char fileExtension[1024]; // 파일의 확장자

	for(int i=0;i<strlen(newfile);i++){		//파일의 확장자 부분만 fileExtension에 저장
		if(pos != 0){
			fileExtension[i - pos - 1] = newfile[i];
		}
		if(newfile[i] == '.'){
			pos = i;			
		}	
	}
	
	unsigned char CTfileExtension[1024];	//파일의 확장자에 따른 Content-Type 출력값

	if(strcmp(fileExtension, "html") == 0){ //파일의 확장자가 html이면 
		strcpy(CTfileExtension, "text/html");  //Content-Type 출력값은 text/html 로 설정
	}else if(strcmp(fileExtension, "jpg") == 0 || strcmp(fileExtension, "jpeg") == 0){ // 파일의 확장자가 jpg나 jpeg면 
		strcpy(CTfileExtension, "image/jpeg");		//Content-Type 출력값은 image/jpeg 로 설정
	}else if(strcmp(fileExtension, "pdf") == 0){	//위와 비슷 
		strcpy(CTfileExtension, "application/pdf");	
	}else if(strcmp(fileExtension, "gif") == 0){	//위와 비슷
		strcpy(CTfileExtension, "image/gif");	
	}else if(strcmp(fileExtension, "mp3") == 0){	//위와 비슷 
		strcpy(CTfileExtension, "audio/mpeg");	
	}else{
		strcpy(CTfileExtension, "multipart/form-data");	 //위에 나타낸것들이 아닌 값이 확장자이면 Content-Type 출력값은 multipart/form-data 로 설정
	}

	char *packet;
	char pre_body[1024];
	char *fileBuf = calloc(sizeof(char), DATA_SIZE);
	char headerline[MAXLINE + 1];
	char *bodyline = calloc(sizeof(char), DATA_SIZE);

	FILE *fp = fopen(newfile, "r");		//파일명(newfile)과 같은 파일 오픈
	if(fp == NULL){						//오류 처리
		printf("file cant read\n");
		fclose(fp);
		return -1;	
	}	
	
	fseek(fp, 0, SEEK_END);			//파일 크기를 계산하기 위해 fseek사용 
	int file_size = ftell(fp);		//파일크기
	fseek(fp, 0, SEEK_SET);			//seek_set으로 다시 파일위치 처음으로 
	if(fread(fileBuf, 1, file_size, fp) == -1)	//fread로 데이터를 fileBuf에 저장
		printf("fread error\n");

	sprintf(pre_body, "\r\n-------------\r\nfilename=\"%s\"\r\n-------------\r\n\r\n", newfile);	//파일명 클라이언트(브라우저)에 출력
 
    int pre_len = strlen(pre_body);
    int body_len = pre_len + file_size;
 
    memcpy(bodyline, pre_body, pre_len);	//bodyline에 pre_body 복사
    memcpy(bodyline+pre_len, fileBuf, file_size);	//bodyline+pre_body한 것에 fileBuf 복사
 
 	//헤더 생성
    sprintf(headerline, "%s %s HTTP/1.1\r\n"  // GET or POST 파일명 HTTP/1.1
        "Host: %s:%d\r\nConnection: keep-alive\r\n"  // Host:127.0.0.1:포트넘버 Connection: keep-alive
        "Content-Length: %d\r\n"	//파일 크기 
        "Content-Type: %s\r\n\r\n", GParray[GorP], newpath, "127.0.0.1", portno, file_size, CTfileExtension); // 파일의 타입 출력
    int head_len = strlen(headerline); 	//헤더의 크기 

    //join header + body
    packet=calloc(1, head_len+body_len+1);	//메모리 할당
    int packet_len = head_len+body_len;
    memcpy(packet, headerline, head_len);	//packet에 headerline 복사
    memcpy(packet+head_len, bodyline, body_len); //packet+header한 것에 bodyline 복사

    write(newsockfd, packet, packet_len);
 
    fclose(fp);	//파일을 닫아줌
    close(sockfd);
    close(newsockfd);
     
    return 0; 
}

