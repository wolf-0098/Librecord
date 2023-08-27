# Librecord
La messagerie du futur entièrement sécurisée et chiffrée.

## Principaux objectifs à atteindre pour la première version de test

### Côté serveur

 [x] Le serveur reçoit les messages
 [] Le serveur conserve les messages selon le format indiqué dans la documentation (il faut le faire tout de suite sinon ça va être compliqué de l'intégrer plus tard, parce que une architecture où tout fonctionne sans stockage ne demande pas de faire des processus d'actualisation des messages au niveau du client, ce qui demande des changement majeurs dans le code)
 [] Le serveur est compatible linux

### Côté client

 [x] Compatible windows
 [] Compatible linux (parce que j'en ai besoin et qu'il faut le faire tout de suite sinon une fois qu'il y aura trop de code à modifier, ce sera l'enfer)
 [x] Peut envoyer un message
 [] Peut télécharger les messages du serveur, avec la possibilité de choisir combien de message l'on souhaite télécharger

## Problèmes connus sur le pdf

Sur le pdf, il manque un élément essentiel que je corrigerai au plus vite.
Le voici, dans sa demande de téléchargement des messages, le client doit renseigner le dernier message qu'il a en mémoire. Pour cela, chaque message doit contenir un ID, il faut donc que le serveur renseigne un id à chanque nouveau message et qu'il transmette l'id du dernier message téléchargé au client, pour que celui-ci puisse le renvoyer au serveur par la suite, et que le serveur le donne les messages sans doublons.
