// Client-ServerModel.cpp : Defines the entry point for the application. 
//This file is considered as a test for the implemented client-server model. 
//It simulates a client node sending data to the server every one second using the TCP protocol.
//The server will be printing out the average temp as well as the accumulated temp every 5 seconds.
//Please note that there will be print messages after every steps confriming successful completion of it.


#include "Client-ServerModel.h"
#include "Server.cpp"
#include "Client.cpp"

void main()
{
	//calling the client and server classes to create an object instance of each

	Server server1 = Server(1);
	Client client1 = Client(1);

	//server is callig the initiateWinsockDLL method to download the  Windows dynamic link library (DLL) so that it can make use of windows sockets
	server1.initiateWinsockDLL();

	//checking if server has downloaded the DLL successfully
	if (server1.wsaInitializationNum != 0) {
		cout << "Server Winsock dll not found" << endl;
		return;
	}

	cout << "Server Winsock dll found "<< endl;

	//server calling the createSockt method to create its windows socket which will be used to communicate with the client
	server1.createSokcet();

	//checking if server socket was created successfully
	if (server1.serverSocket == INVALID_SOCKET) {
		cout << "Error creating server socket " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	cout << "Server socket is created successfully" << endl;

	//client is callig the initiateWinsockDLL method to download the  Windows DLL so that it can make use of windows sockets
	client1.initiateWinsockDLL();

	//checking if the client has downloaded the DLL successfully
	if (client1.wsaInitializationNum != 0) {
		cout << "Client Winsock dll not found" << endl;
		return;
	}

	cout << "Client Winsock dll found " << endl;

	//client calling the createSockt method to create its windows socket which will be used to communicate with the server
	client1.createSokcet();

	//checking if the client socket was created successfully
	if (client1.clientSocket == INVALID_SOCKET) {
		cout << "Error creating client socket " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	cout << "Client socket is ceated successfully" << endl;

	//initializing the IP address and the port number to which the server socket will be bound
	PCSTR IP_address = "127.0.0.1";
	int portNum = 55555;

	//server calls the bindSocket to bind its created socket to the IP address and port number
	server1.bindSocket(IP_address,portNum);

	//checking if the server socket was bound to the IP address and port number successfully
	if (server1.socketBindingVal == SOCKET_ERROR) {
		cout << "Server socket binding failed" << endl;
		server1.closeSocket();
		WSACleanup();
		return;
	}

	cout << "Server socket binding is completed successfully" << endl;

	//initializing the number of clients to which the server will be connected. 
	//In this example, the server will be connected to only one client
	int clientConnectionsNum = 1;

	//server is calling its socketListeningval to start listening out for any incoming client connection requests
	server1.serverListening(clientConnectionsNum);

	//checking if the server's socket listening was successful
	if (server1.socketListeningVal == SOCKET_ERROR) {
		cout << "Error with server socket listening " << WSAGetLastError() << endl;
	}
	else {
		cout << "Server is listening and waiting for client connection" << endl;
	}


	//passing the server's IP address and port number to the connectToServer methodof the client so that
	//it can connect to the server
	client1.connectToServer(server1.IP_address, server1.portNumber);

	//checking if the client connected to the server succssfully
	if (client1.connectedToServerVal == SOCKET_ERROR) {
		cout << "Client failed to connect to server" << endl;
		WSACleanup();
		return;
	}

	cout << "Server-Client connection established successfully" << endl;

	//server calling the acceptClientconnection method to accept the client's connection request
	server1.acceptClientConnection();

	//checking if the server managed to accept the client's connection
	if (server1.acceptDuplicateSocket == INVALID_SOCKET) {
		cout << "Server failed to accept client connection " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	cout << "Server accepted client connection" << endl;

	//initialzing the temperature lower bound to 30 degrees and the temp range to 6 degrees which we will use to generate
	//temperature values between 30 and 36 degrees inclusive
	int tempLL = 30;
	int tempRange = 6;

	//initializing the number of messages that the client will send to the server 
	int counter = 0;
	int numOfMessages = 20;

	//passing seed to the srand function so that the client can generate a different value using the rand function in each iteration
	srand(time(0));

	//while loop for the client to send 20 messages to the server
	while (counter < numOfMessages) {

		//client calling the measureTemperature method to generate a temperature which will be sent to the server
		client1.measureTemperature(tempLL, tempRange);

		//client calling the sendMessages method to send the newly measured temperature to the server
		client1.sendMessage();

		//checking if the client sent the data successfully
		if (client1.sentDataByteCount > 0) {
			cout << "Client managed to send the data to the server" << endl;
		}
		else {
			WSACleanup();
		}

		//server calling the receiveMessage to received the client's message
		server1.receiveMessage();

		//checking if the server received the client's message successfully
		if (server1.receivedDataByteCount > 0) {

			cout << "Server received the messsage from client: " << server1.receivedData << endl;

			server1.calculateAccumulatedTemperature();
			server1.calculateAverageTemperature();

			//we use this if condition so that the server can print out the average temp and the accumulated temp every 5 seconds
			if (counter % 5 == 0) {

				cout << " Average Temperature = " << server1.averageTemp << endl;
				cout << " Accumulated Temperature = " << server1.accumulatedTemp << endl;
			
			}
		}
		else {
			WSACleanup();
		}

		counter++;

		//pausing the program for 1 sec using the sleep function to make sure the client will not send another message to the server
		//unless a second has passed
		Sleep(1000);

	}

	//In the below commented section i was trying using the time function instead of the sleep function to make sure that the client
	// will only send a new message to the server after 1 sec
	// 
	//int startingTime = time(0);
	//counter = 0;

	/*while (counter < 5) {
		if (time(0) - startingTime == 1) {
			startingTime = time(0);

			client1.sendMessage();

			if (client1.sentDataByteCount > 0) {
				cout << "Client managed to send the data to the server" << endl;
			}
			else {
				WSACleanup();
			}

			server1.receiveMessage();

			if (server1.receivedDataByteCount > 0) {
				cout << "Server received the messsage from client: " << server1.receivedData << endl;;
			}
			else {
				WSACleanup();
			}

			counter++;

		}
	}*/

	//each of the client and server calling its closeSocket method to close the socket after the sending and reception of messages is finished
	server1.closeSocket();
	client1.closeSocket();

	return;
}
