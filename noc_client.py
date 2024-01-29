import socket

# Configuración del servidor
HOST = '127.0.0.1'  # Dirección IP del servidor
PORT = int(input("Ingrese el puerto del servidor: "))  # Puerto del servidor

# Crear un socket UDP
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client_socket:
    while True:
        # Solicitar al usuario ingresar un mensaje para enviar al servidor
        message = input("Ingrese un mensaje para el servidor (o 'exit' para salir): ")

        # Enviar el mensaje al servidor
        client_socket.sendto(message.encode(), (HOST, PORT))

        # Salir si el usuario ingresa 'exit'
        if message.lower() == 'exit':
            break

        # Recibir la respuesta del servidor
        response, server_address = client_socket.recvfrom(1024)
        print(f'Respuesta del servidor: {response.decode()}')

print("Cliente cerrado.")
