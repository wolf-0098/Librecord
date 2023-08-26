//Librecord Server pour Windows.
//Créé et développé par Pierre Vialtelle et Hadrien Cros.

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
//#include "stdafx.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Bienvenue dans la version server de Librecord." << endl;

	//Connexion serveur/client : 

	//ETAPE 1 : initialisation de la librairie et téléchargement de la dll de Winsock
	SOCKET serverSocket, acceptSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		cout << "Error : Winsock dll NOT found ! " << endl;
		return 0;
	}
	else
	{
		cout << "The Winsock dll found !" << endl;
		cout << "The status : " << wsaData.szSystemStatus << endl;
	}

	//ETAPE 2 : Initialisation du socket 
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "socket() is OK !" << endl;
	}

	//ETAPE 3 : Mise en relation du port et de l'IP
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		cout << "bind() failed : " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "Bind() is OK ! " << endl;
	}

	//ETAPE 4 : Mise en écoute du server 
	if (listen(serverSocket, 1) == SOCKET_ERROR)
		cout << "listen() : Error listening on socket" << WSAGetLastError() << endl;
	else
		cout << "listen() is OK, I'm waiting for connections... " << endl;

	//ETAPE 5 : Acceptation de la connexion client 
	acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET)
	{
		cout << "accept failed " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "Accepted conection" << endl;
	system("pause");
	WSACleanup();


	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.