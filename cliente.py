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

# Crear un socket TCP
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
    # Conectar al servidor
    client_socket.connect((HOST, PORT))

    while True:
        # Enviar paquete ICMP simulado al servidor
        message = 'Mensaje simulado ICMP'
        client_socket.sendall(message.encode())

        # Recibir la respuesta del servidor
        data = client_socket.recv(1024)
        print(f'Respuesta del servidor: {data.decode()}')
