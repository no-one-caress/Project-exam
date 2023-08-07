//#include "struct_variables.h"
//#include "errors.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)
#define MAX_LINE 256

//extern struct data* H;
extern struct data** tab_data;
extern int max_tab;
extern int current_tab;
extern int questions_total;

extern void error(int, char*);

struct data
{
	char* question;
	char* answers;
	char correct_answer[1];
	//struct data* n;
};

void alloc_tab()
{
	tab_data = (struct data**)malloc(sizeof(struct data*) * 1);
	max_tab += 1;
}

void realloc_tab_more()
{
	tab_data = (struct data**)realloc(tab_data, sizeof(struct data*) * (max_tab + 1));
	max_tab += 1;
}

void realloc_tab_less()
{
	tab_data = (struct data**)realloc(tab_data, sizeof(struct data*) * (max_tab - 1));
	max_tab -= 1;
}

int if_lista_pusta()
{
	if (current_tab < 0)
	{
		printf("List is empty\n");
		return 1;
	}
	else return 0;
}

int if_dlugosc_0(char* bufor)
{
	if (strlen(bufor) == 0) {
		printf("Podano puste dane!\n");
		return 1;
	}
	else return 0;
}

void get_data(FILE* fd)
{
	//FILE* fd;
	//if (!(fd = fopen("data.txt", "r"))) error(2, "data.txt");
	//alloc_tab();

	unsigned len;
	char bufor[MAX_LINE];
	while (fgets(bufor, MAX_LINE, fd))
	{
		current_tab++;
		if (current_tab >= max_tab) realloc_tab_more();
		tab_data[current_tab] = (struct data*)malloc(sizeof(struct data));	//ADD MEMORY CHECK - DONE
		if (!tab_data[current_tab])
		{
			error(3, "struct data* in get_data()");
			exit(1);
		}

		len = (unsigned)strlen(bufor);
		bufor[len - 1] = '\0';
		tab_data[current_tab]->question = (char*)malloc(len); //ADD MEMORY CHECK - DONE
		if (!tab_data[current_tab]->question)
		{
			error(3, "question malloc in get_data()");
			exit(1);
		}
		strcpy(tab_data[current_tab]->question, bufor);

		fgets(bufor, MAX_LINE, fd);
		len = (unsigned)strlen(bufor);
		bufor[len - 1] = '\0';
		tab_data[current_tab]->answers = (char*)malloc(len); //ADD MEMORY CHECK - DONE
		if (!tab_data[current_tab]->answers)
		{
			error(3, "answers malloc in get_data()");
			exit(1);
		}
		strcpy(tab_data[current_tab]->answers, bufor);

		fgets(bufor, MAX_LINE, fd);
		len = (unsigned)strlen(bufor);
		bufor[len - 1] = '\0';
		strcpy(tab_data[current_tab]->correct_answer, bufor);
		
		questions_total++;
	}

	//if (fd) fclose(fd);
}

void display_data()
{
	if (if_lista_pusta()) return;

	for (int i = 1; i <= current_tab; i++)
	{
		printf("\nQUESTION %d\n", i);
		//printf("%p   %p\n", w, w->n);
		printf("%s| \n%s| \n%s|\n", tab_data[i]->question, tab_data[i]->answers, tab_data[i]->correct_answer);
		//printf("\n");
	}
	printf("Amount of questions: %d\n", questions_total);
	printf("Amount of questions: %d\n", current_tab);
}

void add_element()
{
	current_tab++;
	if (current_tab >= max_tab) realloc_tab_more();

	char bufor[MAX_LINE];
	unsigned len;
	tab_data[current_tab] = (struct data*)malloc(sizeof(struct data)); //ADD MEMORY CHECK - DONE
	if (!tab_data[current_tab])
	{
		error(3, "struct data* in add_element()");
		exit(1);
	}
	printf("Input question:\n");
	fgets(bufor, MAX_LINE, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	if (if_dlugosc_0(bufor))
	{
		if (tab_data[current_tab]) free(tab_data[current_tab]);
		current_tab--;
		return;
	}
	tab_data[current_tab]->question = (char*)malloc(len); //ADD MEMORY CHECK - DONE
	if (!tab_data[current_tab]->question)
	{
		error(3, "question malloc in add_element()");
		exit(1);
	}
	strcpy(tab_data[current_tab]->question, bufor);

	printf("Input possible answers: ");
	fgets(bufor, MAX_LINE, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	if (if_dlugosc_0(bufor))
	{
		if (tab_data[current_tab]) free(tab_data[current_tab]);
		current_tab--;
		return;
	}
	tab_data[current_tab]->answers = (char*)malloc(len); //ADD MEMORY CHECK - DONE
	if (!tab_data[current_tab]->answers)
	{
		error(3, "answers malloc in add_element()");
		exit(1);
	}
	strcpy(tab_data[current_tab]->answers, bufor);

	printf("Input correct answer(one letter): ");
	fgets(bufor, MAX_LINE, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	if (if_dlugosc_0(bufor))
	{
		if (tab_data[current_tab]) free(tab_data[current_tab]);
		current_tab--;
		return;
	}
	if (len - 1 != 1 || (isalpha(bufor[0]) == 0 || isalpha(bufor[0]) == 1))
	{
		printf("Incorrect input!\n");
		if (tab_data[current_tab]) free(tab_data[current_tab]);
		current_tab--;
		return;
	}
	if (!(bufor[0] >= 97 && bufor[0] <= 99))
	{
		printf("Incorrect input!\n");
		if (tab_data[current_tab]) free(tab_data[current_tab]);
		current_tab--;
		return;
	}
	strcpy(tab_data[current_tab]->correct_answer, bufor);

	questions_total++;
}

void delete_question(int numb_delete)
{
	if (if_lista_pusta()) return;

	if (tab_data[numb_delete]->question) free(tab_data[numb_delete]->question);
	if (tab_data[numb_delete]->answers) free(tab_data[numb_delete]->answers);
	if (tab_data[numb_delete]) free(tab_data[numb_delete]);

	int i;
	for (i = numb_delete; i < current_tab; i++)
	{
		tab_data[i] = tab_data[i + 1];
	}
	
	questions_total--;
	current_tab--;
	if (current_tab <= max_tab) realloc_tab_less();
}

void clear_data()
{
	if (if_lista_pusta()) return;

	int i;
	for (i = 1; i <= current_tab; i++)
	{
		if (tab_data[i]->question) free(tab_data[i]->question);
		if (tab_data[i]->answers) free(tab_data[i]->answers);
		if (tab_data[i]) free(tab_data[i]);
		tab_data[i] = NULL;
	}
	current_tab = 0;
	questions_total = 0;

	printf("Data has been cleared\n");
}

void save_to_file()
{
	if (if_lista_pusta()) return;

	FILE* fd;

	if (!(fd = fopen("data_edited.txt", "w")))
	{
		error(2, "data_edited.txt, failed to save the data\n");
		return;
	}

	for (int i = 1; i <= current_tab; i++)
	{
		//printf("\nQUESTION %d\n", i);
		//printf("%p   %p\n", w, w->n);
		fprintf(fd, "%s| \n%s| \n%s|\n", tab_data[i]->question, tab_data[i]->answers, tab_data[i]->correct_answer);
		//printf("\n");
		i++;
	}
	printf("Amount of questions saved to file: %d\n", questions_total);

	if (fd) fclose(fd);
}