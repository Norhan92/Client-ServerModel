//this is the client class which will be used to create the server object. 
//it contains the client properties as well as multiple methods which represent the different server functionalities

#include "Client-ServerModel.h"

class Client {

public:

	string nodeType;
	int ID;
	SOCKET clientSocket;
	sockaddr_in service;
	int wsaInitializationNum;
	int connectedToServerVal;
	char dataToSend[200];
	int sentDataByteCount;

	//client class constructor
	Client(int id) {

		nodeType = "Client";
		ID = id;


	}

	//method used by client to download the winsock dll
	void initiateWinsockDLL() {

		WSADATA wsaData;
		WORD winSockVersion = MAKEWORD(2, 2);
		wsaInitializationNum = WSAStartup(winSockVersion, &wsaData);

	}

	//method used by the client for socket creation
	void createSokcet() {
		clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	//method used by the client to connect the server to which it will send data
	void connectToServer(PCSTR IP_address, int portNum) {

		service.sin_family = AF_INET;
		InetPton(AF_INET, _T(IP_address), &service.sin_addr.s_addr);
		service.sin_port = htons(portNum);
		connectedToServerVal = connect(clientSocket, (sockaddr*)&service, sizeof(service));

	}

	//method used by the client to measure the forest temperature
	void measureTemperature(int tempLowerLimit, int tempRange) {
		srand(time(0));
		string temp = to_string(tempLowerLimit + (rand() % tempRange));
		strcpy(dataToSend, temp.c_str());
	}

	//method used by the client to send data to the server
	void sendMessage() {
		sentDataByteCount = send(clientSocket, dataToSend, sizeof(dataToSend)/sizeof(dataToSend[0]), 0);

	}

	//method used by the client to close the socket after communication with the server ends
	void closeSocket() {

		WSACleanup();
		closesocket(clientSocket);
	}
};