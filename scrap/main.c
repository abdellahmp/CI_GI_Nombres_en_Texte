#include <stdio.h>
#include <string.h>

const char *unites[] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf"};
const char *dizaines[] = {"", "dix", "vingt", "trente", "quarante", "cinquante", "soixante", "", "quatre-vingt"};
const char *exceptions[] = {"dix", "onze", "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};




int est_nombre_entier(const char *entree);

int longueur_chaine(const char *entree);

void convertir_nombre(const char *entree, char *résultat);





int main(void) {
    char entree[100];
    char résultat[500] = "";
    printf("Entrez un nombre (jusqu'à 12 chiffres) : ");
    scanf("%s", entree);

    printf("Le nombre %s en lettres est : ", entree);
    convertir_nombre(entree, résultat);
    printf("Nombre en lettres : %s\n", résultat);
    printf("\n");

    return 0;
}



int est_nombre_entier(const char *entree) {
    int i = 0;

    if (entree[0] == '\0') {
        return 0;
    }

    if (entree[0] == '+' || entree[0] == '-') {
        i = 1;
    }

    for (; entree[i] != '\0'; i++) {
        if (entree[i] < '0' || entree[i] > '9') {
            return 0;
        }
    }

    return 1;
}

int longueur_chaine(const char *entree) {
    int longueur = 0;

    while (entree[longueur] != '\0') {
        longueur++;
    }

    return longueur;
}


void convertir_dizaine(int nombre, char *résultat) {
    if (nombre < 10) {
        strcat(résultat, unites[nombre]);
    } else if (nombre < 20) {
        strcat(résultat, exceptions[nombre - 10]);
    } else {
        int dizaine = nombre / 10;
        int unité = nombre % 10;
        strcat(résultat, dizaines[dizaine]);
        if (unité > 0) {
            strcat(résultat, "-");
            strcat(résultat, unites[unité]);
        }
    }
}

void convertir_centaines(int nombre, char *résultat) {
    if (nombre >= 100) {
        int centaines = nombre / 100;
        if (centaines > 1) {
            strcat(résultat, unites[centaines]);
            strcat(résultat, " cent");
        } else {
            strcat(résultat, "cent");
        }
        if (nombre % 100 > 0) strcat(résultat, " ");
    }
    convertir_dizaine(nombre % 100, résultat);
}

void convertir_milliers(int nombre, char *résultat) {
    if (nombre >= 1000) {
        int milliers = nombre / 1000;
        if (milliers > 1) convertir_centaines(milliers, résultat);
        strcat(résultat, " mille");
        if (nombre % 1000 > 0) strcat(résultat, " ");
    }
    convertir_centaines(nombre % 1000, résultat);
}

void convertir_millions(int nombre, char *résultat) {
    if (nombre >= 1000000) {
        int millions = nombre / 1000000;
        convertir_centaines(millions, résultat);
        strcat(résultat, " million");
        if (millions > 1) strcat(résultat, "s");
        if (nombre % 1000000 > 0) strcat(résultat, " ");
    }
    convertir_milliers(nombre % 1000000, résultat);
}

void convertir_milliards(int nombre, char *résultat) {
    if (nombre >= 1000000000) {
        int milliards = nombre / 1000000000;
        convertir_centaines(milliards, résultat);
        strcat(résultat, " milliard");
        if (milliards > 1) strcat(résultat, "s");
        if (nombre % 1000000000 > 0) strcat(résultat, " ");
    }
    convertir_millions(nombre % 1000000000, résultat);
}

void convertir_nombre(const char *entree, char *résultat) {
    int len = longueur_chaine(entree);
    int nombre = 0, i =0;
    if (entree[0] == '-') {
        strcat(résultat, "moins ");
        i++;
    }else if(entree[0] == '+'){
        i++;
    }

    for (; i < len; i++) {
        nombre = nombre * 10 + (entree[i] - '0');
    }

    if (nombre == 0) {
        strcpy(résultat, "zéro");
    } else {
        convertir_milliards(nombre, résultat);
    }
}