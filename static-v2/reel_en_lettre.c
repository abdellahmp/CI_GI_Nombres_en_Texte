#include <stdio.h>
#include <string.h>

// Mots des nombres en français
const char *unites[10] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf"};
const char *dizaines[10] = {
    "", "dix", "vingt", "trente", "quarante", "cinquante", "soixante", "soixante", "quatre-vingt", "quatre-vingt"
};
const char *exceptions[10] = {
    "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"
};

// Tableaux pour les unités de nombres
const long long diviseurs_unites[] = {1000000000LL, 1000000LL, 1000LL, 1LL};
const char *noms_unites[] = {"milliard", "million", "mille", ""};
const int NOMBRE_UNITES = 4;

// Codes d'erreur et limites
#define AUCUNE_ERREUR 0
#define ERREUR_LONGUEUR 1
#define ERREUR_NON_NUMERIQUE 2
#define ERREUR_FORMAT_DECIMAL 3
#define CHIFFRES_MAX 12
#define DECIMALES_MAX 9

// Déclarations des fonctions
void convertir_dizaine(long long nombre, char *resultat);

void convertir_centaines(long long nombre, char *resultat);

void gerer_dizaines_speciales(long long nombre, char *resultat);

int valider_entree(const char *entree);

int longueur_chaine(const char *chaine);

void extraire_parties_nombre(const char *entree, char *partie_entiere, char *partie_decimale);

void convertir_nombre_en_lettres(const char *entree, char *resultat);

void convertir_nombre_en_lettres_entier(const char *entree, char *resultat);

long long convertir_en_nombre(const char *chaine);

int trouver_premier_diviseur(long long nombre);

void convertir_decimales(const char *partie_decimale, char *resultat);

void convertir_decimales_groupees(const char *partie_decimale, char *resultat);


// Retourne la longueur d'une chaîne de caractères
int longueur_chaine(const char *chaine) {
    int longueur = 0;
    while (chaine[longueur] != '\0') {
        longueur++;
    }
    return longueur;
}


// Improved input validation
int valider_entree(const char *entree) {
    int i = 0;
    int point_trouve = 0;
    int chiffres_avant_point = 0;
    int chiffres_apres_point = 0;

    // Check sign
    if (entree[0] == '+' || entree[0] == '-') {
        i = 1;
    }

    // Empty string check
    if (entree[i] == '\0') return ERREUR_NON_NUMERIQUE;

    // Validate each character
    for (; entree[i] != '\0'; i++)
    {
        if (entree[i] == '.' || entree[i] == ',') {
            if (point_trouve || (i == 1 && (entree[0] == '+' || entree[0] == '-'))) {
                return ERREUR_FORMAT_DECIMAL;
            }
            point_trouve = 1;
            continue;
        }



        if (entree[i] < '0' || entree[i] > '9') {
            return ERREUR_NON_NUMERIQUE;
        }

        if (!point_trouve) {
            chiffres_avant_point++;
        } else {
            chiffres_apres_point++;
        }
    }

    if (chiffres_avant_point > CHIFFRES_MAX || chiffres_apres_point > DECIMALES_MAX) {
        return ERREUR_LONGUEUR;
    }

    return AUCUNE_ERREUR;
}

// Extrait les parties entière et décimale d'un nombre
void extraire_parties_nombre(const char *entree, char *partie_entiere, char *partie_decimale) {
    int i = 0;
    int j = 0;
    int point_trouve = 0;

    // Copier le signe si présent
    if (entree[0] == '-' || entree[0] == '+') {
        partie_entiere[j++] = entree[i++];
    }

    // Parcourir la chaîne
    while (entree[i] != '\0') {
        if (entree[i] == '.' || entree[i] == ',') {
            point_trouve = 1;
            partie_entiere[j] = '\0';
            j = 0;
        } else if (!point_trouve) {
            partie_entiere[j++] = entree[i];
        } else {
            partie_decimale[j++] = entree[i];
        }
        i++;
    }

    // Terminer les chaînes
    if (!point_trouve) {
        partie_entiere[j] = '\0';
        partie_decimale[0] = '\0';
    } else {
        partie_decimale[j] = '\0';
    }
}


void convertir_nombre_en_lettres(const char *entree, char *resultat) {
    char partie_entiere[CHIFFRES_MAX + 2];
    char partie_decimale[DECIMALES_MAX + 1];
    resultat[0] = '\0';


    extraire_parties_nombre(entree, partie_entiere, partie_decimale);

    // Handle the coma in debut of the numbre
    if ((entree[0] == ',' || entree[0] == '.')&& partie_entiere[0] == '\0'){
        partie_entiere[0] = '0';
        partie_entiere[1] = '\0';
    }

    // Handle zero case properly
    if (strcmp(partie_entiere, "0") == 0 && partie_decimale[0] == '\0') {
        strcpy(resultat, "zéro");
        return;
    }

    // Handle zero before decimal point
    if (strcmp(partie_entiere, "0") == 0) {
        strcpy(resultat, "zéro");
    } else {
        convertir_nombre_en_lettres_entier(partie_entiere, resultat);
    }

    // Convert decimal part
    convertir_decimales_groupees(partie_decimale, resultat);
}

