import socket
import time
import signal
import sys



# Contadores para las estadísticas
num_sent = 0
num_received = 0


def main():
    global num_sent, num_received, total_time;

    # Solicitar al usuario ingresar el puerto del servidor
    server_port = int(input("Ingrese el puerto del servidor: "))

    # Crear un socket UDP/IP
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    print(f"Cliente UDP en ejecución")
    icmp_seq = 0
    while True:
        # Incrementar el número de secuencia ICMP
        icmp_seq += 1

        # Construir el mensaje 
        message = f"ICMP_SEQ={icmp_seq}"

        # Enviar el mensaje al servidor
        start_time = time.time()
        client_socket.sendto(message.encode("utf-8"), ('localhost', server_port))
        num_received +=1
        # Recibir la respuesta del servidor
        data, server_address = client_socket.recvfrom(1024)
    
        response = data.decode("utf-8")
        #Estadisticas

        print(f"Respuesta del servidor: {response}")

        # Esperar un tiempo antes de enviar el próximo paquete 
        time.sleep(1)

if __name__ == "__main__":
    main()
