//Librecord Server pour Windows.
//Créé et développé par Pierre Vialtelle et Hadrien Cros.

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#define addrServ "127.0.0.1"
#define port 55555
//#include "stdafx.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Bienvenue dans la version server de Librecord." << endl;

	//Connexion serveur/client : 

	//ETAPE 1 : initialisation de la librairie et téléchargement de la dll de Winsock
	SOCKET serverSocket, acceptSocket;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		cout << "Erreur fatale : Winsock dll INtrouvable ! " << endl;
		return 1;
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
		cout << "Erreur fatale lors de la création de socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 2;
	}
	else
	{
		cout << "socket() is OK !" << endl;
	}

	//ETAPE 3 : Mise en relation du port et de l'IP
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T(addrServ), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		cout << "Erreur fatale : bind() échoué : " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 4;
	}
	else
	{
		cout << "Bind() OK ! " << endl;
	}

	//ETAPE 4 : Mise en écoute du server 
	if (listen(serverSocket, 1) == SOCKET_ERROR)
	{
		cout << "listen() : Erreur lors de l'écoute sur le socket" << WSAGetLastError() << endl;
		return 5;
	}
	else
		cout << "listen() OK, en attente de connexions" << endl;

	int code(0);
	do
	{
		//ETAPE 5 : Acceptation de la connexion client 
		acceptSocket = accept(serverSocket, NULL, NULL);
		if (acceptSocket == INVALID_SOCKET)
		{
			cout << "Erreur fatale lors de l'acceptions de la connexion avec le client distant" << WSAGetLastError() << endl;
			WSACleanup();
			code = 1;
		}
		else
		{
			cout << "Connexion acceptée" << endl;
			code = 0;
		}


	} while (code != 0);

	//ETAPE 6 :  Parler au Client;
	char buffer[200];
	int bytesCount = recv(acceptSocket, buffer, 200, 0);
	if (bytesCount > 0)
	{
		cout << "Message recu : " << buffer << endl;
	}
	else
	{
		WSACleanup();
	}

	//ETAPE 7 : Fermeture du socket
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
