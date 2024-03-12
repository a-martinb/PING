import socket

def main():
    # Configuración del servidor
    host = "0.0.0.0"
    port = int(input("Ingrese el puerto del servidor: "))

    # Crear un socket UDP/IP
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Enlazar el socket al host y al puerto
    server_socket.bind((host, port))

    print(f"Servidor UDP Ping en ejecución en {host}:{port}")

    while True:
        # Recibir datos del cliente
        data, client_address = server_socket.recvfrom(1024)

        # Obtener el tamaño del paquete
        packet_size = len(data)

        # Obtener la dirección IP del cliente
        client_ip = client_address[0]

        # Enviar respuesta al cliente con el tamaño del paquete, el número de paquete y la dirección IP
        response = f"Tamaño del paquete: {packet_size} bytes, Número de paquete: {data.decode()}, Dirección IP del cliente: {client_ip}"
        server_socket.sendto(response.encode(), client_address)

if __name__ == "__main__":
    main()
