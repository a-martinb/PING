import socket

# Solicitar al usuario ingresar el puerto
while True:
    try:
        PORT = int(input("Ingrese el puerto de escucha del servidor: "))
        break
    except ValueError:
        print("Por favor, ingrese un número válido para el puerto.")

# Configuración del servidor
HOST = '127.0.0.1'  # Dirección IP del servidor

# Crear un socket TCP
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    # Enlazar el socket a la dirección y puerto
    server_socket.bind((HOST, PORT))
    print(f'Servidor TCP en ejecución en {HOST}:{PORT}')

    # Escuchar por conexiones entrantes
    server_socket.listen()

    # Aceptar la conexión entrante
    conn, addr = server_socket.accept()
    print(f'Cliente conectado desde {addr}')

    while True:
        # Recibir datos del cliente
        data = conn.recv(1024)
        if not data:
            break

        # Procesar los datos recibidos como se desee

        # Responder al cliente
        response = 'Paquete ICMP recibido por el servidor'
        conn.sendall(response.encode())

    # Cerrar la conexión
    conn.close()
