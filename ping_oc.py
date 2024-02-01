import socket
import time

def main():
    # Solicitar al usuario ingresar la dirección IP del servidor y el puerto
    server_ip = input("Ingrese la dirección IP del servidor: ")
    server_port = int(input("Ingrese el puerto del servidor: "))

    # Crear un socket TCP/IP
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Conectar el socket al servidor
    client_socket.connect((server_ip, server_port))

    print(f"Conectado al servidor {server_ip}:{server_port}")

    icmp_seq = 0
    while True:
        # Incrementar el número de secuencia ICMP
        icmp_seq += 1

        # Construir el mensaje ICMP simulado
        message = f"ICMP_SEQ={icmp_seq}"

        # Enviar el mensaje al servidor
        client_socket.sendall(message.encode("utf-8"))

        # Esperar la respuesta del servidor
        response = client_socket.recv(1024).decode("utf-8")

        # Obtener el tiempo actual
        end_time = int(time.time() * 1000)

        print(f"Respuesta del servidor: {response}")

        # Esperar un tiempo antes de enviar el próximo paquete (opcional)
        time.sleep(1)

    # Cerrar el socket del cliente
    client_socket.close()

if __name__ == "__main__":
    main()

