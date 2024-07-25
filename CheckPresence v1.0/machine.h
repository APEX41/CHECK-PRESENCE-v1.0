#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define STUDENT_NUMBER 75
enum utilisation
{
    OUI,
    NON,
    PERSONNEL,
    ABSENT
};
void confirmation();
void Free2D(char **array);
char **Allouer2D();
char *time_en_ce_moment();
typedef enum utilisation utilisation;
struct MachineEtudiant{
    int numero;
    char nom[255];
    char prenom[255];
    char *Temp;
    utilisation machine;
};
int second_menu();
typedef struct MachineEtudiant MachineEtudiant;
void APEX();
typedef struct name name;
int search();               //Recherche par nom
int verifie(int lire);      //Verifie la lecture de donnée
int Findnumero();           //Rechercher par numero

void ecriture(MachineEtudiant *eleve,int numero); //Ecriture de donnée dans le fichier
void displayAndChoice(MachineEtudiant *personne); //Affiche l'interface et recoit le choix de l'Etudiant
void printresultat();       //Affichage des resultat
void PrintAllList(MachineEtudiant *student);      //Afficher tous la liste des etudiant
void checkPC();             //Fonction qui relie chaque fonction

utilisation traitment(int numero);  //Utilisation des machine 
MachineEtudiant* donnee();          //Prise des donnée dans le fichier
FILE *ouvrir(char *nom_fichier,char *mode);    //Ouverture du fichier