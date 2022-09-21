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

	Client(int id) {

		nodeType = "Client";
		ID = id;


	}

	void initiateWinsockDLL() {

		WSADATA wsaData;
		WORD winSockVersion = MAKEWORD(2, 2);
		wsaInitializationNum = WSAStartup(winSockVersion, &wsaData);

	}

	void createSokcet() {
		clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	void connectToServer(PCSTR IP_address, int portNum) {

		service.sin_family = AF_INET;
		InetPton(AF_INET, _T(IP_address), &service.sin_addr.s_addr);
		service.sin_port = htons(portNum);
		connectedToServerVal = connect(clientSocket, (sockaddr*)&service, sizeof(service));

	}

	void measureTemperature(int tempLowerLimit, int tempRange) {
		srand(time(0));
		string temp = to_string(tempLowerLimit + (rand() % tempRange));
		strcpy(dataToSend, temp.c_str());
	}

	void sendMessage() {
		sentDataByteCount = send(clientSocket, dataToSend, sizeof(dataToSend)/sizeof(dataToSend[0]), 0);

	}

	void closeSocket() {

		WSACleanup();
		closesocket(clientSocket);
	}
};