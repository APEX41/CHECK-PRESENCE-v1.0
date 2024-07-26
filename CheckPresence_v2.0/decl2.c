#include "machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

StudentMachine* data()
{
    StudentMachine *l1;
    l1 = (StudentMachine *)malloc(sizeof(StudentMachine) * STUDENT_NUMBER);
    if (l1 == NULL)
	{
        printf("Error when allocating the Array-------\n");
        exit(-1);
    }
    FILE *file = fopen("source.csv", "r");
    if (file == NULL)
	{
        printf("Error when opening the file\n");
        exit(-1);
    }
	char line1[200];
    int i;
	int j;
	int indicator;
    char **NOM = allocation2D();
    char **PRENOM = allocation2D();
    char **number = allocation2D();
	char line[2000];
	char line2[2000];
	FILE *tempData = fopen(".Dtmp.csv","r+");
	if(tempData == NULL)
	{
		indicator = 1;
	}
	else if(tempData != NULL)
	{
		for(i = 0;fgets(line2,1500,tempData) != 0;i++)
		{
			if(i+1 >= STUDENT_NUMBER)
				indicator = 0;
		}
	}
	int test;
	int read1,read2;

	char answer[10];

	if(indicator == 0)
	{
    	printf(" _________________________________\n");
    	printf("/ 1 \\ CONTINUE THE CHECKING       \\\n");
    	printf("\\___/_____________________________/\n");
    	printf("                                  _____________________________________\n");
    	printf("                                  / 2 \\      NEW CHECK                 \\\n");
    	printf("                                  \\___/_________________________________/\n");
		printf("Enter your choice: ");
		read1 = scanf("%d",&test);
		if(read1 != 1)
			test = verify(read1);
		if(test == 1)
			indicator = 0;
		else if(test == 2)
		{
			printf("WARNING: Once chosen , all previous data will be lost !!!!!!!!!!!\n");
			printf("Are you sure you want to continue [YES/NO]?\n");
			printf("Chosing NO is equivalent to chosing \"CONTINUE THE CHECKING\"\n ->");
			scanf("%s",answer); 
			if(strcmp(answer,"YES") == 0)
			{
        		indicator = -1;
    		}
			if(strcmp(answer,"NO") == 0)
			{
        		indicator = 0;
    		}			
		}

		rewind(tempData);

		for(i = 0;fgets(line2,1500,tempData) != 0;i++)
		{
			//printf("%s",line2);
		}
		rewind(tempData);
	}
    int p=0;
	
	i = 0;
    while (fgets(line,1500, file) != 0 && i < STUDENT_NUMBER)
	{
		char *token;
        int field = 0;
        token = strtok(line, " ");
        while (token != NULL)
		{
            switch (field)
			{
                case 0:
                    strcpy(number[i],token);
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
        l1[i].number = atoi(number[i]);
        strcpy(l1[i].name, NOM[i]);
        strcpy(l1[i].firstName, PRENOM[i]);
		l1[i].temp = (char *)malloc(sizeof(char)*50);
		strcpy(l1[i].temp,"---");
        l1[i].machine = ABSENT;
		if(indicator == 0)
		{
			fscanf(tempData,"%d %s %s",&test,l1[i].temp,line1);
			if(strcmp(line1,"YES") == 0 || strcmp(line1,"OUI") == 0)
				l1[i].machine = YES;

			else if(strcmp(line1,"NO") == 0 || strcmp(line1,"NON") == 0)
				l1[i].machine = NO;

			else if(strcmp(line1,"PC_PERSONAL") == 0 || strcmp(line1,"PERSONNEL") == 0)
				l1[i].machine = PERSONAL;

			else if(strcmp(line1,"ABSENT") == 0)
				l1[i].machine = ABSENT;
		}
        i++;
    }
	if(indicator == 0)
		fclose(tempData);
    fclose(file);

    free2D(NOM);
    free2D(PRENOM);
    free2D(number);

    return (l1);
}
char *timeRightNow()
{
    time_t timeT;
    struct tm *time_info;
    char *currentTime = malloc(9 * sizeof(char)); 
    if (currentTime == NULL)
	{
        perror("Erreur d'allocation de memoire");
        exit(EXIT_FAILURE);
    }
    // Obtenir le temps actuel
    time(&timeT);
    time_info = localtime(&timeT);
    strftime(currentTime, 9, "%H:%M:%S", time_info); //transform the time info to chraractere chain
    return currentTime;
}
char **allocation2D()
{
	int i;
	char **A = (char **)malloc(sizeof(char*)*STUDENT_NUMBER);
	for(i = 0;i < STUDENT_NUMBER ;i++)
	{
		A[i] = (char *)malloc(sizeof(char)*255);
	}
	return (A);
}
int findNumber(StudentMachine *student)
{
    int number;
    int read;
	Retry2:
	printf("Enter the number : ");
    read = scanf("%d",&number);
	if(read != 1)
		number = verify(read);

    if(number > STUDENT_NUMBER || number <= 0)
    {
        printf("Student doesn't exist\n");
		printf("Please try again\n");
		goto Retry2;
    }
	printResult();
	printf("|%2d| %-30s |%-35s|\n",student[number - 1].number,student[number -1].name, student[number -1].firstName);
	printf("|___________________________________________________________________________|\n");
    return (number - 1);
}
int verify(int read)
{
	int c=0;
	int choice;
	while(!read)
	{
		if(c == (getchar() != '\n') && c != EOF)
		{
			printf("\tRe-enter your choice : ");
			read = scanf("%d", &choice);
		}
	}
	return (choice);
}
int search(StudentMachine* student)
{
	char nom[200];
	int i ;
	int num;
	int read;
	int indicator = 0;
	int numberFound = 0;
	char nameToLower[200];
	char firstNameToLower[200];
	char verifyNom[200];
	char verifyPrenom[200];
	int j;
	int allNumber[STUDENT_NUMBER];
	printf("Enter the name or firstName you want to search: ");
	getchar();
	fgets(nom, sizeof(nom), stdin);
	nom[strcspn(nom, "\n")] = '\0';
	printResult();
	for (j = 0; j < strlen(nom); j++)
	{
		nameToLower[j] = tolower(nom[j]);
		firstNameToLower[j] = tolower(nom[j]);
	}
	nameToLower[j] = '\0';
	firstNameToLower[j] = '\0';
	
	for (i = 0 ; i< STUDENT_NUMBER; i++)
	{
	    strcpy(verifyNom, student[i].name);
        strcpy(verifyPrenom, student[i].firstName);
		for (j = 0; j < strlen(student[i].name); j++)
		{
			verifyNom[j] = tolower(student[i].name[j]);
		}
		for (j = 0; j < strlen(student[i].firstName); j++)
		{
			verifyPrenom[j] = tolower(student[i].firstName[j]);
		}
		
		if (strcmp(verifyNom,nameToLower) == 0 ||strcmp(verifyPrenom,firstNameToLower) == 0)
		{
			printf("|%2d| %-30s |%-35s|\n", student[i].number, student[i].name, student[i].firstName);
			numberFound++;
		}
        else
        {
            char tempNom[200];
            char tempPrenom[200];
            strcpy(tempNom, nameToLower);
            strcpy(tempPrenom, firstNameToLower);
            char *temp = strtok(tempNom, " ,\t");
            char *temp2 = strtok(tempPrenom, " ,\t");
            while (temp != NULL && temp2 != NULL)
            {
                char *occ = strstr(verifyNom, temp);
                char *occ2 = strstr(verifyPrenom, temp2);
                if (occ || occ2)
                {
                    printf("|%2d| %-30s |%-35s|\n", student[i].number, student[i].name, student[i].firstName);
                    allNumber[numberFound] = i + 1;
                    occ2 = NULL;
                    numberFound++;
                }
                temp = strtok(NULL, " ,\t");
                temp2 = strtok(NULL, " ,\t");
            }
        }
	}
	printf("|___________________________________________________________________________|\n");
	if (numberFound == 0)
	{
		printf("\n\n_____________________________________________________________________________\n");
		printf("|\t\tThe student %s is not on the list     \t\t|\n", nom);
		printf("|____________________________________________________________________________|\n");
		exit(-1);
	}
	Retry :
    printf("Enter the number : ");
	read = scanf("%d",&num);
	if(read != 1)
		num = verify(read);
	for(i = 0;i<numberFound;i++)
	{
		if(num == allNumber[i])
		{
			indicator = 1;
			break;
		}
	}
	if(indicator == 0)
	{
		printf("This student is not on the result !\n");
		printf("Please try again \n");
		goto Retry;
	}
	return (num - 1);
}
FILE *ouvrir(char *fileName, char *mode)
{
	FILE *file = NULL;
	file = fopen(fileName,mode);
	if(file == NULL)
	{
		printf("Erreur d'ouverture\n");
		exit(0);
	}
	return (file);
}
use traitment(int number)
{
    char choice[255];
    printf("YES\tNO\tPERSONAL : ");
    scanf("%s",choice);
    if(strcmp(choice,"YES") == 0 || strcmp(choice,"OUI") == 0)
	{
        return YES;
    }
	if(strcmp(choice,"NO") == 0 || strcmp(choice,"NON") == 0)
	{
        return NO;
    }
    if(strcmp(choice,"ABSENT") == 0)
	{
        return ABSENT;
    }
    if(strcmp(choice,"PERSONAL") == 0 || strcmp(choice,"PERSONNEL") == 0)
	{
        return PERSONAL;
    }
    return (ABSENT);
}
int second_menu()
{
	int choice;
	int read;
	printf("\t=================================================================================\n");
	printf("\t=1                       See the list of student who are absent                 =\n");
	printf("\t=================================================================================\n");
	printf("\t=================================================================================\n");
	printf("\t=2                See the list of student who use computer                      =\n");
	printf("\t=================================================================================\n");
	printf("\t=================================================================================\n");
	printf("\t=3             See the list of student who use a personal computer             =\n");
	printf("\t=================================================================================\n");
	printf("\t=================================================================================\n");
	printf("\t=4                        Quit the special menu                                  =\n");
	printf("\t=================================================================================\n");
	printf("\n What is your choice:");
	read = scanf("%d",&choice);
	if(read != 1)
	{
		choice = verify(read);
	}
	return (choice);
}