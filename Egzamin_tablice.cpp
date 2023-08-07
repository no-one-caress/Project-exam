//#include "struct_variables.h"
//#include "errors.cpp"
#include "functions_data.h"
#include "functions_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAX_LINE 256

struct data
{
    char* question;
    char* answers;
    char correct_answer[1];
    //struct data* n;
};
//struct data* H = NULL;

struct data** tab_data;
int max_tab = 0;
int current_tab = 0;

extern void error(int, char*);
//extern void get_data();
//extern void display_data();
//extern void add_head(); //adds new question to the top of the list (for two-way list can use Tail to add new items)
//extern void delete_question(int numb_delete);
//extern void clear_data();
//extern void save_to_file();
//extern void generate_random_questions(int amount, int* tab);
//extern void output_generated_questions(int amount, int* tab);

int questions_total = 0;
int correct_answers_total = 0; //not necessarry, if delete then change case 1 in switch(op)

int main()
{
    {
        FILE* fd;
        if (!(fd = fopen("data.txt", "r"))) error(2, "data.txt");

        alloc_tab();
        get_data(fd);
        if (fd) fclose(fd);
    }
    //display_data();

    int op = 0; //options

    while (1)
    {
        op = 0;
        printf("(1) Conduct a test\n(2) Edit data base\n(3) Quit program\n");
        while (op == 0 || !(op >= 1 && op <= 3))
        {
            if (scanf("%d", &op) != 1) error(1, "integers only");
            //if (!(op >= 1 && op <= 3)) printf("Incorrect number\n");
            getchar();
        }

        switch (op)
        {
        case 1:
            if (questions_total == 0)
            {
                printf("Your data base is empty!\n");
                break;
            }
            conduct_test();
            break;
        case 2:
            edit_data();
            break;
        case 3:
            printf("Clearing all data...\n");
            clear_data();
            printf("Quitting...");
            goto loop_exit;
            break;
        }
    }
loop_exit:;
}
