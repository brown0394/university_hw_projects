from socket import *
serverName = 'localhost'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)

clientSocket.connect((serverName, serverPort))
while True:
    
    messageToSent = input('나 : ')
    if messageToSent == 'exit' :
        break
    clientSocket.send(messageToSent.encode())
    replyMessage = clientSocket.recv(1024).decode()
    if replyMessage == '' :
        print ("server disconnected")
        break
    print('상대 :', replyMessage)
clientSocket.close()