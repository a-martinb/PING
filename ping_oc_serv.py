import socket
import time

def main():
    # Solicitar al usuario ingresar la dirección IP del servidor y el puerto
    server_ip = "127.0.0.1"
    server_port = int(input("Ingrese el puerto del servidor: "))

    # Crear un socket TCP/IP
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Enlazar el socket al puerto
    server_socket.bind((server_ip, server_port))

    # Escuchar conexiones entrantes
    server_socket.listen(1)

    print(f"Servidor TCP en ejecución en {server_ip}:{server_port}")

    while True:
        # Esperar por una conexión
        print("Esperando conexión...")
        connection, client_address = server_socket.accept()

        try:
            print(f"Conexión establecida desde {client_address}")

            while True:
                # Recibir datos del cliente
                data = connection.recv(1024)
                if data:
                    # Obtener información del cliente
                    client_ip = client_address[0]

                    # Decodificar los datos recibidos
                    seq = data.decode("utf-8")

                    # Construir la respuesta
                    response = f"Tamaño del paquete recibido: {len(seq)}, Direccion IP del cliente: {client_ip},SEQ={seq},"

                    # Enviar la respuesta al cliente
                    connection.sendall(response.encode("utf-8"))
                else:
                    break
        finally:
            # Cerrar la conexión
            connection.close()

if __name__ == "__main__":
    main()
