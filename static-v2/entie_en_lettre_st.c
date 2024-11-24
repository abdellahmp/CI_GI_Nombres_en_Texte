#include <stdio.h>
#include <string.h>

// Mots des nombres en français
const char *unites[] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf"};
const char *dizaines[] = {"", "dix", "vingt", "trente", "quarante", "cinquante", "soixante", "soixante", "quatre-vingt", "quatre-vingt"};
const char *exceptions[] = {"dix", "onze", "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};

// Tableaux pour les unités de nombres (pour facilitate la modifications de la taille de nombre que le programme peut convertir)
// Pour ajouter une unite il suffit d'ajouter la valeur numirique de l'unite dans le tableou "diviseurs_unites" et ajouter le nom de l'unite dans le tableou "noms_unites"
const long long diviseurs_unites[] = { 1000000000LL, 1000000LL, 1000LL, 1LL};
const char *noms_unites[] = {"milliard", "million", "mille", ""};
const int NOMBRE_UNITES = 4; // la taille des tableaux des unites (il est nécessaire que les deux tableoux doit de la meme taille)

// Codes d'erreur et nombre maximum de chiffres dans un nombre
#define AUCUNE_ERREUR 0
#define ERREUR_LONGUEUR 1
#define ERREUR_NON_NUMERIQUE 2
#define CHIFFRES_MAX 12 // Si tu as changer les tableoux d'unites il fout que tu changes ce nombre pour corespondre a le nombre de chiffre dans l'unite la plus garnde

// Déclarations des fonctions
void convertir_dizaine(long long nombre, char *resultat);
void convertir_centaines(long long nombre, char *resultat);
void gerer_dizaines_speciales(long long nombre, char *resultat);
int valider_entree(const char *entree);
int longueur_chaine(const char *chaine);
long long convertir_en_nombre(const char *chaine);
int trouver_premier_diviseur(long long nombre);
void convertir_nombre_en_lettres(const char *entree, char *resultat);

// Retourne la longueur d'une chaîne de caractères
int longueur_chaine(const char *chaine) {
    int longueur = 0;
    while (chaine[longueur] != '\0') {
        longueur++;
    }
    return longueur;
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

// Valide l'entrée utilisateur
int valider_entree(const char *entree) {
    int i = 0;

    // Vérifier la longueur
    if (longueur_chaine(entree) > CHIFFRES_MAX) {
        return ERREUR_LONGUEUR;
    }

    // Vérifier le signe
    if (entree[0] == '+' || entree[0] == '-') {
        i = 1;
    }

    // Vérifier si tous les caractères sont des chiffres
    for (; entree[i] != '\0'; i++) {
        if (entree[i] < '0' || entree[i] > '9') {
            return ERREUR_NON_NUMERIQUE;
        }
    }

    return AUCUNE_ERREUR;
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

// Trouve le premier diviseur significatif pour le nombre parmis les unites
int trouver_premier_diviseur(long long nombre) {
    for (int i = 0; i < NOMBRE_UNITES; i++) {
        if (nombre / diviseurs_unites[i] > 0) {
            return i;
        }
    }
    return NOMBRE_UNITES - 1;  // Par defaut, retourne l'unite la plus petite
}

// Fonction principale de conversion d'un nombre en lettres
void convertir_nombre_en_lettres(const char *entree, char *resultat) {
    resultat[0] = '\0';
    long long nombre = convertir_en_nombre(entree);

    // Traiter le zéro
    if (nombre == 0) {
        strcpy(resultat, "zéro");
        return;
    }

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
            // Ajouter un espace entre les parties si ce n'est pas la première
            if (!premiere_partie) {
                strcat(resultat, " ");
            }
            premiere_partie = 0;

            // Convertir la partie courante
            convertir_centaines(valeur_courante, resultat);

            // Ajouter le nom de l'unité si ce n'est pas la dernière unité
            if (noms_unites[i][0] != '\0') {
                strcat(resultat, " ");
                strcat(resultat, noms_unites[i]);
                // Ajouter le 's' du pluriel si nécessaire (sauf pour "mille")
                if (valeur_courante > 1 && strcmp(noms_unites[i], "mille") != 0) {
                    strcat(resultat, "s");
                }
            }
        }
        nombre %= diviseurs_unites[i];
    }
}

int main(void) {
    char entree[CHIFFRES_MAX + 1];  // +1 pour le caractère nul
    char resultat[1000] = "";

    printf("Entrez un nombre (jusqu'à %d chiffres) : ", CHIFFRES_MAX);
    scanf("%s", entree);

    int erreur = valider_entree(entree);
    if (erreur == AUCUNE_ERREUR) {
        convertir_nombre_en_lettres(entree, resultat);
        printf("Le nombre %s en lettres est : %s\n", entree, resultat);
    } else {
        switch (erreur) {
            case ERREUR_LONGUEUR:
                printf("Erreur : nombre trop long (maximum %d chiffres avec le singe)\n", CHIFFRES_MAX);
                break;
            case ERREUR_NON_NUMERIQUE:
                printf("Erreur : entrée non numérique\n");
                break;
        }
    }

    return 0;
}