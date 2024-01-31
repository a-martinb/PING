import socket
import time
import signal
import sys

global num_sent, num_received, total_time, min_time, max_time

# Contadores para las estadísticas
num_sent = 0
num_received = 0

# Tiempos para el cálculo del tiempo medio
total_time = 0.0
min_time = float('inf')
max_time = 0.0


def signal_handler(sig, frame):
    print(f"\n{SERVER_IP} ping statistics ---")
    print(f"{num_sent} packets transmitted, {num_received} packets received, {(1 - (num_received / num_sent)) * 100}% packet loss")
    if num_received > 0:
        avg_time = total_time / num_received
        print(f"round-trip min/avg/max/mdev = {min_time:.3f}/{avg_time:.3f}/{max_time:.3f} ms")
    else:
        print("round-trip min/avg/max/mdev = N/A")
    sys.exit(0)

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
        start_time = time.time()
        client_socket.sendto(message.encode("utf-8"), ('localhost', server_port))
        num_received +=1
        # Recibir la respuesta del servidor
        data, server_address = client_socket.recvfrom(1024)
        end_time = time.time()
        response = data.decode("utf-8")
        # Estadísticas
            num_received += 1
            rtt = (end_time - start_time) * 1000
            total_time += rtt
            if rtt < min_time:
                min_time = rtt
            if rtt > max_time:
                max_time = rtt
        # Obtener el tiempo actual
        end_time = int(time.time() * 1000)

        print(f"Respuesta del servidor: {response}")

        # Esperar un tiempo antes de enviar el próximo paquete (opcional)
        time.sleep(1)
         except KeyboardInterrupt:
        signal_handler(signal.SIGINT, None)

if __name__ == "__main__":
    main()
