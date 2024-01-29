import socket

# Solicitar al usuario ingresar el puerto
while True:
    try:
        PORT = int(input("Ingrese el puerto del servidor: "))
        break
    except ValueError:
        print("Por favor, ingrese un número válido para el puerto.")

# Configuración del servidor
HOST = '127.0.0.1'  # Dirección IP del servidor

# Crear un socket UDP
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client_socket:
    while True:
        # Solicitar al usuario ingresar un mensaje para simular un paquete ICMP
        message = input("Ingrese un mensaje ICMP simulado para enviar al servidor (o 'exit' para salir): ")

        # Enviar el mensaje simulado al servidor
        client_socket.sendto(message.encode(), (HOST, PORT))

        # Salir si el usuario ingresa 'exit'
        if message.lower() == 'exit':
            break

        # No se espera una respuesta del servidor para los mensajes ICMP simulados
        print("Mensaje ICMP simulado enviado al servidor.")

print("Cliente cerrado.")
