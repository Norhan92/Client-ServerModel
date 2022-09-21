//this is the server class which will be used to create the server object. 
//it contains the server properties as well as multiple methods which represent the different server functionalities

#include "Client-ServerModel.h"

class Server {

public:

	string nodeType;
	int ID;
	PCSTR IP_address;
	int portNumber;
	SOCKET serverSocket;
	sockaddr_in service;
	int socketBindingVal;
	int socketListeningVal;
	SOCKET acceptDuplicateSocket;
	int wsaInitializationNum;
	char receivedData[200];
	int receivedDataByteCount;
	int averageTemp=0;
	int accumulatedTemp=0;
	int tempCount=0;

	//server class constructor
	Server(int id) {

		nodeType = "Server";
		ID = id;

	}

	//method used by server to download the winscok dll
    void initiateWinsockDLL() {

		WSADATA wsaData;
		WORD winSockVersion = MAKEWORD(2, 2);
		wsaInitializationNum=WSAStartup(winSockVersion, &wsaData);

	}

	//method used by srever to create its socket
	void createSokcet() {
		serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	//method used by server to bind its socket to the its IP address and port number which will be useed by the client to connect to it
	void bindSocket(PCSTR IP_add, int portNum) {

		IP_address = IP_add;
		portNumber = portNum;
		service.sin_family = AF_INET;
		service.sin_addr.s_addr = INADDR_ANY;
		InetPton(AF_INET, _T(IP_address), &service.sin_addr.s_addr);
		service.sin_port = htons(portNum);
		socketBindingVal= bind(serverSocket, (sockaddr*)&service, sizeof(service));

	}

	//method used by server to listen out to any incoming clients' connection requests
	void serverListening(int clinetConnectionsNum) {

		socketListeningVal=listen(serverSocket, clinetConnectionsNum);
	}

	//method used by server to accept the client connection
	void acceptClientConnection() {

		acceptDuplicateSocket = accept(serverSocket, NULL, NULL);

	}

	//method used by server to receive the client's sent data
	void receiveMessage() {

		receivedDataByteCount = recv(acceptDuplicateSocket, receivedData, sizeof(receivedData)/sizeof(receivedData[0]), 0);

	}

	//method used by server to update the average temperature each time the client send a successful message
	void calculateAverageTemperature() {
		averageTemp = accumulatedTemp / (++tempCount);
	}

	//method used by server to update the accumulated temperature each time the client send a successful message
	void calculateAccumulatedTemperature() {
		accumulatedTemp += atoi(receivedData);
	}

	//method used by server to close the created socket after communication with client ends
	void closeSocket() {

		WSACleanup();
		closesocket(serverSocket);
	}
};