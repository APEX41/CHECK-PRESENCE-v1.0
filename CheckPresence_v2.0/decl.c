#include "machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void checkPC()
{
    StudentMachine *person;
    person = data();
	Try:
    	displayAndChoice(person);
	goto Try;
}
void printAllList(StudentMachine *student)
{
	int choice;
	char line[200];
	char find_name[200];
	FILE *file = ouvrir(".Dtmp.csv","r");
	choice = second_menu();
	switch (choice)
	{
	case 1:
		strcpy(find_name,"ABSENT");
		break;
	case 2:
		strcpy(find_name,"YES");
		break;
	case 3:
		strcpy(find_name,"PERSONAL");
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


void sent()
{	
	printf(" ________________________\n");
	printf("/   Send Now             \\\n");
	printf("\\_______________________/\n");
	system("chmod +x Send.bash");
	system("./Send.bash");
}
void free2D(char **array)
{
	int i;
    for (i = 0; i < STUDENT_NUMBER; i++)
	{
        free(array[i]);
    }
    free(array);
}

void menuprint()
{
    printf(" ____________________________________                _____________________________________\n");
    printf("/ 1 \\        SEARCH NAME             \\              / 2 \\      NUMBER SEARCH              \\\n");
    printf("\\___/________________________________/              \\___/_________________________________/\n");
    printf(" ____________________________________                _____________________________________\n");
    printf("/ 3 \\     LIST OF ALL STUDENT        \\              / 4 \\      QUIT THIS PROGRAMM         \\\n");
    printf("\\___/________________________________/              \\___/_________________________________/\n");
    printf(" ____________________________________                _____________________________________\n");
    printf("/ 5 \\ SENT THE CHECK'S FILE ON EMAIL \\              / 6 \\      APEX MEMBER                \\\n");
    printf("\\___/________________________________/              \\___/_________________________________/\n");
    printf("\t\t\t __________________________________________\n");
    printf("\t\t\t/ 7 \\ CONFIRM END OF CHECKING (FOR TODAY) \\\n");
    printf("\t\t\t\\___/_____________________________________/ \n");
}

void displayAndChoice(StudentMachine *person)
{
    int choice;
    int number;
	int read;
	menuprint();
	do{
		printf("\t Your choice: ");
		read = scanf("%d",&choice);
		if(read != 1)
			choice = verify(read);
		if(choice == 1)
		{
			number = search(person);
			writeFile(person,number);
		}
		else if(choice == 2)
		{
			number = findNumber(person);
			writeFile(person,number);
		}
		else if(choice == 3)
		{
			printAllList(person);
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

void printResult()
{
	printf("_______________________________________________________________________________\n");
	printf("|__________Result Found     :__________________________________________________|\n");
	printf("|number|NAME____________________________|FIRSTNAME_____________________________|\n");
	printf("|______________________________________________________________________________|\n");
}
void writeFile(StudentMachine *student,int num)
{
	FILE *file = NULL;
	char option[20];
	char ancientOption[20];
	int i;
	FILE *tempData = ouvrir(".Dtmp.csv","w+");
	file = ouvrir(".tmp.html","w+");
	use util = traitment(student[num].number);
	student[num].machine = util;
	switch(util)
	{
		case (YES):
			strcpy(option, "YES");
			break;
		case (NO):
			strcpy(option, "NO");
			break;
		case (PERSONAL):
			strcpy(option, "PC_PERSONAL");
			break;
		case (ABSENT):
			strcpy(option, "ABSENT");
			break;
	}
	fprintf(file, "<HTML>\n");
	fprintf(file, "\t<HEAD>\n");
	fprintf(file, "\t\t<TITLE>");
	fprintf(file, "APEX TEAM ");
	fprintf(file, "</TITLE>\n");
	fprintf(file, "\t</HEAD>\n");
	fprintf(file, "\t<BODY style=\"font-family:Arial;background-size:cover; background-image:url('images.png')\"\n");
	student[num].temp = timeRightNow();
	fprintf(file, "\t\t<figure style=\"display: inline-block; vertical-align: middle;\">");
    fprintf(file, "\t\t\t<img src=\"logo_mit.png\" width=\"150\" height=\"150\">");
    fprintf(file, "\t\t</figure>");
	fprintf(file, "\t<CENTER>\n");
	fprintf(file, "\t\t\t<FONT COLOR=\"#000000\"><b>=====================> %s <======================</b></FONT><br><br>\n", __DATE__);
	fprintf(file, "\t\t\t<FONT COLOR=\"black\" style=\" margin:0; font-size: 45px; font-weight:bold; box-shadow:0 4px 8px rgba(20,100,100,100);\"><b> CHECK PC L1 MIT </b></FONT><br><br>\n");	
	fprintf(file, "\t\t<table border=\"0\" cellpadding=\"20\" cellspacing=\"5\" style=\"border-collapse: collapse; width: 100 max-width: 1200px; box-shadow: 0 50px 8px rgba(20, 100, 100, 100);\">\n");
	for(i = 0;i<STUDENT_NUMBER;i++)
	{
		if(i == num)
		{
			//sauvegarde des data
			fprintf(tempData, "%d %s %s\n", student[i].number,timeRightNow(),option);
			//write du file .tmp.html
			fprintf(file,  "\t<tr style=\"background-color: ##B143BF;\">\n\t\t<b><TD><FONT COLOR=\"black\">%d</FONT></TD></b>\n", student[i].number);
			fprintf(file,  "\t\t<TD style=\"border: 1px solid #ff4b4b; box-shadow: 0 1px 3pxrgba(0, 0, 0, 0.1);\"><b><FONT COLOR=\"black\">%s</FONT></b></TD>\n",student[i].name);
			fprintf(file,  "\t\t\"<TD style=\"border: 1px solid #ff4b4b; box-shadow: 0 1px 3pxrgba(0, 0, 0, 0.1);\"><FONT COLOR=\"black\">%s</FONT></TD>\n",student[i].firstName);
			fprintf(file,  "\t\t<TD style=\"border: 1px solid #ff4b4b; box-shadow: 0 1px 3pxrgba(0, 0, 0, 0.1);\"><FONT COLOR=\"#000000\">%s </FONT></TD>\n",__DATE__);
			fprintf(file,  "\t\t<TD style=\"border: 1px solid #ff4b4b; box-shadow: 0 1px 3pxrgba(0, 0, 0, 0.1);\"><FONT COLOR=\"#1111FF\">%s </FONT></TD>\n",timeRightNow());
			fprintf(file,  "\t\t<TD style=\"border: 1px solid #ff4b4b; box-shadow: 0 1px 3pxrgba(0, 0, 0, 0.1);\"><IMG src=\"%s.png\" height=50 width=50></TD>\n</TR>\n",option);
		}
		else{
			switch(student[i].machine)
			{
				
				case (YES):
					strcpy(ancientOption, "YES");
					break;
				case (NO):
					strcpy(ancientOption, "NO");
					break;
				case (PERSONAL):
					strcpy(ancientOption, "PC_PERSONAL");
					break;
				case (ABSENT):
					strcpy(ancientOption, "ABSENT");
					break;
			}
			fprintf(tempData, "%d %s %s\n", student[i].number,student[i].temp,ancientOption);
			//write du file .tmp.html
			fprintf(file,  "\t<tr style=\"background-color: ##B143BF;\">\n\t\t<TD><br><FONT COLOR=\"black\">%d</FONT></br></TD>\n", student[i].number);
			fprintf(file,  "\t\t<TD style=\"border: 1px solid #ff4b4b; box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);\"><b><FONT COLOR=\"black\">%s</FONT></b></TD>\n",student[i].name);
			fprintf(file,  "\t\t\"<TD style=\"border: 1px solid #ff4b4b; box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);\"><FONT COLOR=\"black\">%s</b></FONT></TD>\n",student[i].firstName);
			fprintf(file,  "\t\t<TD style=\"border: 1px solid #ff4b4b; box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);\"><FONT COLOR=\"#000000\">%s </FONT></TD>\n",__DATE__);
			fprintf(file,  "\t\t<TD style=\"border: 1px solid #ff4b4b; box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);\"><FONT COLOR=\"#1111FF\">%s </FONT></TD>\n",student[i].temp);
			fprintf(file,  "\t\t<TD style=\"border: 1px solid #ff4b4b; box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);\"><IMG src=\"%s.png\" height=50 width=50></TD>\n</TR>\n",ancientOption);
		}
	}
	fprintf(file, "\t\t</TABLE>\n");
	fprintf(file, "\t</CENTER><br><br>\n");
	fprintf(file, "<b>==>Dernier modification :%s\n\t\t%s</b><br><br>\n", __DATE__,__TIME__);
	fprintf(file, "\t</BODY>\n");
	fprintf(file, "</HTML>\n");
	fclose(file);
	fclose(tempData);
}
void confirmation()
{
	int i;
	char tempLine[300];
	char barre[101];
	FILE *tmp = ouvrir(".tmp.html","a+");
	FILE *file = ouvrir("check.html","a+");
	memset(barre,' ',STUDENT_NUMBER);
	for(i = 0;i < STUDENT_NUMBER*8 + 15;i++)
	{
		fgets(tempLine,299,tmp);
		fputs(tempLine,file);
		printf("[");
		printf("%s]-->[%d/%d]\r",barre,i/8,STUDENT_NUMBER);
		usleep(1000);
		barre[i/8] = '#';
		fflush(stdout);
	}
	printf("[%s]-->[%d/%d]",barre,STUDENT_NUMBER,STUDENT_NUMBER);
	printf("\n");
	fclose(tmp);
	fclose(file);
	remove(".Dtmp.csv");
	exit(1);
}

void APEX()
{
	printf("RAKOTONDRAIBE Mihasintsoa Hosea\n");
	printf("RAMANDIAMANANA Iavonirina Ambinintsoa\n");
	printf("RANAIVOTRIMO Baritahina\n");
	printf("RAZAFITRIMO Tsifeherana Miranto\n");
}
