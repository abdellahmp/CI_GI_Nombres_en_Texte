#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// French number words
const char *unites[] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf"};
const char *dizaines[] = {"", "dix", "vingt", "trente", "quarante", "cinquante", "soixante", "soixante", "quatre-vingt", "quatre-vingt"};
const char *exceptions[] = {"dix", "onze", "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};

// Error codes
#define ERREUR_AUCUNE 0
#define ERREUR_TROP_LONG 1
#define ERREUR_NON_NUMERIQUE 2

// Function declarations
void convertir_dizaine(long long nombre, char *resultat);

void convertir_centaines(long long nombre, char *resultat);

void gerer_dizaines_speciales(long long nombre, char *resultat);

int valider_entree(const char *entree);

int longueur_chaine(const char *str);

long long convertir_en_nombre(const char *str);


int longueur_chaine(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}


long long convertir_en_nombre(const char *str) {
    long long nombre = 0;
    int i = 0;
    int negatif = 0;

    if (str[0] == '-') {
        negatif = 1;
        i = 1;
    } else if (str[0] == '+') {
        i = 1;
    }

    while (str[i] != '\0') {
        nombre = nombre * 10 + (str[i] - '0');
        i++;
    }

    return negatif ? -nombre : nombre;
}

int valider_entree(const char *entree) {
    int i = 0;

    // Check length (allowing for 12 digits plus possible sign)
    if (longueur_chaine(entree) > 13) {
        return ERREUR_TROP_LONG;
    }

    // Check sign
    if (entree[0] == '+' || entree[0] == '-') {
        i = 1;
    }

    // Check if all characters are digits
    for (; entree[i] != '\0'; i++) {
        if (entree[i] < '0' || entree[i] > '9') {
            return ERREUR_NON_NUMERIQUE;
        }
    }

    return ERREUR_AUCUNE;
}

void gerer_dizaines_speciales(long long nombre, char *resultat) {
    if (nombre >= 70 && nombre <= 79) {
        strcat(resultat, "soixante");
        if (nombre == 71) {
            strcat(resultat, " et onze");
        } else if (nombre > 70) {
            strcat(resultat, "-");
            convertir_dizaine(nombre - 60, resultat);
        } else {
            strcat(resultat, "-dix");
        }
    } else if (nombre >= 90 && nombre <= 99) {
        strcat(resultat, "quatre-vingt");
        if (nombre > 90) {
            strcat(resultat, "-");
            convertir_dizaine(nombre - 80, resultat);
        } else {
            strcat(resultat, "-dix");
        }
    }
}

void convertir_dizaine(long long nombre, char *resultat) {
    if (nombre == 0) {
        return;
    } else if (nombre < 10) {
        strcat(resultat, unites[nombre]);
    } else if (nombre < 20) {
        strcat(resultat, exceptions[nombre - 10]);
    } else if (nombre == 20 || nombre == 30 || nombre == 40 || nombre == 50 || nombre == 60 || nombre == 80) {
        strcat(resultat, dizaines[nombre / 10]);
        if (nombre == 80) {
            strcat(resultat, "s");
        }
    } else if (nombre >= 70 && nombre <= 99) {
        gerer_dizaines_speciales(nombre, resultat);
    } else {
        long long dizaine = nombre / 10;
        long long unite = nombre % 10;
        if (unite == 1 && dizaine < 8) {
            strcat(resultat, dizaines[dizaine]);
            strcat(resultat, " et un");
        } else {
            strcat(resultat, dizaines[dizaine]);
            strcat(resultat, "-");
            strcat(resultat, unites[unite]);
        }
    }
}

void convertir_centaines(long long nombre, char *resultat) {
    if (nombre >= 100) {
        if (nombre == 100) {
            strcat(resultat, "cent");
            return;
        }

        long long centaines = nombre / 100;
        if (centaines > 1) {
            strcat(resultat, unites[centaines]);
            strcat(resultat, " cent");
        } else {
            strcat(resultat, "cent");
        }

        if (nombre % 100 > 0) {
            strcat(resultat, " ");
            convertir_dizaine(nombre % 100, resultat);
        }
    } else {
        convertir_dizaine(nombre, resultat);
    }
}

void convertir_nombre_en_lettres(const char *entree, char *resultat) {
    resultat[0] = '\0';



    // Convert string to long long
    long long nombre = convertir_en_nombre(entree);

    // Handle zero
    if (nombre == 0) {
        strcpy(resultat, "zéro");
        return;
    }

    // Handle negative numbers
    if (nombre < 0) {
        strcat(resultat, "moins ");
        nombre = -nombre;
    }

    // Break down the number
    long long milliards = nombre / 1000000000;
    long long millions = (nombre / 1000000) % 1000;
    long long milliers = (nombre / 1000) % 1000;
    long long reste = nombre % 1000;

    // Convert billions
    if (milliards > 0) {
        convertir_centaines(milliards, resultat);
        strcat(resultat, " milliard");
        if (milliards > 1)
            strcat(resultat, "s");
        if (millions > 0 || milliers > 0 || reste > 0)
            strcat(resultat, " ");
    }

    // Convert millions
    if (millions > 0) {
        convertir_centaines(millions, resultat);
        strcat(resultat, " million");
        if (millions > 1)
            strcat(resultat, "s");
        if (milliers > 0 || reste > 0)
            strcat(resultat, " ");
    }

    // Convert thousands
    if (milliers > 0) {
        if (milliers > 1) {
            convertir_centaines(milliers, resultat);
            strcat(resultat, " mille");
        } else {
            strcat(resultat, "mille");
        }
        if (reste > 0)
            strcat(resultat, " ");
    }

    // Convert remainder
    if (reste > 0) {
        convertir_centaines(reste, resultat);
    }
}


int main(void) {
    char entree[100];
    char resultat[1000] = "";

    printf("Entrez un nombre (jusqu'à 12 chiffres) : ");
    scanf("%s", entree);
    // Validate input
    int erreur = valider_entree(entree);
    if (erreur == ERREUR_AUCUNE) {
        convertir_nombre_en_lettres(entree, resultat);
        printf("Le nombre %s en lettres est : %s\n", entree, resultat);
    }
    else {
        switch (erreur) {
            case ERREUR_TROP_LONG:
                printf("Erreur: nombre trop long");
                break;
            case ERREUR_NON_NUMERIQUE:
                printf("Erreur: entrée non numérique");
                break;
        }
    }


    return 0;
}
