#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// listes d'unités et de leurs valeurs numériques et leur nombres, pour faciliter l'extension future.
// Pour ajouter une unité, il faut ajouter son nom dans la liste "noms_unites"
// et sa valeur numérique dans la liste "diviseurs_unites". Assurez-vous que les deux
// ont le même ordre dans les listes respectives.
// N'oubliez pas de mettre à jour "NOMBRE_UNITES" pour qu'il corresponde à la longueur des listes.
// Remarque : le pas entre les unités doit être de 1000.
const long long diviseurs_unites[] = {1000000000LL, 1000000LL, 1000LL, 1LL};
const char *noms_unites[] = {"milliard", "million", "mille", ""};
const int NOMBRE_UNITES = 4;
// Pointeur vers le tableau qui contiendra les nombres en français
// et variable pour suivre combien de nombres sont chargés
char **frenchNumbers = NULL;
int numbersLoaded = 0;

// Codes d'erreur et limites.
#define AUCUNE_ERREUR 0
#define ERREUR_LONGUEUR 1
#define ERREUR_NON_NUMERIQUE 2
#define CHIFFRES_MAX  (NOMBRE_UNITES*3) // Le nombre maximal de chiffres dans le nombre que l'utilisateur peut entrer correspond au nombre d'unités.
#define MAX_WORD_LENGTH 100 // la taille maximale qu'un nombre écrit peut avoir


// Déclarations de fonctions.

// Fonction pour charger les nombres depuis un fichier
int loadFrenchNumbers(const char *filename);

// Fonction pour libérer la mémoire allouée
void freeFrenchNumbers();

// Valider que la chaîne de caractères correspond à un nombre valide (entier dans ce cas).
int valider_entree(const char *entree);

// Convertir la chaîne de caractères en un nombre numérique.
long long convertir_en_nombre(const char *chaine);

// Procédure principale de conversion.
void convertir_nombre_en_lettres(const char *entree, char *resultat);

// Prendre un entier positif, le convertir en lettres et l'ajouter à la liste résultat.
void convertir_nombre_entiere(long long nombre, char *resultat);


// Main
//----------------------------------------------------------------------------------------------------------------------
int main(void) {
    // Charger les nombres à partir du fichier
    if (!loadFrenchNumbers("french_numbers.txt")) {
        printf("Error: Failed to load French numbers from file\n");
        return 1;
    }

    char entree[CHIFFRES_MAX + 2]; // +2 pour le signe et le terminateur nul.
    char resultat[1000] = "";

    printf("Entrez un nombre entier (max %d chiffres) : ", CHIFFRES_MAX);
    scanf("%s", entree);

    int erreur = valider_entree(entree);
    if (erreur == AUCUNE_ERREUR) {
        // Vérifier s'il n'y a pas d'erreurs.
        convertir_nombre_en_lettres(entree, resultat);
        printf("Le nombre %s en lettres est : %s\n", entree, resultat);
    } else {
        // Si une erreur existe, indiquer quelle erreur a été rencontrée pour informer l'utilisateur.
        switch (erreur) {
            case ERREUR_LONGUEUR:
                printf("Erreur : nombre trop long\n");
                break;
            case ERREUR_NON_NUMERIQUE:
                printf("Erreur : entrée non numérique\n");
                break;
        }
    }

    freeFrenchNumbers();
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------
// Fonctions et procédures
//----------------------------------------------------------------------------------------------------------------------

// Fonction pour charger les nombres depuis un fichier
// Retourne 1 si succès, 0 si échec
int loadFrenchNumbers(const char *filename) {
    // Ouvre le fichier en mode lecture
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // Si l'ouverture échoue, affiche une erreur et retourne 0
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }

    // Alloue la mémoire initiale pour le tableau de pointeurs
    // Peut stocker jusqu'à 1000 nombres
    frenchNumbers = malloc(1000 * sizeof(char *));
    if (frenchNumbers == NULL) {
        // Si l'allocation échoue, ferme le fichier et retourne 0
        fclose(file);
        return 0;
    }

    // Buffer temporaire pour lire chaque ligne
    char line[MAX_WORD_LENGTH];
    int index = 0;

    // Read each line from the file
    while (fgets(line, sizeof(line), file) && index < 1000) {
        // Supprime le caractère de nouvelle ligne si présent
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Alloue la mémoire pour ce nombre spécifique
        frenchNumbers[index] = malloc(strlen(line) + 1);
        if (frenchNumbers[index] == NULL) {
            // En cas d'échec d'allocation, libère toute la mémoire déjà allouée
            for (int i = 0; i < index; i++) {
                free(frenchNumbers[i]);
            }
            free(frenchNumbers);
            fclose(file);
            return 0;
        }
        // Copie la ligne dans le tableau
        strcpy(frenchNumbers[index], line);
        index++;
    }

    // Sauvegarde le nombre total de nombres chargés
    numbersLoaded = index;
    // Ferme le fichier
    fclose(file);
    return 1;
}

