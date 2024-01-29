#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>

#define BUFFER_SIZE 1024

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <hostname/IP> <puerto>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd, recv_len;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        handle_error("Error al crear el socket");
    }

    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "Error: No se pudo resolver el nombre del host\n");
        exit(EXIT_FAILURE);
    }
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    
    struct icmphdr icmp_hdr;
    icmp_hdr.type = ICMP_ECHO; 
    icmp_hdr.code = 0;
    icmp_hdr.checksum = 0;
    icmp_hdr.un.echo.id = getpid();
    icmp_hdr.un.echo.sequence = 0;

    
    if (sendto(sockfd, &icmp_hdr, sizeof(icmp_hdr), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        handle_error("Error al enviar el paquete ICMP");
    }

    printf("Paquete ICMP (Echo Request) enviado al servidor.\n");
    // Cerrar socket
    close(sockfd);

    return 0;
}