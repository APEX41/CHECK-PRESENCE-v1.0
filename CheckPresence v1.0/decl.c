#include "machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

void checkPC()
{
    MachineEtudiant *personne;
    personne = donnee();
	Try:
    	displayAndChoice(personne);
	goto Try;
}
void PrintAllList(MachineEtudiant *student)
{
	int choice;
	char line[200];
	char find_name[200];
	FILE *file = ouvrir(".tmp.csv","r");
	choice = second_menu();
	printf("choice = %d\n",choice);
	switch (choice)
	{
	case 1:
		strcpy(find_name,"ABSENT");
		break;
	case 2:
		strcpy(find_name,"OUI");
		break;
	case 3:
		strcpy(find_name,"PERSONNEL");
		break;
	case 4:
		displayAndChoice(student);
	default:
		break;
	}
	while (fgets(line,200,file) != 0)
	{
		if(strstr(line,find_name) != NULL)
			puts(line);
	}
	fclose(file);
	displayAndChoice(student);
}
char *time_en_ce_moment()
{
    time_t temps;
    struct tm *temps_info;
    char *temp_actuel = malloc(9 * sizeof(char)); 
    if (temp_actuel == NULL)
	{
        perror("Erreur d'allocation de memoire");
        exit(EXIT_FAILURE);
    }
    // Obtenir le temps actuel
    time(&temps);
    temps_info = localtime(&temps);
    strftime(temp_actuel, 9, "%H:%M:%S", temps_info);
    return temp_actuel;
}
MachineEtudiant* donnee()
{
    int i = 0;
	int j;
    char **NOM = Allouer2D();
    char **PRENOM = Allouer2D();
    char **numero = Allouer2D();
    MachineEtudiant *l1;
    l1 = (MachineEtudiant *)malloc(sizeof(MachineEtudiant) * STUDENT_NUMBER);
    if (l1 == NULL)
	{
        printf("Erreur d'allocation du tableau\n");
        exit(-1);
    }
    FILE *file = fopen("source.csv", "r");
    if (file == NULL)
	{
        printf("Erreur d'ouverture de fichier\n");
        exit(-1);
    }
    int p=0;
    char line[2000];
	int indice = 0;
    while (fgets(line, sizeof(line), file) && i < STUDENT_NUMBER)
	{
        char *token;
        int field = 0;
        token = strtok(line, " ");
        while (token != NULL)
		{
            switch (field)
			{
                case 0:
                    strcpy(numero[i],token);
                    break;
                case 1:
                    strcpy(NOM[i],token);
                    break;
                case 2:
					strcpy(PRENOM[i],token);
					while((token = strtok(NULL, " ")) && token != NULL)
					{
						strcat(PRENOM[i]," ");
						strcat(PRENOM[i],token);
					}
					for(p = 0;p < strlen(PRENOM[i]);p++)
						if(PRENOM[i][p] == '\n')
						{
							PRENOM[i][p] = '\0';
						}
                default:
                    break;
            }
            field++;
            token = strtok(NULL, " ");
        }
        l1[i].numero = atoi(numero[i]);
        strcpy(l1[i].nom, NOM[i]);
        strcpy(l1[i].prenom, PRENOM[i]);
        l1[i].machine = ABSENT; 
        i++;
    }
    fclose(file);
    Free2D(NOM);
    Free2D(PRENOM);
    Free2D(numero);
    return l1;
}
void sent()
{	
	int choice;
	printf(" ________________________\n");
	printf("/   Envoyer maintenant   \\\n");
	printf("\\_______________________/\n");
	system("chmod +x Send.bash");
	system("./Send.bash");
}
char **Allouer2D()
{
	int i;
	char **A = (char **)malloc(sizeof(char*)*STUDENT_NUMBER);
	for(i = 0;i < STUDENT_NUMBER ;i++)
	{
		A[i] = (char *)malloc(sizeof(char)*255);
	}
	return A;
}
void Free2D(char **array)
{
	int i;
    for (i = 0; i < STUDENT_NUMBER; i++)
	{
        free(array[i]);
    }
    free(array);
}
int Findnumero(MachineEtudiant *Etudiant)
{
    int numero;
    int lire;
	Retry2:
	printf("Enter le numero : ");
    lire = scanf("%d",&numero);
	if(lire != 1)
		numero = verifie(lire);

    if(numero > STUDENT_NUMBER || numero <= 0)
    {
        printf("L'Etudiant n'est pas dans la liste\n");
		printf("Veulliez reessayer\n");
		goto Retry2;
    }
	printresultat();
	printf("|%6d| %-30s |%-35s|\n",Etudiant[numero - 1].numero,Etudiant[numero -1].nom, Etudiant[numero -1].prenom);
	printf("|___________________________________________________________________________|\n");
    return numero - 1;
}
void menuprint()
{
    printf(" ____________________________________                _____________________________________\n");
    printf("/ 1 \\        NAME'S SEARCH           \\              / 2 \\      NUMBER'S SEARCH            \\\n");
    printf("\\___/________________________________/              \\___/_________________________________/\n");
    printf(" ____________________________________                _____________________________________\n");
    printf("/ 3 \\     LIST OF ALL STUDENT        \\              / 4 \\      QUIT THIS PROGRAMM         \\\n");
    printf("\\___/________________________________/              \\___/_________________________________/\n");
    printf(" ____________________________________                _____________________________________\n");
    printf("/ 5 \\ SENT THE CHECK'S FILE ON EMAIL \\              / 6 \\      APEX TEAM                 \\\n");
    printf("\\___/________________________________/              \\___/_________________________________/\n");
    printf("\t\t\t ________________________________________\n");
    printf("\t\t\t/ 7 \\ CONFIRM END OF CHECKING FOR TODAY \\\n");
    printf("\t\t\t\\___/___________________________________/ \n");
}

