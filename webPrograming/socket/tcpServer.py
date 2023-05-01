from socket import *
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print('The server is ready to receive')
first = True
while True:
    if first :
        connectionSocket, addr = serverSocket.accept()
        first = False
    messageReceived = connectionSocket.recv(1024).decode()
    if messageReceived == '' :
        connectionSocket.close()
        first = True
        continue
    print('상대 :', messageReceived, addr)
    replyMessage = input('나 : ')
    if replyMessage == 'bye' :
        connectionSocket.close()
        first = True
        continue
    connectionSocket.send(replyMessage.encode())
    