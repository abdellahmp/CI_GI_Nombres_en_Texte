#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Listes d'unités et de leurs valeurs numériques et leurs nombres, pour faciliter l'extension future.
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


// Codes d'erreur et limites
#define AUCUNE_ERREUR 0
#define ERREUR_LONGUEUR 1
#define ERREUR_NON_NUMERIQUE 2
#define ERREUR_FORMAT_DECIMAL 3
#define CHIFFRES_MAX (NOMBRE_UNITES*3) // Le nombre maximal de chiffres dans le nombre que l'utilisateur peut entrer correspond au nombre d'unités.
#define DECIMALES_MAX 9 // Le nombre maximal de chiffres après la virgule
#define MAX_WORD_LENGTH 100 // la taille maximale qu'un nombre écrit peut avoir

// Déclarations de fonctions.

// Fonction pour charger les nombres depuis un fichier
int loadFrenchNumbers(const char *filename);

// Fonction pour libérer la mémoire allouée
void freeFrenchNumbers();

// Valider que la chaîne de caractères correspond à un nombre valide (relle dans ce cas).
int valider_entree(const char *entree);

// Extrait la partie entière et la partie décimale du nombre sous forme de chaînes de caractères.
void extraire_parties_nombre(const char *entree, char *partie_entiere, char *partie_decimale);

// Nettoie la partie décimale en supprimant les zéros à la fin.
void nettoyer_decimales(char *partie_decimale);

// Convertit une chaîne de caractères en nombre entier (long long).
long long convertir_en_nombre(const char *chaine);

// Convertit le nombre entier et décimal en lettres.
void convertir_nombre_en_lettres(const char *entree, char *resultat);

// Convertit la partie entière du nombre en lettres.
void convertir_nombre_entiere(long long nombre, char *resultat);

// Convertit la partie décimale du nombre en lettres.
void convertir_decimales(const char *partie_decimale, char *resultat);