void displayAndChoice(MachineEtudiant *personne)
{
    int choice;
    int numero;
	int lire;
	menuprint();
	do{
		printf("\t Votre choix : ");
		lire = scanf("%d",&choice);
		if(lire != 1)
			choice = verifie(lire);
		if(choice == 1)
		{
			numero = search(personne);
			ecriture(personne,numero);
		}
		else if(choice == 2)
		{
			numero = Findnumero(personne);
			ecriture(personne,numero);
		}
		else if(choice == 3)
		{
			PrintAllList(personne);
		}
		else if(choice == 4)
		{
			exit(EXIT_SUCCESS);
		}
		else if(choice == 5)
		{
			sent();
		}
		else if(choice == 6)
		{
			APEX();
		}
		else if(choice == 7)
		{
			confirmation();
		}
	}while(choice > 7 || choice <= 0);
}
int verifie(int lire)
{
	int c=0;
	int choice;
	while(!lire)
	{
		if(c == (getchar() != '\n') && c != EOF)
		{
			printf("\tRetry your choice : ");
			lire = scanf("%d", &choice);
		}
	}
	return choice;
}
void printresultat()
{
	printf("_____________________________________________________________________________\n");
	printf("|__________Resultat Trouvee :_______________________________________________|\n");
	printf("|Numero|NOM_____________________________|PRENOM_____________________________|\n");
	printf("|___________________________________________________________________________|\n");
}

