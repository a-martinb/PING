#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUF_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[MAX_BUF_SIZE];
    int port;
    char ip[16];

    // Solicitar al usuario ingresar la dirección IP del servidor
    printf("Ingrese la dirección IP del servidor: ");
    scanf("%s", ip);

    // Solicitar al usuario ingresar el puerto del servidor
    printf("Ingrese el puerto del servidor: ");
    scanf("%d", &port);

    // Crear el socket UDP
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

     int icmp_seq = 0;
    while (1) {
        // Incrementar el número de secuencia ICMP
        
        icmp_seq++;

        // Construir el mensaje ICMP simulado
        snprintf(message, MAX_BUF_SIZE, "Paquete ICMP_SEQ=%d", icmp_seq);

        // Enviar el mensaje al servidor
        if (sendto(client_socket, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            perror("Error al enviar el mensaje al servidor");
            exit(EXIT_FAILURE);
        }

        // Esperar la respuesta del servidor
        memset(message, 0, sizeof(message));
        recvfrom(client_socket, message, MAX_BUF_SIZE, 0, NULL, NULL);

        // Imprimir la respuesta del servidor
        printf("Respuesta del servidor: %s\n", message);

        // Esperar un tiempo antes de enviar el próximo paquete (opcional)
        sleep(1);
        
    }

    close(client_socket);
    return 0;
}
