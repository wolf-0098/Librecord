#include <stdio.h>
#include <rnp/rnp.h>
#include <string.h>
#include <stdlib.h>

#define TJSONCLEF 452 
/* Taille précalculée du JSON pour créer la clef */

int genClef(unsigned char *pseudo[], unsigned char *clefPub[], unsigned char *clefPriv[]){
/* Création du JSON qui donnera les paramètres pour la génération de la clef */
  unsigned char *RSA_KEY_DESC;
  
  RSA_KEY_DESC = malloc((sizeof(pseudo) + TJSONCLEF - 1)); /* -1 correspond au caractère de fin en trop */

  if(RSA_KEY_DESC == NULL){
    return -11;
  }

  /*Ajout de la première partie du JSON */
  strcat(RSA_KEY_DESC, "{\
    'primary': {\
        'type': 'RSA',\
        'length': 2048,\
        'userid': '");
  /* Ajout du pseudo */
  strcat(RSA_KEY_DESC, pseudo);
  /* Ajout de la troisième partie du JSON */
  strcat(RSA_KEY_DESC, "',\
        'expiration': 31536000,\
        'usage': ['sign'],\
        'protection': {\
            'cipher': 'AES256',\
            'hash': 'SHA256'\
        }\
    },\
    'sub': {\
        'type': 'RSA',\
        'length': 2048,\
        'expiration': 15768000,\
        'usage': ['encrypt'],\
        'protection': {\
            'cipher': 'AES256',\
            'hash': 'SHA256'\
        }\
    }\
}");
  printf("%s\n", RSA_KEY_DESC);

  /* NE PAS OUBLIER D'AUGMENTER LE NIVEAU DU CHIFFREMENT QUAND LA FONCTION SERA OPERATIONNELLE */

/* Fin de la création du JSON pour la clef */

/* Génération de la clef RSA */
  
  free(RSA_KEY_DESC);
}