int search(MachineEtudiant* student)
{
	char Nom[200];
	int i ;
	int num;
	int lire;
	int indicateur = 0;
	int nombretrouvee = 0;
	char Nomtransforme[200];
	char Prenomtransforme[200];
	char verifieNom[200];
	char verifiePrenom[200];
	int j;
	int tousnumero[STUDENT_NUMBER];
	printf("Enter the ------------------name or firstName you want to search: ");
	getchar();
	fgets(Nom, sizeof(Nom), stdin);
	Nom[strcspn(Nom, "\n")] = '\0';
	printresultat();
	for (j = 0; j < strlen(Nom); j++)
	{
		Nomtransforme[j] = tolower(Nom[j]);
		Prenomtransforme[j] = tolower(Nom[j]);
	}
	Nomtransforme[j] = '\0';
	Prenomtransforme[j] = '\0';
	
	for (i = 0 ; i< STUDENT_NUMBER; i++)
	{
	    strcpy(verifieNom, student[i].nom);
        strcpy(verifiePrenom, student[i].prenom);
		for (j = 0; j < strlen(student[i].nom); j++)
		{
			verifieNom[j] = tolower(student[i].nom[j]);
		}
		for (j = 0; j < strlen(student[i].prenom); j++)
		{
			verifiePrenom[j] = tolower(student[i].prenom[j]);
		}
		
		if (strcmp(verifieNom,Nomtransforme) == 0 ||strcmp(verifiePrenom,Prenomtransforme) == 0)
		{
			printf("|%6d| %-30s |%-35s|\n", student[i].numero, student[i].nom, student[i].prenom);
			nombretrouvee++;
		}
        else
        {
            char tempNom[200];
            char tempPrenom[200];
            strcpy(tempNom, Nomtransforme);
            strcpy(tempPrenom, Prenomtransforme);
            char *temp = strtok(tempNom, " ,\t");
            char *temp2 = strtok(tempPrenom, " ,\t");
            while (temp != NULL && temp2 != NULL)
            {
                char *occ = strstr(verifieNom, temp);
                char *occ2 = strstr(verifiePrenom, temp2);
                if (occ || occ2)
                {
                    printf("|%6d| %-30s |%-35s|\n", student[i].numero, student[i].nom, student[i].prenom);
                    tousnumero[nombretrouvee] = i + 1;
                    occ2 = NULL;
                    nombretrouvee++;
                }
                temp = strtok(NULL, " ,\t");
                temp2 = strtok(NULL, " ,\t");
            }
        }
	}
	printf("|___________________________________________________________________________|\n");
	if (nombretrouvee == 0)
	{
		printf("\n\n_____________________________________________________________________________\n");
		printf("|\t\tl'etudiant %s n'est pas dans la liste     \t\t|\n", Nom);
		printf("|____________________________________________________________________________|\n");
		exit(-1);
	}
	Retry :
    printf("Entrer la numero : ");
	lire = scanf("%d",&num);
	if(lire != 1)
		num = verifie(lire);
	for(i = 0;i<nombretrouvee;i++)
	{
		if(num == tousnumero[i])
		{
			indicateur = 1;
			break;
		}
	}
	if(indicateur == 0)
	{
		printf("This student is not on the result !\n");
		printf("Please retry your choice\n");
		goto Retry;
	}
	return (num - 1);
}
int second_menu()
{
	int choice;
	int lire;
	printf("\t=================================================================================\n");
	printf("\t=1                       Set the list of student absent                         =\n");
	printf("\t=================================================================================\n");
	printf("\t=================================================================================\n");
	printf("\t=2                Set the list of student who use computer                      =\n");
	printf("\t=================================================================================\n");
	printf("\t=================================================================================\n");
	printf("\t=3             Set the list of student who use a personnal computer             =\n");
	printf("\t=================================================================================\n");
	printf("\t=================================================================================\n");
	printf("\t=5                        Quit the spetial menu                                  =\n");
	printf("\t=================================================================================\n");
	printf("\n What is your choice:");
	lire = scanf("%d",&choice);
	if(lire != 1)
	{
		choice = verifie(lire);
	}
	return (choice);
}
utilisation traitment(int numero)
{
    char choix[255];
    printf("OUI\tNON\tPERSONNEL : ");
    scanf("%s",choix);
    if(strcmp(choix,"OUI") == 0)
	{
        return OUI;
    }
	if(strcmp(choix,"NON") == 0)
	{
        return NON;
    }
    if(strcmp(choix,"ABSENT") == 0)
	{
        return ABSENT;
    }
    if(strcmp(choix,"PERSONNEL") == 0)
	{
        return PERSONNEL;
    }
    return ABSENT;
}

