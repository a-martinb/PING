#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>

#define PORT 10000
#define BUFFER_SIZE 1024
#define ICMP_HEADER_SIZE 8

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <puerto>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd, recv_len;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Crear socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        handle_error("Error al crear el socket");
    }

    // Configurar dirección del servidor
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // Enlazar el socket a la dirección y puerto
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        handle_error("Error al enlazar el socket");
    }

    printf("Servidor ping NOC en ejecución en el puerto %s...\n", argv[1]);

    while (1) {
        // Recibir paquete ICMP del cliente
        if ((recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len)) == -1) {
            handle_error("Error al recibir el paquete");
        }

        // Verificar tamaño mínimo del paquete ICMP
       	
        }

        // Procesar el paquete ICMP
        struct icmphdr *icmp_hdr = (struct icmphdr *)buffer;
        if (icmp_hdr->type == ICMP_ECHO) {
            printf("Paquete ICMP (Echo Request) recibido desde %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            // Preparar respuesta (Echo Reply)
            icmp_hdr->type = ICMP_ECHOREPLY;
            // No necesitamos calcular el checksum en este caso

            // Enviar respuesta al cliente
            if (sendto(sockfd, buffer, recv_len, 0, (struct sockaddr *)&client_addr, addr_len) == -1) {
                handle_error("Error al enviar la respuesta");
            }

            printf("Respuesta ICMP (Echo Reply) enviada al cliente.\n");
        } else {
            printf("Paquete ICMP no reconocido\n");
        }
    }

    // Cerrar socket
    close(sockfd);

    return 0;
}
