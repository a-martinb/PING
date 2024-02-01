import socket
import time

def main():
    # Solicitar al usuario ingresar el puerto del servidor
    server_port = int(input("Ingrese el puerto del servidor: "))

    # Crear un socket UDP/IP
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Enlazar el socket al puerto
    server_socket.bind(('localhost', server_port))

    print(f"Servidor UDP en ejecución en el puerto {server_port}")

    while True:
        # Recibir datos del cliente
        data, client_address = server_socket.recvfrom(1024)

        # Obtener el tiempo actual
        start_time = int(time.time() * 1000)

        # Obtener información del cliente
        client_ip = client_address[0]

        # Decodificar los datos recibidos
        icmp_seq = data.decode("utf-8")

        # Construir la respuesta
        response = f"Tamaño del paquete recibido: {len(icmp_seq)}, Direccion IP del cliente: {client_ip}, ICMP_SEQ={icmp_seq}, TIME={start_time} ms"

        # Enviar la respuesta al cliente
        server_socket.sendto(response.encode("utf-8"), client_address)

if __name__ == "__main__":
    main()