FILE *ouvrir(char *nom_fichier, char *mode)
{
	FILE *fichier = NULL;
	fichier = fopen(nom_fichier,mode);
	if(fichier == NULL)
	{
		printf("Erreur d'ouverture\n");
		exit(0);
	}
	return (fichier);
}
void ecriture(MachineEtudiant *student,int num)
{
	FILE *fichier = NULL;
	char option[20];
	char ancienOption[20];
	int i;
	fichier = ouvrir(".tmp.html","w+");
	utilisation util = traitment(student[num].numero);
	student[num].machine = util;
	switch(util)
	{
		case (OUI):
			strcpy(option, "OUI");
			break;
		case (NON):
			strcpy(option, "NON");
			break;
		case (PERSONNEL):
			strcpy(option, "PC_PERSONNEL");
			break;
		case (ABSENT):
			strcpy(option, "ABSENT");
			break;
	}
	fprintf(fichier, "<HTML>\n");
	fprintf(fichier, "\t<HEAD>\n");
	fprintf(fichier, "\t\t<TITLE>");
	fprintf(fichier, "APEX TEAM ");
	fprintf(fichier, "</TITLE>\n");
	fprintf(fichier, "\t</HEAD>\n");
	fprintf(fichier, "\t<BODY  background=\"apex.jpeg\">\n");
	student[num].Temp = time_en_ce_moment();
	fprintf(fichier, "\t<CENTER>\n");
	fprintf(fichier, "\t\t\t<FONT COLOR=\"#FFFFFF\"><b>=====================> %s <======================</b></FONT>\n", __DATE__);
	fprintf(fichier, "\t\t<TABLe bgColor=\"#333333\" border=\"4\" bordercolor=\"#8218BC\">\n");
	for(i = 0;i<STUDENT_NUMBER;i++)
	{
		if(i == num)
			fprintf(fichier,  "<TR>\n\t<TD><FONT COLOR=\"red\">%2d</FONT></TD>\n<TD><FONT COLOR=\"yellow\"><b>%-30s</b></FONT></TD>\n<TD><FONT COLOR=\"CYAN\">%-30s </FONT></TD>\n<FONT COLOR=\"CYAN\"><TD>%-20s </TD></FONT>\n<FONT COLOR=\"#F3BB46\"><TD>%-20s </TD></FONT>\n<TD><IMG src=\"%s.png\" height=50 width=50></TD>\n</TR>\n", student[i].numero, student[i].nom, student[i].prenom, __DATE__,time_en_ce_moment(),option);
		else{
			switch(student[i].machine)
			{
				case (OUI):
					strcpy(ancienOption, "OUI");
					break;
				case (NON):
					strcpy(ancienOption, "NON");
					break;
				case (PERSONNEL):
					strcpy(ancienOption, "PC_PERSONNEL");
					break;
				case (ABSENT):
					strcpy(ancienOption, "ABSENT");
					break;
			}
			fprintf(fichier,  "<TR>\n\t<TD><FONT COLOR=\"red\">%2d</FONT></TD>\n<TD><FONT COLOR=\"yellow\"><b>%-30s</b></FONT></TD>\n<TD><FONT COLOR=\"CYAN\">%-30s </FONT></TD>\n<FONT COLOR=\"CYAN\"><TD>%-20s </TD></FONT>\n<FONT COLOR=\"#F3BB46\"><TD>%-20s </TD></FONT>\n<TD><IMG src=\"%s.png\" height=50 width=50></TD>\n</TR>\n", student[i].numero, student[i].nom, student[i].prenom, __DATE__,time_en_ce_moment(),ancienOption);
		}
	}
	fprintf(fichier, "\t\t<TABLe>\n");
	fprintf(fichier, "\t</CENTER>\n");
	fprintf(fichier, "Dernier modification :%s\n\t\t%s\n", __DATE__,__TIME__);
	fprintf(fichier, "\t</BODY>\n");
	fprintf(fichier, "</HTML>\n");
	fclose(fichier);
}
void confirmation()
{
	int i;
	char linetmp[300];
	FILE *tmp = ouvrir(".tmp.html","a+");
	FILE *file = ouvrir("check.html","a+");
	for(i = 0;i < STUDENT_NUMBER*8+14;i++)
	{
		fgets(linetmp,299,tmp);
		//printf("%s\n",linetmp);
		fputs(linetmp,file);
	}
	fclose(tmp);
	fclose(file);
	exit(1);
}

void APEX()
{
	printf("RAKOTONDRAIBE Mihasintsoa Hosea\n");
	printf("RAMANDIAMANANA Iavonirina Ambinintsoa\n");
	printf("RANAIVOTRIMO Baritahina\n");
	printf("RAZAFITRIMO Tsifeherana Miranto\n");
}
