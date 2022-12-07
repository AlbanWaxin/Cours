#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include"string.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netdb.h>
#include "sys/types.h"

#define SET_LI(packet,li) (uint8_t)(packet.li_vn_mode |= (li << 6))
#define SET_VN(packet,vn) (uint8_t)(packet.li_vn_mode |= (vn << 3))
#define SET_MODE(packet,mode) (uint8_t)(packet.li_vn_mode |= (mode << 0))
#define SIZEMSG 20
//Les macros fonctionnent comme les fonctions normales à l'exception que cela remplace directement le code à la compilation
void error(char * msg){
    perror(msg);
    _exit(EXIT_FAILURE);
}

typedef struct ntp_packet
{
    u_int8_t li_vn_mode;   
    u_int8_t stratum;
    u_int8_t poll;
    u_int8_t precision;
    u_int32_t rootDelay;
    u_int32_t rootDispersion;
    u_int32_t refId;
    u_int32_t refTm_s;
    u_int32_t refTm_f;
    u_int32_t orig_Tm_s;
    u_int32_t orig_Tm_f;
    u_int32_t rxTm_s;
    u_int32_t rxTm_f;
    u_int32_t txTm_s;
    u_int32_t txTm_f;
}ntp_packet;

int main(int argc, char const *argv[]){
    ntp_packet packet;
    bzero(&packet, sizeof(ntp_packet));
    SET_LI(packet,0);
    SET_MODE(packet,3);
    SET_VN(packet,3);
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        error("Error Socket : ");
    }
    return 0;
    char * hostname = "fr.pool.ntp.org";
    struct hostent* server;
    if (!(server = gethostbyname(hostname))){
        error("Error Hostname:");
    }
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr,&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(123);
    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1){
        error("Error Connection : ");
    }
    if (write(sockfd,&packet,sizeof(ntp_packet)) == -1)
    {
        error("Erreur write");
    }
    return 0;
}