// Fonction pour libérer la mémoire allouée
void freeFrenchNumbers() {
    if (frenchNumbers != NULL) {
        for (int i = 0; i < numbersLoaded; i++) {
            free(frenchNumbers[i]);
        }
        free(frenchNumbers);
        frenchNumbers = NULL;
    }
}


int valider_entree(const char *entree) {
    int i = 0;
    int chiffres = 0;

    // Vérifier si l'utilisateur a saisi un signe.
    if (entree[0] == '+' || entree[0] == '-') {
        i = 1; // Si oui, ignorer le signe.
    }

    // Vérification de chaîne vide
    if (entree[i] == '\0') return ERREUR_NON_NUMERIQUE;

    // Valider chaque caractère et compter les chiffres
    for (; entree[i] != '\0'; i++) {
        if (entree[i] < '0' || entree[i] > '9') {
            return ERREUR_NON_NUMERIQUE;
        }
        chiffres++;
    }

    // Ne pas compter les zéros non significatifs
    i = (entree[0] == '+' || entree[0] == '-') ? 1 : 0;
    while (entree[i] == '0' && entree[i + 1] != '\0') {
        chiffres--;
        i++;
    }

    // Vérifier la longueur du nombre (nombre de chiffres)
    // (C'est très important pour ne pas dépasser le nombre que l'on peut convertir selon les unités que l'on a configurées)
    if (chiffres > CHIFFRES_MAX) {
        return ERREUR_LONGUEUR;
    }

    return AUCUNE_ERREUR;
}

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

void convertir_nombre_en_lettres(const char *entree, char *resultat) {
    resultat[0] = '\0';
    long long nombre = convertir_en_nombre(entree);

    // Gérer les nombres négatifs
    if (nombre < 0) {
        strcat(resultat, "moins ");
        nombre = -nombre;
    }

    if (nombre == 0) {
        // Gérer le cas zéro
        strcat(resultat, frenchNumbers[0]);
    } else {
        convertir_nombre_entiere(nombre, resultat);
    }
}

void convertir_nombre_entiere(long long nombre, char *resultat) {
    if (nombre < 1000) {
        // Si le nombre est inférieur à 1000,
        strcat(resultat, frenchNumbers[nombre]);
        //utiliser directement la valeur correspondante dans le tableau frenchNumbers.
        return;
    }

    int premiere_partie = 1; // Pour indiquer si l'on est dans la première partie du nombre (les 3 premiers chiffres).

    for (int i = 0; i < NOMBRE_UNITES; i++) {
        // Commence par la plus grande unité que l'on ait (par exemple, milliard, million, etc.).

        long long valeur_courante = nombre / diviseurs_unites[i];
        // Déterminer combien de fois une unité est contenue dans le nombre.

        if (valeur_courante > 0) {
            if (!premiere_partie) {
                strcat(resultat, " "); // Si ce n'est pas la première partie, ajouter un espace.
            }
            premiere_partie = 0;
            // Après la première unité, on est sûr qu'on n'est plus dans la première partie du nombre.

            if (valeur_courante < 1000) {
                strcat(resultat, frenchNumbers[valeur_courante]);
                // Ajouter la valeur correspondante en lettres pour les nombres inférieurs à 1000.
            }

            // Ajouter le nom de l'unité (milliard, million, mille)
            if (noms_unites[i][0] != '\0') {
                strcat(resultat, " ");
                strcat(resultat, noms_unites[i]); // Ajouter l'unité (ex: milliard, million, mille).
                if (valeur_courante > 1 && strcmp(noms_unites[i], "mille") != 0) {
                    // Gérer le cas du pluriel, sauf pour "mille"
                    strcat(resultat, "s"); // Ajouter "s" pour les unités au pluriel (par exemple, milliards).
                }
            }
        }
        nombre %= diviseurs_unites[i];
        // Réduire le nombre pour traiter la partie suivante (les unités restantes après division).
    }
}
