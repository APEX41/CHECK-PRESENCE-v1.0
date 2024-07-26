#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define STUDENT_NUMBER 75
enum use
{
    YES,
    NO,
    PERSONAL,
    ABSENT
};

char **allocation2D();
char *timeRightNow();
typedef enum use use;
struct StudentMachine{
    int number;
    char name[255];
    char firstName[255];
    char *temp;
    use machine;
};
typedef struct StudentMachine StudentMachine;
typedef struct name name;

int search();               //Recherche par nom
int verify(int lire);      //verify la lecture de donnée
int findNumber();           //Rechercher par number
int second_menu();

void writeFile(StudentMachine *eleve,int number); //write de donnée dans le fichier
void displayAndChoice(StudentMachine *personne); //Affiche l'interface et recoit le choix de l'Etudiant
void printResult();       //Affichage des resultat
void printAllList(StudentMachine *student);      //Afficher tous la liste des etudiant
void checkPC();             //Fonction qui relie chaque fonction
void APEX();
void confirmation();
void free2D(char **array);

use traitment(int number);  //use des machine 
StudentMachine* data();          //Prise des donnée dans le fichier
FILE *ouvrir(char *fileName,char *mode);    //Ouverture du fichier