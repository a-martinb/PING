import socket

# Configuración del servidor
HOST = '127.0.0.1'  # Dirección IP del servidor

# Solicitar al usuario ingresar el puerto
while True:
    try:
        PORT = int(input("Ingrese el puerto del servidor: "))
        break
    except ValueError:
        print("Por favor, ingrese un número válido para el puerto.")

# Crear un socket UDP
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server_socket:
    # Enlazar el socket a la dirección y puerto
    server_socket.bind((HOST, PORT))
    print(f'Servidor UDP en ejecución en {HOST}:{PORT}')

    while True:
        # Recibir datos del cliente
        data, client_address = server_socket.recvfrom(1024)
        print(f'Datos recibidos del cliente {client_address}: {data.decode()}')

        # Responder al cliente
        response = 'Mensaje recibido por el servidor'
        server_socket.sendto(response.encode(), client_address)
