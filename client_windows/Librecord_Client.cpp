//Librecord Client pour Windows.
//Créé par Pierre Vialtelle et Hadrien Cros.

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
	cout << "Bienvenue dans la version Client de Librecord." << endl;

	//Connexion serveur/client : 
	
	//ETAPE 1  : initialisation de la librairie et téléchargement de la dll de Winsock
	SOCKET clientSocket;
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
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Erreur fatale lors de la création de socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 2;
	}
	else
	{
		cout << "socket() OK !" << endl;
	}

	//ETAPE 3 : Connexion au serveur
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T(addrServ), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		cout << "Client erreur fatale: connect() - Connexion échouée" << endl;
		WSACleanup();
		return 3;
	}
	else
	{
		cout << "Client : connect() établi" << endl;
		cout << "Client : début de la phase d'envoi et de reception des données" << endl;
	}
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
