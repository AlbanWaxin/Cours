#include "ntpclient-udp.h"


void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}


int main(int argc, char* argv[]){
    ntp_packet packet = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    SET_LI(packet, 0);
    SET_VN(packet, 3);
    SET_MODE(packet, 3);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd <0)
    {
        error("Error socket()");
    }
    char *host_name = "fr.pool.ntp.org";
    struct hostent *server;
    server= gethostbyname(host_name);
    if (server == NULL)
    {
        error("Error no such host");
    }
    struct sockaddr_in serv_addr ;
    bzero(&serv_addr,sizeof(struct sockaddr_in));
    serv_addr.sin_family=AF_INET;
    bcopy(server->h_addr,&serv_addr.sin_addr.s_addr,server->h_length);
    int portno = 123;
    serv_addr.sin_port=htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))){
        error("Error connect");
    }
    //char buffer[BUFSIZ+1];
    //register int bytes;
    int n;
    n= read(sockfd, &packet,sizeof(ntp_packet));
    if (n<0){
        error("ERROR reading from socket");
    }
    printf("Timestamp: %u\n", ntohl(packet.txTm_s));
    //while ((bytes = read(sockfd, buffer, BUFSIZ)) > 0){
        //write(1, buffer, bytes);
        
    //}
    printf("Timestamp: %llu\n", (ntohl(packet.txTm_s)-NTP_TIMESTAMP_DELTA));
    time_t txTm = (time_t)(ntohl(packet.txTm_s) - NTP_TIMESTAMP_DELTA ); 
    printf("Time: %s",ctime((const time_t*)&txTm));
    return(EXIT_SUCCESS);
}