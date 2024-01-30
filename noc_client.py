import socket
import time

def main():
    # Solicitar al usuario ingresar el puerto del servidor
    server_port = int(input("Ingrese el puerto del servidor: "))

    # Crear un socket UDP/IP
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    print(f"Cliente UDP en ejecución")

    icmp_seq = 0
    while True:
        # Incrementar el número de secuencia ICMP
        icmp_seq += 1

        # Construir el mensaje ICMP simulado
        message = f"ICMP_SEQ={icmp_seq}"

        # Enviar el mensaje al servidor
        client_socket.sendto(message.encode("utf-8"), ('localhost', server_port))

        # Recibir la respuesta del servidor
        data, server_address = client_socket.recvfrom(1024)
        response = data.decode("utf-8")

        # Obtener el tiempo actual
        end_time = int(time.time() * 1000)

        print(f"Respuesta del servidor: {response}")

        # Esperar un tiempo antes de enviar el próximo paquete (opcional)
        time.sleep(1)

if __name__ == "__main__":
    main()
