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

	Server(int id) {

		nodeType = "Server";
		ID = id;

	}

    void initiateWinsockDLL() {

		WSADATA wsaData;
		WORD winSockVersion = MAKEWORD(2, 2);
		wsaInitializationNum=WSAStartup(winSockVersion, &wsaData);

	}

	void createSokcet() {
		serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	void bindSocket(PCSTR IP_add, int portNum) {

		IP_address = IP_add;
		portNumber = portNum;
		service.sin_family = AF_INET;
		service.sin_addr.s_addr = INADDR_ANY;
		InetPton(AF_INET, _T(IP_address), &service.sin_addr.s_addr);
		service.sin_port = htons(portNum);
		socketBindingVal= bind(serverSocket, (sockaddr*)&service, sizeof(service));

	}

	void serverListening(int clinetConnectionsNum) {

		socketListeningVal=listen(serverSocket, clinetConnectionsNum);
	}

	void acceptClientConnection() {

		acceptDuplicateSocket = accept(serverSocket, NULL, NULL);

	}

	void receiveMessage() {

		receivedDataByteCount = recv(acceptDuplicateSocket, receivedData, sizeof(receivedData)/sizeof(receivedData[0]), 0);

	}

	void calculateAverageTemperature() {
		averageTemp = accumulatedTemp / (++tempCount);
	}

	void calculateAccumulatedTemperature() {
		//cout << accumulatedTemp << endl;
		//cout << atoi(receivedData) << endl;
		accumulatedTemp += atoi(receivedData);
		//cout << accumulatedTemp << endl;
	}

	void closeSocket() {

		WSACleanup();
		closesocket(serverSocket);
	}
};