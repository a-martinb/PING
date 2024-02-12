#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 12345 // Puerto superior a 1023
#define BACKLOG 5
#define BUFFER_SIZE 1024

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main() {
    int sockfd, client_sockfd, recv_len;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Crear socket TCP
    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        handle_error("Error al crear el socket");
        
    }

    // Configurar dirección del servidor
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    // Enlazar el socket a la dirección y puerto
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        handle_error("Error al enlazar el socket");
    }

    // Escuchar por conexiones entrantes
    if (listen(sockfd, BACKLOG) == -1) {
        handle_error("Error al escuchar por conexiones entrantes");
    }

    printf("Servidor TCP en ejecución en el puerto %d...\n", PORT);

    // Aceptar conexiones entrantes
    if ((client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len)) == -1) {
        handle_error("Error al aceptar la conexión entrante");
    }

    printf("Cliente conectado desde %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Enviar datos al cliente
    char *data = "Bienvenido al servidor TCP";
    if (send(client_sockfd, data, strlen(data), 0) == -1) {
        handle_error("Error al enviar datos al cliente");
    }

    printf("Datos enviados al cliente\n");

    // Cerrar sockets
    close(client_sockfd);
    close(sockfd);

    return 0;
}

