import sys
from socket import *


def chat(newConnection, clientName, userName):
    message = ""            #Hold the message
    while 1:                #Run until we no longer want to chat
        receive = newConnection.recv(501)[0:-1]        #Receive message
        if receive == "":                  #If nothing is received. Wait for new connection
            print "End of connection"
            print "Waiting..."
            break
        
        print "{}> {}".format(clientName, receive)     #Puts the prompt in the propert format  
        sending = ""
        while len(sending) > 500 or len(sending) == 0:
            sending = raw_input("{}> ".format(userName))
            
        if sending == "\quit":              #Per assignment specs, must be able to quit when you type in \quit
            print "End of connection"
            print "Waiting..."
            break
        newConnection.send(sending)

def infoSave(connection, userName):
    clientName = connection.recv(1024)    
    connection.send(userName)
    return clientName

if __name__ == "__main__":    
    if len(sys.argv) != 2:              #First check if the user put in the right number of arguments. If not, print the usage statement
        print "Usage: python chatServer.py [port]"
        exit(1)
   
    portNumber = sys.argv[1]
    newSocket = socket(AF_INET, SOCK_STREAM)         #Taken from here https://docs.python.org/2/howto/sockets.html
    
    newSocket.bind(('128.193.54.182', int(portNumber)))           #Also from this link https://docs.python.org/2/howto/sockets.html
   
    newSocket.listen(1)         #Start listening
    
    userName = ""
    while len(userName) > 10 or len(userName) == 0:     #Get the user name, estabish connection, call chat function and finally close when we're ready
        userName = raw_input("Enter a username that is 10 characters or less. ")
        print "Server is  ready for messages."
    while 1:
        connection, address = newSocket.accept()                         
        print "Connected on address {}".format(address)
        
        chat(connection, infoSave(connection, userName), userName)
        
        connection.close()