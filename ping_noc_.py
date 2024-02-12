import socket
import time

def main():
    # Configuración del cliente
    ip = input("Ingrese la dirección IP del servidor: ")
    port = int(input("Ingrese el puerto del servidor: "))


    # Crear un socket UDP/IP
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    print(f"Cliente UDP Ping conectado al servidor {host}:{port}")

    # Número de paquete inicial
    packet_number = 0

    while True:
        # Incrementar el número de paquete
        packet_number += 1

        # Construir el mensaje a enviar al servidor (simula el número de paquete)
        message = str(packet_number)

        # Enviar datos al servidor
        client_socket.sendto(message.encode(), (host, port))

        # Recibir respuesta del servidor
        data, server_address = client_socket.recvfrom(1024)
        print(f"Respuesta del servidor: {data.decode()}")

        # Esperar un segundo antes de enviar el siguiente paquete (simula el ping)
        time.sleep(1)

if __name__ == "__main__":
    main()