// Main
//----------------------------------------------------------------------------------------------------------------------
int main(void) {
    // Charger les nombres à partir du fichier
    if (!loadFrenchNumbers("french_numbers.txt")) {
        printf("Error: Failed to load French numbers from file\n");
        return 1;
    }
    char entree[CHIFFRES_MAX + DECIMALES_MAX + 2]; // +2 pour le point décimal et le caractère nul
    char resultat[1000] = "";

    // Demander à l'utilisateur d'entrer un nombre
    printf("Entrez un nombre (max %d chiffres avant et %d après la virgule) : ", CHIFFRES_MAX, DECIMALES_MAX);
    scanf("%s", entree);

    // Valider l'entrée
    int erreur = valider_entree(entree);
    if (erreur == AUCUNE_ERREUR) {
        // Convertir le nombre en lettres si l'entrée est valide
        convertir_nombre_en_lettres(entree, resultat);
        printf("Le nombre %s en lettres est : %s\n", entree, resultat);
    } else {
        // Gérer les erreurs selon le type d'erreur
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

//----------------------------------------------------------------------------------------------------------------------
// Fonctions
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
    int point_trouve = 0;
    int chiffres_avant_point = 0;
    int chiffres_apres_point = 0;
    int premier_caractere = 1;

    // Vérification du signe
    if (entree[0] == '+' || entree[0] == '-') {
        i = 1;
    }

    // Vérification de chaîne vide
    if (entree[i] == '\0') return ERREUR_NON_NUMERIQUE;

    // Validation des caractères
    for (; entree[i] != '\0'; i++) {
        if (entree[i] == '.' || entree[i] == ',') {
            if (point_trouve || premier_caractere) {
                return ERREUR_FORMAT_DECIMAL;
            }
            point_trouve = 1;
            premier_caractere = 1;
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
        premier_caractere = 0;
    }

    // Vérification de la longueur du nombre (sans compter les zéros devant)
    int j = (entree[0] == '+' || entree[0] == '-') ? 1 : 0;
    while (entree[j] == '0' && entree[j + 1] != '\0' && entree[j + 1] != '.' && entree[j + 1] != ',') {
        chiffres_avant_point--;
        j++;
    }

    // Vérification des limites de longueur
    if (chiffres_avant_point > CHIFFRES_MAX || chiffres_apres_point > DECIMALES_MAX) {
        return ERREUR_LONGUEUR;
    }

    return AUCUNE_ERREUR;
}


void extraire_parties_nombre(const char *entree, char *partie_entiere, char *partie_decimale) {
    int i = 0;
    int j = 0;
    int point_trouve = 0;

    // Gérer le signe
    if (entree[0] == '-' || entree[0] == '+') {
        partie_entiere[j++] = entree[i++];
    }

    // Ignorer les zéros au début tout en gardant au moins un zéro avant le point décimal
    while (entree[i] == '0' && entree[i + 1] != '\0' && entree[i + 1] != '.' && entree[i + 1] != ',') {
        i++;
    }

    // Traitement des caractères restants
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

    // Finalisation des chaînes
    if (!point_trouve) {
        partie_entiere[j] = '\0';
        partie_decimale[0] = '\0';
    } else {
        partie_decimale[j] = '\0';
        nettoyer_decimales(partie_decimale);
    }
}


void nettoyer_decimales(char *partie_decimale) {
    // Supprimer les zéros à la fin de la partie décimale
    int len = strlen(partie_decimale);
    while (len > 0 && partie_decimale[len - 1] == '0') {
        partie_decimale[len - 1] = '\0';
        len--;
    }
}

long long convertir_en_nombre(const char *chaine) {
    // Convertir une chaîne de caractères en nombre entier (long long)
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
    // Convertir le nombre en lettres (entier + décimal)
    char partie_entiere[CHIFFRES_MAX + 2];
    char partie_decimale[DECIMALES_MAX + 1];
    resultat[0] = '\0';

    extraire_parties_nombre(entree, partie_entiere, partie_decimale);
    long long nombre = convertir_en_nombre(partie_entiere);

    // Gérer les nombres négatifs
    if (nombre < 0) {
        strcat(resultat, "moins ");
        nombre = -nombre;
    }

    // Gérer le cas zéro
    if (nombre == 0) {
        strcat(resultat, frenchNumbers[0]);
    } else {
        convertir_nombre_entiere(nombre, resultat);
    }

    // Gérer la partie décimale
    convertir_decimales(partie_decimale, resultat);
}

void convertir_nombre_entiere(long long nombre, char *resultat) {
    // Convertir la partie entière du nombre en lettres
    if (nombre < 1000) {
        strcat(resultat, frenchNumbers[nombre]);
        return;
    }

    int premiere_partie = 1;
    for (int i = 0; i < NOMBRE_UNITES; i++) {
        long long valeur_courante = nombre / diviseurs_unites[i];
        if (valeur_courante > 0) {
            if (!premiere_partie) {
                strcat(resultat, " ");
            }
            premiere_partie = 0;

            // Convertir les nombres moins de 1000 avec l'array
            strcat(resultat, frenchNumbers[valeur_courante]);

            // Ajouter le nom de l'unité (milliard, million, mille)
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

void convertir_decimales(const char *partie_decimale, char *resultat) {
    // Convertir la partie décimale du nombre en lettres.
    if (partie_decimale[0] == '\0') return;

    strcat(resultat, " virgule");

    // Gérer les zéros initiaux avant de traiter le nombre.
    int i = 0;
    while (partie_decimale[i] == '0') {
        strcat(resultat, " zéro");
        i++;
    }

    strcat(resultat, " ");

    // Créer un tableau dynamique pour stocker une copie des chiffres après les zéros.
    char *entire_partie_decimales = malloc((DECIMALES_MAX - i) * sizeof(char));
    strncpy(entire_partie_decimales, &partie_decimale[i], DECIMALES_MAX-i);
    entire_partie_decimales[DECIMALES_MAX - i] = '\0';

    // Traiter la copie comme un entier.
    long long nombre = convertir_en_nombre(entire_partie_decimales);
    convertir_nombre_entiere(nombre, resultat);

    // Libérer la mémoire après avoir terminé le traitement.
    free(entire_partie_decimales);
}
