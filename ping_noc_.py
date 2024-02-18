import socket
import time
import argparse

def main():
    # Configuración del cliente
    host = input("Ingrese la dirección IP del servidor: ")
    port = int(input("Ingrese el puerto del servidor: "))

    # Crear un socket UDP/IP
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    print(f"Cliente UDP Ping conectado al servidor {host}:{port}")

    # Crear un objeto ArgumentParser
    parser = argparse.ArgumentParser(description="Enviar paquetes ICMP a un servidor.")

    # Añadir el argumento para el número de paquetes
    parser.add_argument("--num-paquetes", type=int, default=float('inf'), help="Número de paquetes a enviar.")

    # Parsear los argumentos
    args = parser.parse_args()

    # Número de paquete inicial
    packet_number = 0

    while packet_number < args.num_paquetes:
        # Incrementar el número de paquete
        packet_number += 1

        # Obtener la marca de tiempo antes de enviar el mensaje
        start_time = time.time()

        # Construir el mensaje a enviar al servidor (simula el número de paquete)
        message = str(packet_number)

        # Enviar datos al servidor
        client_socket.sendto(message.encode(), (host, port))

        # Recibir respuesta del servidor
        data, server_address = client_socket.recvfrom(1024)
        print(f"Respuesta del servidor: {data.decode()}")

        # Calcular la diferencia de tiempo después de recibir la respuesta
        end_time = time.time()
        elapsed_time = end_time - start_time

        # Imprimir el tiempo transcurrido
        print(f"Tiempo transcurrido: {elapsed_time} segundos")

        # Esperar un segundo antes de enviar el siguiente paquete (simula el ping)
        time.sleep(1)

    # Cerrar el socket del cliente
    client_socket.close()

if __name__ == "__main__":
    main()
