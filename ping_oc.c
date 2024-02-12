#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

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

    // Crear el socket TCP
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error al crear el socket del cliente");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Conectar al servidor
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al conectar con el servidor");
        exit(EXIT_FAILURE);
    }

    printf("Conectado al servidor\n");

    // Enviar y recibir paquetes ICMP al servidor
    int icmp_seq = 0;
    while (1) {
        // Incrementar el número de secuencia ICMP
        icmp_seq++;

        // Construir el mensaje ICMP simulado
        snprintf(message, MAX_BUF_SIZE, "Paquete ICMP_SEQ=%d", icmp_seq);

        // Enviar el mensaje al servidor
        if (send(client_socket, message, strlen(message), 0) < 0) {
            perror("Error al enviar el mensaje al servidor");
            exit(EXIT_FAILURE);
        }

        // Esperar la respuesta del servidor
        memset(message, 0, sizeof(message));
        if (recv(client_socket, message, MAX_BUF_SIZE, 0) <= 0)
        {
        perror("Error al recibir datos del servidor");
        exit(EXIT_FAILURE);
        }   


        // Imprimir la respuesta del servidor
        printf("Respuesta del servidor: %s\n", message);

        // Esperar un tiempo antes de enviar el próximo paquete (opcional)
        sleep(1);
    }

    // Cerrar el socket del cliente
    close(client_socket);

    return 0;
}



