# Name: Garen Porter
# Program name: ftserver
# Program description: Waits on a control socket and accepts incoming clients. Sends either a directory listing or file over a separate data connection.
# Course name: CS 372 Intro to Computer Networks
# Program can be ran on any flip server
# Last modified: 3/2/2019
# Citations:
#     Help with socket programming in Python: https://pymotw.com/2/socket/tcp.html
#     Help with getting hostname: https://www.saltycrane.com/blog/2011/11/how-get-username-home-directory-and-hostname-python/
#     Help with sleep functions: https://stackoverflow.com/questions/510348/how-can-i-make-a-time-delay-in-python
#     Help with finding whethere or not a file exists: https://stackoverflow.com/questions/82831/how-do-i-check-whether-a-file-exists-without-exceptions
#     Help with file I/O - https://www.programiz.com/python-programming/file-operation

import sys
import socket
import time
import os.path

#Function description: Sets up the data connection and accepts the server's connection
#Preconditions: Client has requested either a file or directory to be sent over a data connection
#Postconditions: Data connection has been setup and both the server and client are connected
#Cites used: https://pymotw.com/2/socket/tcp.html
def connect_data_socket(hostname, data_port):
    print("Setting up data connection with server...")
    #create TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    #bind socket to port
    server_address = (hostname, data_port)       #set address to be server hostname and port#
    sock.bind(server_address)

    #listen for connections (total of 1 connection can be made at a time)
    sock.listen(1)

    #accept incoming server connection and retrieve server's address
    connection, client_address = sock.accept()  

    print("Data connection established with server!")
    #return the connection
    return connection

#Function description: Sets up a TCP socket and connects to the server over the control connection
#Preconditions: User inputted the correct number of command line args
#Postconditions: Control connection has been established between client and server
#Cites used: https://pymotw.com/2/socket/tcp.html
def connect_control_socket(server_host, server_port):
    #create TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server_address = (server_host, server_port)

    #connect to the control socket
    sock.connect(server_address)

    #return the socket
    print("Control connection established with server!")
    return sock

#Function description: Sends the required info needed for the server to connect to the data connection socket
#Preconditions: Client and server successfully setup the control connection
#Postconditions: Server has the info required to connect to the data connection
#Cites used: https://pymotw.com/2/socket/tcp.html
def send_sock_info(connection, data_port, hostname):
    #send the data port number
    connection.sendall(str(data_port))

    #sleep for one second before sending the hostname
    time.sleep(1)

    #send the client's hostname
    connection.sendall(hostname)

    #sleep for one second before continuing 
    time.sleep(1)

#Function description: Handles the scenario where the client wants the server's directory listing
#Preconditions: User inputted the -l command and control connection was successfully established between client and server
#Postconditions: Client received server directory listing
#Cites used: https://pymotw.com/2/socket/tcp.html
def get_directory(connection, hostname, data_port):
    #send the -l commmand to the server
    print("Requesting directory listing from server...")
    connection.sendall("-l")

    #setup the data connection
    data_connection = connect_data_socket(hostname, data_port)

    #receive and print the directory listing
    receive_dir_listing(data_connection)

    #close the data connection
    print("\nClosing data connection with server")
    data_connection.close()

#Function description: Handles the scenario where the client wants the server to send a file
#Preconditions: User inputted the -g command and control connection was successfully established between client and server
#Postconditions: Client received the requested file or a file not found error
#Cites used: https://pymotw.com/2/socket/tcp.html
def get_file(connection, hostname, data_port, filename):
    #Send the -g command to the server
    print("Requesting file from server...")
    connection.sendall("-g")

    #get ready from server
    connection.recv(1024)   

    #send filename to the server
    connection.sendall(filename)

    #check if file exists on server, if not quit and print an error message
    if connection.recv(1024) != "_good_!":
        print("FILE DOES NOT EXIST")
        return
    
    #setup the data connection between the client and server
    data_connection = connect_data_socket(hostname, data_port)

    #Receive the file and print out its contents
    receive_file(data_connection, filename)

    #closet the data connection
    print("\nClosing data connection with server")
    data_connection.close()

#Function description: Receives a file sent by the server, saves it, and prints it to the terminal
#Preconditions: User inputted the -g command and control connection was successfully established between client and server
#Postconditions: File has been received and saved without overwriting any files and printed to the terminal
#Cites used: 
#https://www.programiz.com/python-programming/file-operation
#https://stackoverflow.com/questions/82831/how-do-i-check-whether-a-file-exists-without-exceptions
#https://pymotw.com/2/socket/tcp.html
def receive_file(connection, filename):
    #determines if file already exist so that the file can renamed and avoid overwriting data
    i = 1
    while(os.path.isfile(filename)):                #while the filename already exists in the current directory 
        temp = str(i) + "_" + filename              #append a number to the file
        if not (os.path.isfile(temp)):              #if new filename does not exist, change the filename
            filename = str(i) + "_" + filename
        i = i + 1
    
    #open the file with write access and receive the first chunk of the file
    file = open(filename, 'w')
    buffer = connection.recv(1024)

    #while the done message has not been received, keep writing data to the file
    while buffer != "_done_!":
        file.write(buffer)                  #write the receive data to the file
        buffer = connection.recv(1024)      #receive the next chunk of data
    
    #close the file and sleep for 2 seconds before printing it out
    file.close()
    print("File received! Printing out file contents...\n")
    time.sleep(2)

    #open the file with read access, print the contents, then close the file
    file = open(filename, 'r')
    print(file.read())
    file.close()

#Function description: Receives the directory listing from the ser ver and prints it
#Preconditions: User inputted the -l command and control connection was successfully established between client and server
#Postconditions: The directoy listing has been received and printed to the terminal
#Cites used: https://pymotw.com/2/socket/tcp.html
def receive_dir_listing(connection):
    #receive the first file or directory from the server
    buffer = connection.recv(1024)

    #while the done message has not been received
    while buffer != "_done_!":
        print(buffer)                   #print out the file or directory
        buffer = connection.recv(1024)  #receive the next file or directory

if __name__ == "__main__":
    #check for the correct number of command line arguments
    if len(sys.argv) != 6 and len(sys.argv) != 5:
        print('Wrong number of arguments, must be 5 or 6! Usage: <SERVER_HOST> <SERVER_PORT> <COMMAND> <FILENAME> <DATA_PORT>')
        exit(1)
    
    #assign each command line argument to a variable. Assigned variables depend on number of command line arguments
    server_host = sys.argv[1]
    server_port = int(sys.argv[2])
    command = sys.argv[3]
    if len(sys.argv) == 6:
        filename = sys.argv[4]
        data_port = int(sys.argv[5])
    else:
        data_port = int(sys.argv[4])
    
    #get the hostname of the client 
    hostname = socket.gethostname()

    #connect to the server over the control connection
    connection = connect_control_socket(server_host, server_port)

    #send the client's hostname and data port to the server
    send_sock_info(connection, data_port, hostname)

    #get directory listing if command is -l
    if command == "-l":
        get_directory(connection, hostname, data_port)

    #get desired file if command is -g
    elif command == "-g":
        get_file(connection, hostname, data_port, filename)
    #print an error if command is neither -g or -l
    else:
        print('INVALID COMMAND')
        connection.close()
        exit(1)

    #close control connection
    print("Closing control connection with server")
    connection.close()