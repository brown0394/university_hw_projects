from socket import *

serverName = "127.0.0.1"
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_DGRAM)
while True:
    message = input("나 : ")
    if message == 'exit':
        break
    clientSocket.sendto(message.encode(), (serverName, serverPort))
    replyMessage, serverAddress = clientSocket.recvfrom(2048)
    print("상대 :", replyMessage.decode())
clientSocket.close()