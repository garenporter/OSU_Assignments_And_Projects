Initial setup:
1. Open two Putty sessions, one connected to flip1 and the other connected to flip2
2. Navigate to the folder containing the ftserver, ftclient, Makefile, sample files, and README on both Putty sessions.

Compile and run:
1. Run the following commands on flip2:
$ make
$ ./ftserver PORTNUM               //replace PORTNUM with a valid port number, such as 40051

2. Run the following commands on flip1:
- To get server directory listing:
$ python ./ftclient.py flip2.engr.oregonstate.edu PORTNUM -l DATA_PORT        //replace PORTNUM with the same port number used in the above command and DATA_PORT with a differen valid port number
- To get a file:
$ python ./ftclient.py flip2.engr.oregonstate.edu PORTNUM -g FILENAME DATA_PORT //PORTNUM and DATA_PORT are the same as above, and filename is a valid file that lives in server's directory

Controlling the program:
1. The ftserver program does not need to be touched once it is ran as it will accept connections indefinitely.
2. To end the ftserver program, send a SIGINT to flip2 by pressing Ctrl+c on your keyboard.
3. Once the ftclient program is ran it will run by itself and terminate itself at the appropriate time.

Things to note:
1. There are 3 sample text files in the .zip folder, one small, one big, and one huge. The huge file is substantially bigger than the other two files.