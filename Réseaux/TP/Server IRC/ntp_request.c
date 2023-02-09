#include "./headers/ntprequest.h"


void error(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}


int make_ntp_request(){
    ntp_packet packet = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    SET_LI(packet, 0);
    SET_VN(packet, 3);
    SET_MODE(packet, 3);
    int ntpfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (ntpfd <0)
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
    struct sockaddr_in serv_addr;
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    bcopy(server->h_addr,&serv_addr.sin_addr.s_addr,server->h_length);
    int portno = 123;
    serv_addr.sin_port=htons(portno);
    if (connect(ntpfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0){
        error("Error connect");
    }
    printf("connected\n");
    //char buffer[BUFSIZ+1];
    //register int bytes;
    int n;
    n= write(ntpfd, &packet,sizeof(ntp_packet));
    if (n<0){
        error("ERROR writing to socket");
    }
    printf("packet send\n");
    n = read(ntpfd, &packet, sizeof(ntp_packet));
    if (n<0){
        error("ERROR reading from socket");
    }
    printf("read\n");
    time_t txTm = (time_t)(ntohl(packet.txTm_s) - NTP_TIMESTAMP_DELTA ); 
    printf("[%s]\n",ctime((const time_t*)&txTm));
    return(EXIT_SUCCESS);
}
