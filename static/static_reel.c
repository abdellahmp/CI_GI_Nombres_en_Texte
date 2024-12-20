#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Liste des nombres français de 0 à 999 en lettres.
const char *frenchNumbers[1000] = {"zéro", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf", "vingt", "vingt-un", "vingt-deux", "vingt-trois", "vingt-quatre", "vingt-cinq", "vingt-six", "vingt-sept", "vingt-huit", "vingt-neuf", "trente", "trente-un", "trente-deux", "trente-trois", "trente-quatre", "trente-cinq", "trente-six", "trente-sept", "trente-huit", "trente-neuf", "quarante", "quarante-un", "quarante-deux", "quarante-trois", "quarante-quatre", "quarante-cinq", "quarante-six", "quarante-sept", "quarante-huit", "quarante-neuf", "cinquante", "cinquante-un", "cinquante-deux", "cinquante-trois", "cinquante-quatre", "cinquante-cinq", "cinquante-six", "cinquante-sept", "cinquante-huit", "cinquante-neuf", "soixante", "soixante-un", "soixante-deux", "soixante-trois", "soixante-quatre", "soixante-cinq", "soixante-six", "soixante-sept", "soixante-huit", "soixante-neuf", "soixante", "soixante-onze", "soixante-douze", "soixante-treize", "soixante-quatorze", "soixante-quinze", "soixante-seize", "soixante-dix-sept", "soixante-dix-huit", "soixante-dix-neuf", "quatre-vingts", "quatre-vingts-un", "quatre-vingts-deux", "quatre-vingts-trois", "quatre-vingts-quatre", "quatre-vingts-cinq", "quatre-vingts-six", "quatre-vingts-sept", "quatre-vingts-huit", "quatre-vingts-neuf", "quatre-vingts", "quatre-vingts-onze", "quatre-vingts-douze", "quatre-vingts-treize", "quatre-vingts-quatorze", "quatre-vingts-quinze", "quatre-vingts-seize", "quatre-vingts-dix-sept", "quatre-vingts-dix-huit", "quatre-vingts-dix-neuf", "cent", "cent un", "cent deux", "cent trois", "cent quatre", "cent cinq", "cent six", "cent sept", "cent huit", "cent neuf", "cent dix", "cent onze", "cent douze", "cent treize", "cent quatorze", "cent quinze", "cent seize", "cent dix-sept", "cent dix-huit", "cent dix-neuf", "cent vingt", "cent vingt-un", "cent vingt-deux", "cent vingt-trois", "cent vingt-quatre", "cent vingt-cinq", "cent vingt-six", "cent vingt-sept", "cent vingt-huit", "cent vingt-neuf", "cent trente", "cent trente-un", "cent trente-deux", "cent trente-trois", "cent trente-quatre", "cent trente-cinq", "cent trente-six", "cent trente-sept", "cent trente-huit", "cent trente-neuf", "cent quarante", "cent quarante-un", "cent quarante-deux", "cent quarante-trois", "cent quarante-quatre", "cent quarante-cinq", "cent quarante-six", "cent quarante-sept", "cent quarante-huit", "cent quarante-neuf", "cent cinquante", "cent cinquante-un", "cent cinquante-deux", "cent cinquante-trois", "cent cinquante-quatre", "cent cinquante-cinq", "cent cinquante-six", "cent cinquante-sept", "cent cinquante-huit", "cent cinquante-neuf", "cent soixante", "cent soixante-un", "cent soixante-deux", "cent soixante-trois", "cent soixante-quatre", "cent soixante-cinq", "cent soixante-six", "cent soixante-sept", "cent soixante-huit", "cent soixante-neuf", "cent soixante", "cent soixante-onze", "cent soixante-douze", "cent soixante-treize", "cent soixante-quatorze", "cent soixante-quinze", "cent soixante-seize", "cent soixante-dix-sept", "cent soixante-dix-huit", "cent soixante-dix-neuf", "cent quatre-vingts", "cent quatre-vingts-un", "cent quatre-vingts-deux", "cent quatre-vingts-trois", "cent quatre-vingts-quatre", "cent quatre-vingts-cinq", "cent quatre-vingts-six", "cent quatre-vingts-sept", "cent quatre-vingts-huit", "cent quatre-vingts-neuf", "cent quatre-vingts", "cent quatre-vingts-onze", "cent quatre-vingts-douze", "cent quatre-vingts-treize", "cent quatre-vingts-quatorze", "cent quatre-vingts-quinze", "cent quatre-vingts-seize", "cent quatre-vingts-dix-sept", "cent quatre-vingts-dix-huit", "cent quatre-vingts-dix-neuf", "deux cent", "deux cent un", "deux cent deux", "deux cent trois", "deux cent quatre", "deux cent cinq", "deux cent six", "deux cent sept", "deux cent huit", "deux cent neuf", "deux cent dix", "deux cent onze", "deux cent douze", "deux cent treize", "deux cent quatorze", "deux cent quinze", "deux cent seize", "deux cent dix-sept", "deux cent dix-huit", "deux cent dix-neuf", "deux cent vingt", "deux cent vingt-un", "deux cent vingt-deux", "deux cent vingt-trois", "deux cent vingt-quatre", "deux cent vingt-cinq", "deux cent vingt-six", "deux cent vingt-sept", "deux cent vingt-huit", "deux cent vingt-neuf", "deux cent trente", "deux cent trente-un", "deux cent trente-deux", "deux cent trente-trois", "deux cent trente-quatre", "deux cent trente-cinq", "deux cent trente-six", "deux cent trente-sept", "deux cent trente-huit", "deux cent trente-neuf", "deux cent quarante", "deux cent quarante-un", "deux cent quarante-deux", "deux cent quarante-trois", "deux cent quarante-quatre", "deux cent quarante-cinq", "deux cent quarante-six", "deux cent quarante-sept", "deux cent quarante-huit", "deux cent quarante-neuf", "deux cent cinquante", "deux cent cinquante-un", "deux cent cinquante-deux", "deux cent cinquante-trois", "deux cent cinquante-quatre", "deux cent cinquante-cinq", "deux cent cinquante-six", "deux cent cinquante-sept", "deux cent cinquante-huit", "deux cent cinquante-neuf", "deux cent soixante", "deux cent soixante-un", "deux cent soixante-deux", "deux cent soixante-trois", "deux cent soixante-quatre", "deux cent soixante-cinq", "deux cent soixante-six", "deux cent soixante-sept", "deux cent soixante-huit", "deux cent soixante-neuf", "deux cent soixante", "deux cent soixante-onze", "deux cent soixante-douze", "deux cent soixante-treize", "deux cent soixante-quatorze", "deux cent soixante-quinze", "deux cent soixante-seize", "deux cent soixante-dix-sept", "deux cent soixante-dix-huit", "deux cent soixante-dix-neuf", "deux cent quatre-vingts", "deux cent quatre-vingts-un", "deux cent quatre-vingts-deux", "deux cent quatre-vingts-trois", "deux cent quatre-vingts-quatre", "deux cent quatre-vingts-cinq", "deux cent quatre-vingts-six", "deux cent quatre-vingts-sept", "deux cent quatre-vingts-huit", "deux cent quatre-vingts-neuf", "deux cent quatre-vingts", "deux cent quatre-vingts-onze", "deux cent quatre-vingts-douze", "deux cent quatre-vingts-treize", "deux cent quatre-vingts-quatorze", "deux cent quatre-vingts-quinze", "deux cent quatre-vingts-seize", "deux cent quatre-vingts-dix-sept", "deux cent quatre-vingts-dix-huit", "deux cent quatre-vingts-dix-neuf", "trois cent", "trois cent un", "trois cent deux", "trois cent trois", "trois cent quatre", "trois cent cinq", "trois cent six", "trois cent sept", "trois cent huit", "trois cent neuf", "trois cent dix", "trois cent onze", "trois cent douze", "trois cent treize", "trois cent quatorze", "trois cent quinze", "trois cent seize", "trois cent dix-sept", "trois cent dix-huit", "trois cent dix-neuf", "trois cent vingt", "trois cent vingt-un", "trois cent vingt-deux", "trois cent vingt-trois", "trois cent vingt-quatre", "trois cent vingt-cinq", "trois cent vingt-six", "trois cent vingt-sept", "trois cent vingt-huit", "trois cent vingt-neuf", "trois cent trente", "trois cent trente-un", "trois cent trente-deux", "trois cent trente-trois", "trois cent trente-quatre", "trois cent trente-cinq", "trois cent trente-six", "trois cent trente-sept", "trois cent trente-huit", "trois cent trente-neuf", "trois cent quarante", "trois cent quarante-un", "trois cent quarante-deux", "trois cent quarante-trois", "trois cent quarante-quatre", "trois cent quarante-cinq", "trois cent quarante-six", "trois cent quarante-sept", "trois cent quarante-huit", "trois cent quarante-neuf", "trois cent cinquante", "trois cent cinquante-un", "trois cent cinquante-deux", "trois cent cinquante-trois", "trois cent cinquante-quatre", "trois cent cinquante-cinq", "trois cent cinquante-six", "trois cent cinquante-sept", "trois cent cinquante-huit", "trois cent cinquante-neuf", "trois cent soixante", "trois cent soixante-un", "trois cent soixante-deux", "trois cent soixante-trois", "trois cent soixante-quatre", "trois cent soixante-cinq", "trois cent soixante-six", "trois cent soixante-sept", "trois cent soixante-huit", "trois cent soixante-neuf", "trois cent soixante", "trois cent soixante-onze", "trois cent soixante-douze", "trois cent soixante-treize", "trois cent soixante-quatorze", "trois cent soixante-quinze", "trois cent soixante-seize", "trois cent soixante-dix-sept", "trois cent soixante-dix-huit", "trois cent soixante-dix-neuf", "trois cent quatre-vingts", "trois cent quatre-vingts-un", "trois cent quatre-vingts-deux", "trois cent quatre-vingts-trois", "trois cent quatre-vingts-quatre", "trois cent quatre-vingts-cinq", "trois cent quatre-vingts-six", "trois cent quatre-vingts-sept", "trois cent quatre-vingts-huit", "trois cent quatre-vingts-neuf", "trois cent quatre-vingts", "trois cent quatre-vingts-onze", "trois cent quatre-vingts-douze", "trois cent quatre-vingts-treize", "trois cent quatre-vingts-quatorze", "trois cent quatre-vingts-quinze", "trois cent quatre-vingts-seize", "trois cent quatre-vingts-dix-sept", "trois cent quatre-vingts-dix-huit", "trois cent quatre-vingts-dix-neuf", "quatre cent", "quatre cent un", "quatre cent deux", "quatre cent trois", "quatre cent quatre", "quatre cent cinq", "quatre cent six", "quatre cent sept", "quatre cent huit", "quatre cent neuf", "quatre cent dix", "quatre cent onze", "quatre cent douze", "quatre cent treize", "quatre cent quatorze", "quatre cent quinze", "quatre cent seize", "quatre cent dix-sept", "quatre cent dix-huit", "quatre cent dix-neuf", "quatre cent vingt", "quatre cent vingt-un", "quatre cent vingt-deux", "quatre cent vingt-trois", "quatre cent vingt-quatre", "quatre cent vingt-cinq", "quatre cent vingt-six", "quatre cent vingt-sept", "quatre cent vingt-huit", "quatre cent vingt-neuf", "quatre cent trente", "quatre cent trente-un", "quatre cent trente-deux", "quatre cent trente-trois", "quatre cent trente-quatre", "quatre cent trente-cinq", "quatre cent trente-six", "quatre cent trente-sept", "quatre cent trente-huit", "quatre cent trente-neuf", "quatre cent quarante", "quatre cent quarante-un", "quatre cent quarante-deux", "quatre cent quarante-trois", "quatre cent quarante-quatre", "quatre cent quarante-cinq", "quatre cent quarante-six", "quatre cent quarante-sept", "quatre cent quarante-huit", "quatre cent quarante-neuf", "quatre cent cinquante", "quatre cent cinquante-un", "quatre cent cinquante-deux", "quatre cent cinquante-trois", "quatre cent cinquante-quatre", "quatre cent cinquante-cinq", "quatre cent cinquante-six", "quatre cent cinquante-sept", "quatre cent cinquante-huit", "quatre cent cinquante-neuf", "quatre cent soixante", "quatre cent soixante-un", "quatre cent soixante-deux", "quatre cent soixante-trois", "quatre cent soixante-quatre", "quatre cent soixante-cinq", "quatre cent soixante-six", "quatre cent soixante-sept", "quatre cent soixante-huit", "quatre cent soixante-neuf", "quatre cent soixante", "quatre cent soixante-onze", "quatre cent soixante-douze", "quatre cent soixante-treize", "quatre cent soixante-quatorze", "quatre cent soixante-quinze", "quatre cent soixante-seize", "quatre cent soixante-dix-sept", "quatre cent soixante-dix-huit", "quatre cent soixante-dix-neuf", "quatre cent quatre-vingts", "quatre cent quatre-vingts-un", "quatre cent quatre-vingts-deux", "quatre cent quatre-vingts-trois", "quatre cent quatre-vingts-quatre", "quatre cent quatre-vingts-cinq", "quatre cent quatre-vingts-six", "quatre cent quatre-vingts-sept", "quatre cent quatre-vingts-huit", "quatre cent quatre-vingts-neuf", "quatre cent quatre-vingts", "quatre cent quatre-vingts-onze", "quatre cent quatre-vingts-douze", "quatre cent quatre-vingts-treize", "quatre cent quatre-vingts-quatorze", "quatre cent quatre-vingts-quinze", "quatre cent quatre-vingts-seize", "quatre cent quatre-vingts-dix-sept", "quatre cent quatre-vingts-dix-huit", "quatre cent quatre-vingts-dix-neuf", "cinq cent", "cinq cent un", "cinq cent deux", "cinq cent trois", "cinq cent quatre", "cinq cent cinq", "cinq cent six", "cinq cent sept", "cinq cent huit", "cinq cent neuf", "cinq cent dix", "cinq cent onze", "cinq cent douze", "cinq cent treize", "cinq cent quatorze", "cinq cent quinze", "cinq cent seize", "cinq cent dix-sept", "cinq cent dix-huit", "cinq cent dix-neuf", "cinq cent vingt", "cinq cent vingt-un", "cinq cent vingt-deux", "cinq cent vingt-trois", "cinq cent vingt-quatre", "cinq cent vingt-cinq", "cinq cent vingt-six", "cinq cent vingt-sept", "cinq cent vingt-huit", "cinq cent vingt-neuf", "cinq cent trente", "cinq cent trente-un", "cinq cent trente-deux", "cinq cent trente-trois", "cinq cent trente-quatre", "cinq cent trente-cinq", "cinq cent trente-six", "cinq cent trente-sept", "cinq cent trente-huit", "cinq cent trente-neuf", "cinq cent quarante", "cinq cent quarante-un", "cinq cent quarante-deux", "cinq cent quarante-trois", "cinq cent quarante-quatre", "cinq cent quarante-cinq", "cinq cent quarante-six", "cinq cent quarante-sept", "cinq cent quarante-huit", "cinq cent quarante-neuf", "cinq cent cinquante", "cinq cent cinquante-un", "cinq cent cinquante-deux", "cinq cent cinquante-trois", "cinq cent cinquante-quatre", "cinq cent cinquante-cinq", "cinq cent cinquante-six", "cinq cent cinquante-sept", "cinq cent cinquante-huit", "cinq cent cinquante-neuf", "cinq cent soixante", "cinq cent soixante-un", "cinq cent soixante-deux", "cinq cent soixante-trois", "cinq cent soixante-quatre", "cinq cent soixante-cinq", "cinq cent soixante-six", "cinq cent soixante-sept", "cinq cent soixante-huit", "cinq cent soixante-neuf", "cinq cent soixante", "cinq cent soixante-onze", "cinq cent soixante-douze", "cinq cent soixante-treize", "cinq cent soixante-quatorze", "cinq cent soixante-quinze", "cinq cent soixante-seize", "cinq cent soixante-dix-sept", "cinq cent soixante-dix-huit", "cinq cent soixante-dix-neuf", "cinq cent quatre-vingts", "cinq cent quatre-vingts-un", "cinq cent quatre-vingts-deux", "cinq cent quatre-vingts-trois", "cinq cent quatre-vingts-quatre", "cinq cent quatre-vingts-cinq", "cinq cent quatre-vingts-six", "cinq cent quatre-vingts-sept", "cinq cent quatre-vingts-huit", "cinq cent quatre-vingts-neuf", "cinq cent quatre-vingts", "cinq cent quatre-vingts-onze", "cinq cent quatre-vingts-douze", "cinq cent quatre-vingts-treize", "cinq cent quatre-vingts-quatorze", "cinq cent quatre-vingts-quinze", "cinq cent quatre-vingts-seize", "cinq cent quatre-vingts-dix-sept", "cinq cent quatre-vingts-dix-huit", "cinq cent quatre-vingts-dix-neuf", "six cent", "six cent un", "six cent deux", "six cent trois", "six cent quatre", "six cent cinq", "six cent six", "six cent sept", "six cent huit", "six cent neuf", "six cent dix", "six cent onze", "six cent douze", "six cent treize", "six cent quatorze", "six cent quinze", "six cent seize", "six cent dix-sept", "six cent dix-huit", "six cent dix-neuf", "six cent vingt", "six cent vingt-un", "six cent vingt-deux", "six cent vingt-trois", "six cent vingt-quatre", "six cent vingt-cinq", "six cent vingt-six", "six cent vingt-sept", "six cent vingt-huit", "six cent vingt-neuf", "six cent trente", "six cent trente-un", "six cent trente-deux", "six cent trente-trois", "six cent trente-quatre", "six cent trente-cinq", "six cent trente-six", "six cent trente-sept", "six cent trente-huit", "six cent trente-neuf", "six cent quarante", "six cent quarante-un", "six cent quarante-deux", "six cent quarante-trois", "six cent quarante-quatre", "six cent quarante-cinq", "six cent quarante-six", "six cent quarante-sept", "six cent quarante-huit", "six cent quarante-neuf", "six cent cinquante", "six cent cinquante-un", "six cent cinquante-deux", "six cent cinquante-trois", "six cent cinquante-quatre", "six cent cinquante-cinq", "six cent cinquante-six", "six cent cinquante-sept", "six cent cinquante-huit", "six cent cinquante-neuf", "six cent soixante", "six cent soixante-un", "six cent soixante-deux", "six cent soixante-trois", "six cent soixante-quatre", "six cent soixante-cinq", "six cent soixante-six", "six cent soixante-sept", "six cent soixante-huit", "six cent soixante-neuf", "six cent soixante", "six cent soixante-onze", "six cent soixante-douze", "six cent soixante-treize", "six cent soixante-quatorze", "six cent soixante-quinze", "six cent soixante-seize", "six cent soixante-dix-sept", "six cent soixante-dix-huit", "six cent soixante-dix-neuf", "six cent quatre-vingts", "six cent quatre-vingts-un", "six cent quatre-vingts-deux", "six cent quatre-vingts-trois", "six cent quatre-vingts-quatre", "six cent quatre-vingts-cinq", "six cent quatre-vingts-six", "six cent quatre-vingts-sept", "six cent quatre-vingts-huit", "six cent quatre-vingts-neuf", "six cent quatre-vingts", "six cent quatre-vingts-onze", "six cent quatre-vingts-douze", "six cent quatre-vingts-treize", "six cent quatre-vingts-quatorze", "six cent quatre-vingts-quinze", "six cent quatre-vingts-seize", "six cent quatre-vingts-dix-sept", "six cent quatre-vingts-dix-huit", "six cent quatre-vingts-dix-neuf", "sept cent", "sept cent un", "sept cent deux", "sept cent trois", "sept cent quatre", "sept cent cinq", "sept cent six", "sept cent sept", "sept cent huit", "sept cent neuf", "sept cent dix", "sept cent onze", "sept cent douze", "sept cent treize", "sept cent quatorze", "sept cent quinze", "sept cent seize", "sept cent dix-sept", "sept cent dix-huit", "sept cent dix-neuf", "sept cent vingt", "sept cent vingt-un", "sept cent vingt-deux", "sept cent vingt-trois", "sept cent vingt-quatre", "sept cent vingt-cinq", "sept cent vingt-six", "sept cent vingt-sept", "sept cent vingt-huit", "sept cent vingt-neuf", "sept cent trente", "sept cent trente-un", "sept cent trente-deux", "sept cent trente-trois", "sept cent trente-quatre", "sept cent trente-cinq", "sept cent trente-six", "sept cent trente-sept", "sept cent trente-huit", "sept cent trente-neuf", "sept cent quarante", "sept cent quarante-un", "sept cent quarante-deux", "sept cent quarante-trois", "sept cent quarante-quatre", "sept cent quarante-cinq", "sept cent quarante-six", "sept cent quarante-sept", "sept cent quarante-huit", "sept cent quarante-neuf", "sept cent cinquante", "sept cent cinquante-un", "sept cent cinquante-deux", "sept cent cinquante-trois", "sept cent cinquante-quatre", "sept cent cinquante-cinq", "sept cent cinquante-six", "sept cent cinquante-sept", "sept cent cinquante-huit", "sept cent cinquante-neuf", "sept cent soixante", "sept cent soixante-un", "sept cent soixante-deux", "sept cent soixante-trois", "sept cent soixante-quatre", "sept cent soixante-cinq", "sept cent soixante-six", "sept cent soixante-sept", "sept cent soixante-huit", "sept cent soixante-neuf", "sept cent soixante", "sept cent soixante-onze", "sept cent soixante-douze", "sept cent soixante-treize", "sept cent soixante-quatorze", "sept cent soixante-quinze", "sept cent soixante-seize", "sept cent soixante-dix-sept", "sept cent soixante-dix-huit", "sept cent soixante-dix-neuf", "sept cent quatre-vingts", "sept cent quatre-vingts-un", "sept cent quatre-vingts-deux", "sept cent quatre-vingts-trois", "sept cent quatre-vingts-quatre", "sept cent quatre-vingts-cinq", "sept cent quatre-vingts-six", "sept cent quatre-vingts-sept", "sept cent quatre-vingts-huit", "sept cent quatre-vingts-neuf", "sept cent quatre-vingts", "sept cent quatre-vingts-onze", "sept cent quatre-vingts-douze", "sept cent quatre-vingts-treize", "sept cent quatre-vingts-quatorze", "sept cent quatre-vingts-quinze", "sept cent quatre-vingts-seize", "sept cent quatre-vingts-dix-sept", "sept cent quatre-vingts-dix-huit", "sept cent quatre-vingts-dix-neuf", "huit cent", "huit cent un", "huit cent deux", "huit cent trois", "huit cent quatre", "huit cent cinq", "huit cent six", "huit cent sept", "huit cent huit", "huit cent neuf", "huit cent dix", "huit cent onze", "huit cent douze", "huit cent treize", "huit cent quatorze", "huit cent quinze", "huit cent seize", "huit cent dix-sept", "huit cent dix-huit", "huit cent dix-neuf", "huit cent vingt", "huit cent vingt-un", "huit cent vingt-deux", "huit cent vingt-trois", "huit cent vingt-quatre", "huit cent vingt-cinq", "huit cent vingt-six", "huit cent vingt-sept", "huit cent vingt-huit", "huit cent vingt-neuf", "huit cent trente", "huit cent trente-un", "huit cent trente-deux", "huit cent trente-trois", "huit cent trente-quatre", "huit cent trente-cinq", "huit cent trente-six", "huit cent trente-sept", "huit cent trente-huit", "huit cent trente-neuf", "huit cent quarante", "huit cent quarante-un", "huit cent quarante-deux", "huit cent quarante-trois", "huit cent quarante-quatre", "huit cent quarante-cinq", "huit cent quarante-six", "huit cent quarante-sept", "huit cent quarante-huit", "huit cent quarante-neuf", "huit cent cinquante", "huit cent cinquante-un", "huit cent cinquante-deux", "huit cent cinquante-trois", "huit cent cinquante-quatre", "huit cent cinquante-cinq", "huit cent cinquante-six", "huit cent cinquante-sept", "huit cent cinquante-huit", "huit cent cinquante-neuf", "huit cent soixante", "huit cent soixante-un", "huit cent soixante-deux", "huit cent soixante-trois", "huit cent soixante-quatre", "huit cent soixante-cinq", "huit cent soixante-six", "huit cent soixante-sept", "huit cent soixante-huit", "huit cent soixante-neuf", "huit cent soixante", "huit cent soixante-onze", "huit cent soixante-douze", "huit cent soixante-treize", "huit cent soixante-quatorze", "huit cent soixante-quinze", "huit cent soixante-seize", "huit cent soixante-dix-sept", "huit cent soixante-dix-huit", "huit cent soixante-dix-neuf", "huit cent quatre-vingts", "huit cent quatre-vingts-un", "huit cent quatre-vingts-deux", "huit cent quatre-vingts-trois", "huit cent quatre-vingts-quatre", "huit cent quatre-vingts-cinq", "huit cent quatre-vingts-six", "huit cent quatre-vingts-sept", "huit cent quatre-vingts-huit", "huit cent quatre-vingts-neuf", "huit cent quatre-vingts", "huit cent quatre-vingts-onze", "huit cent quatre-vingts-douze", "huit cent quatre-vingts-treize", "huit cent quatre-vingts-quatorze", "huit cent quatre-vingts-quinze", "huit cent quatre-vingts-seize", "huit cent quatre-vingts-dix-sept", "huit cent quatre-vingts-dix-huit", "huit cent quatre-vingts-dix-neuf", "neuf cent", "neuf cent un", "neuf cent deux", "neuf cent trois", "neuf cent quatre", "neuf cent cinq", "neuf cent six", "neuf cent sept", "neuf cent huit", "neuf cent neuf", "neuf cent dix", "neuf cent onze", "neuf cent douze", "neuf cent treize", "neuf cent quatorze", "neuf cent quinze", "neuf cent seize", "neuf cent dix-sept", "neuf cent dix-huit", "neuf cent dix-neuf", "neuf cent vingt", "neuf cent vingt-un", "neuf cent vingt-deux", "neuf cent vingt-trois", "neuf cent vingt-quatre", "neuf cent vingt-cinq", "neuf cent vingt-six", "neuf cent vingt-sept", "neuf cent vingt-huit", "neuf cent vingt-neuf", "neuf cent trente", "neuf cent trente-un", "neuf cent trente-deux", "neuf cent trente-trois", "neuf cent trente-quatre", "neuf cent trente-cinq", "neuf cent trente-six", "neuf cent trente-sept", "neuf cent trente-huit", "neuf cent trente-neuf", "neuf cent quarante", "neuf cent quarante-un", "neuf cent quarante-deux", "neuf cent quarante-trois", "neuf cent quarante-quatre", "neuf cent quarante-cinq", "neuf cent quarante-six", "neuf cent quarante-sept", "neuf cent quarante-huit", "neuf cent quarante-neuf", "neuf cent cinquante", "neuf cent cinquante-un", "neuf cent cinquante-deux", "neuf cent cinquante-trois", "neuf cent cinquante-quatre", "neuf cent cinquante-cinq", "neuf cent cinquante-six", "neuf cent cinquante-sept", "neuf cent cinquante-huit", "neuf cent cinquante-neuf", "neuf cent soixante", "neuf cent soixante-un", "neuf cent soixante-deux", "neuf cent soixante-trois", "neuf cent soixante-quatre", "neuf cent soixante-cinq", "neuf cent soixante-six", "neuf cent soixante-sept", "neuf cent soixante-huit", "neuf cent soixante-neuf", "neuf cent soixante", "neuf cent soixante-onze", "neuf cent soixante-douze", "neuf cent soixante-treize", "neuf cent soixante-quatorze", "neuf cent soixante-quinze", "neuf cent soixante-seize", "neuf cent soixante-dix-sept", "neuf cent soixante-dix-huit", "neuf cent soixante-dix-neuf", "neuf cent quatre-vingts", "neuf cent quatre-vingts-un", "neuf cent quatre-vingts-deux", "neuf cent quatre-vingts-trois", "neuf cent quatre-vingts-quatre", "neuf cent quatre-vingts-cinq", "neuf cent quatre-vingts-six", "neuf cent quatre-vingts-sept", "neuf cent quatre-vingts-huit", "neuf cent quatre-vingts-neuf", "neuf cent quatre-vingts", "neuf cent quatre-vingts-onze", "neuf cent quatre-vingts-douze", "neuf cent quatre-vingts-treize", "neuf cent quatre-vingts-quatorze", "neuf cent quatre-vingts-quinze", "neuf cent quatre-vingts-seize", "neuf cent quatre-vingts-dix-sept", "neuf cent quatre-vingts-dix-huit", "neuf cent quatre-vingts-dix-neuf"};


// listes d'unités et de leurs valeurs numériques et leur nombres, pour faciliter l'extension future.
// Pour ajouter une unité, il faut ajouter son nom dans la liste "noms_unites"
// et sa valeur numérique dans la liste "diviseurs_unites". Assurez-vous que les deux
// ont le même ordre dans les listes respectives.
// N'oubliez pas de mettre à jour "NOMBRE_UNITES" pour qu'il corresponde à la longueur des listes.
// Remarque : le pas entre les unités doit être de 1000.
const long long diviseurs_unites[] = {1000000000LL, 1000000LL, 1000LL, 1LL};
const char *noms_unites[] = {"milliard", "million", "mille", ""};
const int NOMBRE_UNITES = 4;

// Codes d'erreur et limites
#define AUCUNE_ERREUR 0
#define ERREUR_LONGUEUR 1
#define ERREUR_NON_NUMERIQUE 2
#define ERREUR_FORMAT_DECIMAL 3
#define CHIFFRES_MAX (NOMBRE_UNITES*3) // Le nombre maximal de chiffres dans le nombre que l'utilisateur peut entrer correspond au nombre d'unités.
#define DECIMALES_MAX 9 // Le nombre maximal de chiffres après la virgule


// Déclarations de fonctions.

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

int valider_entree(const char *entree) {
    int i = 0;
    int point_trouve = 0;
    int chiffres_avant_point = 0;
    int chiffres_apres_point = 0;

    // Vérification du signe
    if (entree[0] == '+' || entree[0] == '-') {
        i = 1;
    }

    // Vérification de chaîne vide
    if (entree[i] == '\0') return ERREUR_NON_NUMERIQUE;

    // Validation des caractères
    for (; entree[i] != '\0'; i++) {
        if (entree[i] == '.' || entree[i] == ',') {
            if (point_trouve) {
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
