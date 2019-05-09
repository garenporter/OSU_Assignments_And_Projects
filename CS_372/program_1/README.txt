Initial setup:
1. Open two Putty sessions, one connected to flip1 and the other connected to flip2
2. Navigate to the folder containing the chatserv, chatclient, Makefile, and README on both Putty sessions.
3. Run the following commands:
$ dos2unix chatserve
$ chmod +x chatserve

Compile and run:
1. Run the following commands:
$ make
$ ./chatserve PORTNUM               //replace PORTNUM with a valid port number, such as 40020
$ ./chatclient flip1 PORTNUM        //replace PORTNUM with the same port number used in the above command

Controlling the program:
1. Enter a user handle into the chatclient. The handle must be 10 or less characters.
2. The client will now send its portnumber to the server, and the server will sends its portnumber to the client once it has received the client's port number.
3. The server and client will now take turns sending messages back and forth. The server starts, and the client will follow. The server and client must take turns.
4. To quit, either the server or client must simply input "quit" without quotes.
5. To kill the server, send a SIGINT by typing ctrl+c