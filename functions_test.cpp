//#include "struct_variables.h"
//#include "errors.cpp"
#include "functions_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#pragma warning(disable:4996)
#define MAX_LINE 256

extern struct data** tab_data;
extern int max_tab;
extern int current_tab;
extern int questions_total;
extern int correct_answers_total;

extern void error(int, char*);

struct data
{
	char* question;
	char* answers;
	char correct_answer[1];
};

void generate_random_questions(int amount, int* tab)
{
	srand(time(0));
	int i;
	for (i = 0; i < questions_total; i++)
	{     // fill array
		tab[i] = i;
		//printf("%d ", tab[i]);
	}

	for (i = 0; i < questions_total; i++)
	{    // shuffle array
		int temp = tab[i];
		int randomIndex = rand() % questions_total;

		tab[i] = tab[randomIndex];
		tab[randomIndex] = temp;
	}

	for (i = 0; i < questions_total; i++)
	{
		tab[i] = tab[i] + 1;
	}

	printf("Drawn questions: ");
	for (int i = 0; i < amount; i++)
	{    // print array
		printf("%d ", tab[i]);
	}
	printf("\n");
}

void output_generated_questions(int amount, int* tab)
{
	int i;
	char user_answer[MAX_LINE];
	unsigned len;

	for (i = 0; i < amount; i++)
	{

		printf("\nQUESTION %d\n", tab[i]);
		printf("%s| \n%s| \n", tab_data[tab[i]]->question, tab_data[tab[i]]->answers);

	input_again:
		user_answer[0] = '\0';
		printf("Enter your answer: ");
		fgets(user_answer, MAX_LINE, stdin);
		len = (unsigned)strlen(user_answer);
		user_answer[len - 1] = '\0';
		if (if_dlugosc_0(user_answer))
		{
			goto input_again;
		}
		if (len - 1 != 1 || (isalpha(user_answer[0]) == 0 || isalpha(user_answer[0]) == 1))
		{
			printf("Incorrect input!\n");
			goto input_again;
		}
		if (!(user_answer[0] >= 97 && user_answer[0] <= 99))
		{
			goto input_again;
		}
		
		if (user_answer[0] == tab_data[tab[i]]->correct_answer[0])
		{
			printf("Your answer is correct!\n");
			correct_answers_total++;
		}
		else
		{
			printf("Your answer is wrong!\n");
		}
		user_answer[0] = '\0';
	}
}

void conduct_test()
{
	correct_answers_total = 0;
	printf("Enter the number of questions that will be drawn: ");
	int amoun_of_questions_to_draw = 0;
	int temp = 0; int temp2 = 0;
	while (amoun_of_questions_to_draw == 0 || !(amoun_of_questions_to_draw >= 1 && amoun_of_questions_to_draw <= questions_total))
	{
		if (scanf("%d", &amoun_of_questions_to_draw) != 1)
		{
			if (temp2 == 0)
			{
				error(1, "Provide a number in a correct range");
				printf("Total amount of questions is %d\n", questions_total);
				temp2++;
			}
			temp++;
		}
		if (!(amoun_of_questions_to_draw >= 1 && amoun_of_questions_to_draw <= questions_total))
		{
			if (temp == 0)
				printf("Total amount of questions is %d\n", questions_total);
			temp = 0;
		}
		getchar();
	}

	int* tab; tab = (int*)malloc(sizeof(int) * questions_total); //array to store numbers of drawn questions
	if (!tab)
	{
		error(3, "array for generated questions");
		exit(1);
	}
	generate_random_questions(amoun_of_questions_to_draw, tab);
	output_generated_questions(amoun_of_questions_to_draw, tab);

	printf("\nYour final score is: %d\n", correct_answers_total);

}

void edit_data()
{
	int op_2 = 0; //options for editing data base
	while (1)
	{
		op_2 = 0;
		printf("(1) Display data base\n(2) Add question\n(3) Delete question\n(4) Clear all data\n(5) Save current data base to a file\n(6) Quit editing\n");
		while (op_2 == 0 || !(op_2 >= 1 && op_2 <= 6))
		{
			if (scanf("%d", &op_2) != 1) error(1, "integers only");
			//if (!(op >= 1 && op <= 4)) printf("Incorrect number\n");
			getchar();
		}

		switch (op_2)
		{
		case 1:
			display_data();
			break;
		case 2:
			add_element();
			break;
		case 3:
			printf("Number of the question to be deleted: ");
			int numb_delete = 0;
			while (numb_delete == 0 || !(numb_delete >= 1 && numb_delete <= questions_total))
			{
				if (scanf("%d", &numb_delete) != 1)
				{
					error(1, "Provide a number in a correct range, total amount of questions is ");
					printf("%d", questions_total);
				}
				getchar();
			}
			delete_question(numb_delete);
			break;
		case 4:
			clear_data();
			break;
		case 5:
			save_to_file();
			break;
		case 6:
			goto loop_exit;
			break;
		}
	}
loop_exit:;
}