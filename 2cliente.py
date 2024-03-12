import socket
import sys
import select
import time
def error(argumento): #Definimos la funcion que emite el mensaje en caso de error
 print(argumento)
 exit(1)
if (len(sys.argv) != 3):#Comprobamos los argumentos pasados por linea de comandos, deben ser 3: el programa, la direccion ip del servidor y el puerto de escucha
 error("Número de argumentos invalido")
sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #Creamos el socket
#Conectamos al servidor
print("Conectaremos a ", sys.argv[1], ", ", int(sys.argv[2]))
sockfd.connect((sys.argv[1], int(sys.argv[2]))) #Conectamos con el servidor
sockfd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)#Opciones del
socket para reutilizar la direccion local del socket
entradas = [sys.stdin, sockfd]#Creamos la lista de sockets para leer del select
nombre = input("Nombre de usuario: ") #Introducimos nombre de usuario
print("Si quiere enviar un fichero escriba primero: \'fichero\' y presione Enter")
while True:
 try:
 readable,writable,error_s= select.select(entradas, [],[], 0) #Utilizamos select para que no se bloquee el programa al pedir datos de entrada del socket o del teclado
 except KeyboardInterrupt: #Si cerramos el programa cerramos los sockets
 sockfd.close()
 error("Desconectando del servidor")
 for s in readable:
 if s == sockfd: #Si el socket es el del servidor
 data = s.recv(1024) #Recibimos datos
 if data:
 #Si recibimos un fichero lo guardamos
 if data.decode('ascii') == 'fichero\n':#palabra clave para indicar que
recibimos un fichero
 f = open("recibido.txt","wb") #Abrimos el fichero donde lo vamos a guardar
 lectura = s.recv(1024) #recibimos los datos del fichero
 comprobacion = lectura #como luego voy a decodificar comprobacion para ver si llega 'fin', pero si no, si sigue siendo parte del fichero no me interesa decodificarlo pues por eso
 while comprobacion.decode('ascii') != 'fin':
 f.write(lectura) #Escribimos el contenido del fichero recibido en otro fichero
 lectura = s.recv(1024)
 comprobacion = lectura
 print("Fichero guardado")
 else:#Si no recibimos fichero
 print(data.decode('ascii')) #Imprimimos un mensaje normal
 else:
 error("Desconectando")#si no me llegan datos es que se ha desconectado
 else:
 mensaje = sys.stdin.readline() #Escribimos un mensaje por teclado
 if mensaje == 'fichero\n': #Si escribimos fichero nos preparamos para mandar un fichero
 sockfd.send(mensaje.encode('ascii')) #Mandamos la palabra clave fichero
 fichero = input('Nombre del fichero: ') #Nombre del fichero
 f = open(fichero,'rb') #Abrimos el fichero
 content = f.read(1024) #Leemos los datos del fichero
 while content:
 sockfd.send(content) #Mandamos el contenido del fichero
 #El contenido del fichero no hay que codificarlo pues lo que leemos del fichero ya son bytes que es lo que mandamos por el socket
 content = f.read(1024) #Leemos del fichero
 time.sleep(1) #Es para que no se junte el ultimo mensaje con contenido del fichero con la palabra clave de fin de fichero
 content = 'fin' #Palabra clave de fin de fichero
 sockfd.send(content.encode('ascii')) #Mandamos la palabra clave
 else: #si no queremos enviar el fichero
 mensaje = nombre + ' > '+ mensaje.rstrip('\n') #Añadimos al mensaje el nombre de usuario para que indique quien envio el mensaje
 sockfd.send(mensaje.encode('ascii')) #Mandamos el mensaje