void convertir_decimales_groupees(const char *partie_decimale, char *resultat) {
    if (partie_decimale[0] == '\0') return;

    // Count leading zeros and add them to result
    int i = 0;
    while (partie_decimale[i] == '0') {
        if (i == 0) {
            strcat(resultat, " virgule");
        }
        strcat(resultat, " zéro");
        i++;
    }

    // If all zeros, we're done
    if (partie_decimale[i] == '\0') return;

    // If we haven't added "virgule" yet (no leading zeros)
    if (i == 0) {
        strcat(resultat, " virgule");
    }

    // Convert the rest as a regular number
    strcat(resultat, " ");
    char nombre_temp[DECIMALES_MAX + 1];
    strcpy(nombre_temp, partie_decimale + i);
    char resultat_temp[1000] = "";
    convertir_nombre_en_lettres_entier(nombre_temp, resultat_temp);
    strcat(resultat, resultat_temp);
}


// Fonction auxiliaire pour convertir la partie entière
void convertir_nombre_en_lettres_entier(const char *entree, char *resultat) {
    resultat[0] = '\0';
    long long nombre = convertir_en_nombre(entree);

    // Traiter les nombres négatifs
    if (nombre < 0) {
        strcat(resultat, "moins ");
        nombre = -nombre;
    }

    // Trouver l'indice de l'unité de départ
    int indice_debut = trouver_premier_diviseur(nombre);
    int premiere_partie = 1;

    // Traiter à partir du chiffre significatif
    for (int i = indice_debut; i < NOMBRE_UNITES; i++) {
        long long valeur_courante = nombre / diviseurs_unites[i];
        if (valeur_courante > 0) {
            if (!premiere_partie) {
                strcat(resultat, " ");
            }
            premiere_partie = 0;

            convertir_centaines(valeur_courante, resultat);

            if (noms_unites[i][0] != '\0') {
                strcat(resultat, " ");
                strcat(resultat, noms_unites[i]);
                if (valeur_courante > 1 && strcmp(noms_unites[i], "mille") != 0) {
                    strcat(resultat, "s");
                }
            }
        }
        nombre %= diviseurs_unites[i];
    }
}

// Convertit les nombres de 1 à 999 en lettres
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

// Convertit les nombres de 1 à 99 en lettres
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

// Gère les cas spéciaux pour les nombres 70-79 et 90-99
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


// Improved decimal part handling
void convertir_decimales(const char *partie_decimale, char *resultat) {
    if (partie_decimale[0] == '\0') return;

    strcat(resultat, " virgule");

    // Handle leading zeros
    int i = 0;
    while (partie_decimale[i] == '0') {
        strcat(resultat, " zéro");
        i++;
    }

    // Convert remaining digits
    while (partie_decimale[i] != '\0') {
        int chiffre = partie_decimale[i] - '0';
        strcat(resultat, " ");

        // Handle special cases for 1-19
        if (i + 1 < strlen(partie_decimale)) {
            int next_chiffre = partie_decimale[i + 1] - '0';
            int nombre = chiffre * 10 + next_chiffre;

            if (chiffre == 1 || (chiffre >= 7 && chiffre <= 9)) {
                char temp[100] = "";
                convertir_dizaine(nombre, temp);
                strcat(resultat, temp);
                i += 2;
                continue;
            }
        }

        if (chiffre == 0) {
            strcat(resultat, "zéro");
        } else {
            strcat(resultat, unites[chiffre]);
        }
        i++;
    }
}


// Convertit une chaîne de caractères en nombre
long long convertir_en_nombre(const char *chaine) {
    long long nombre = 0;
    int i = 0;
    int negatif = 0;

    if (chaine[0] == '-') {
        negatif = 1;
        i = 1;
    } else if (chaine[0] == '+') {
        i = 1;
    }

    while (chaine[i] != '\0') {
        nombre = nombre * 10 + (chaine[i] - '0');
        i++;
    }

    return negatif ? -nombre : nombre;
}


// Trouve le premier diviseur significatif pour le nombre parmis les unites
int trouver_premier_diviseur(long long nombre) {
    for (int i = 0; i < NOMBRE_UNITES; i++) {
        if (nombre / diviseurs_unites[i] > 0) {
            return i;
        }
    }
    return NOMBRE_UNITES - 1; // Par defaut, retourne l'unite la plus petite
}


int main(void) {
    char entree[CHIFFRES_MAX + DECIMALES_MAX + 2]; // +2 pour le point décimal et le caractère nul
    char resultat[1000] = "";

    printf("Entrez un nombre (max %d chiffres avant et %d après la virgule) : ", CHIFFRES_MAX, DECIMALES_MAX);
    scanf("%s", entree);

    int erreur = valider_entree(entree);
    if (erreur == AUCUNE_ERREUR) {
        convertir_nombre_en_lettres(entree, resultat);
        printf("Le nombre %s en lettres est : %s\n", entree, resultat);
    } else {
        switch (erreur) {
            case ERREUR_LONGUEUR:
                printf("Erreur : nombre trop long\n");
                break;
            case ERREUR_NON_NUMERIQUE:
                printf("Erreur : entrée non numérique\n");
                break;
            case ERREUR_FORMAT_DECIMAL:
                printf("Erreur : format décimal invalide\n");
                break;
        }
    }

    return 0;
}
