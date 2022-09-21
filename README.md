# Client-ServerModel

this repository contains my c++ client-server model implementation acheived by the use of network programming
i used the cmake project option when creating this function

my implementation is OOP based

the implemetation has two classes the "Server.cpp" for the server node and the "Client.cpp" for the client node (loacted in the forest). 
each of the classes has methods to help establish a communication with the other node

there is also another cpp file named "Client-ServerModel.cpp" which contains the main function which simulates the creation of the 
client and server objects and establishes a connection between each by calling the methods from both classes

the "Client-ServerModel.cpp" can be considered as a test to my implementation where there are print messages after each step to confirm successful completion of it

both nodes (client and server) use wisockets and i chose the TCP protocol for reliable communication between the two nodes

afte a connection is establisehd successfully between the two nodes, there is a while loop to simulate the process of data being sent from the client to the serevr 
in the "Client-ServerModel.cpp" file

please note that all the 3 files above are commented to facilitate the understanding of my implementation
