import socket
import time
import argparse

def main():


    # Solicitar al usuario ingresar la dirección IP del servidor y el puerto
    server_ip = input("Ingrese la dirección IP del servidor: ")
    server_port = int(input("Ingrese el puerto del servidor: "))

    # Crear un socket TCP/IP
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Conectar el socket al servidor
    client_socket.connect((server_ip, server_port))

    print(f"Conectado al servidor {server_ip}:{server_port}")

    # Crear un objeto ArgumentParser
    parser = argparse.ArgumentParser(description="Enviar paquetes ICMP a un servidor.")

    # Añadir el argumento para el número de paquetes
    parser.add_argument("--num-paquetes", type=int, default=float('inf'), help="Número de paquetes a enviar.")

    # Parsear los argumentos
    args = parser.parse_args()

    # Inicializar el número de secuencia ICMP
    seq = 0

while seq < args.num_paquetes:
    # Incrementar el número de secuencia ICMP
    seq += 1

    # Obtener la marca de tiempo antes de enviar el mensaje
    start_time = time.time()

    # Construir el mensaje 
    message = f"{seq}"

    # Enviar el mensaje al servidor
    client_socket.sendall(message.encode("utf-8"))

    # Esperar la respuesta del servidor
    response = client_socket.recv(1024).decode("utf-8")

    # Calcular la diferencia de tiempo después de recibir la respuesta
    end_time = time.time()
    elapsed_time = end_time - start_time

    # Imprimir la respuesta del servidor y el tiempo transcurrido
    print(f"Respuesta del servidor: {response}, Tiempo transcurrido: {elapsed_time} segundos")

    # Esperar un tiempo antes de enviar el próximo paquete (opcional)
    time.sleep(1)

# Cerrar el socket del cliente
client_socket.close()
