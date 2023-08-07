#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data
{
    char* question;
    char* answers;
    char correct_answer[1];
};

int questions_total = 0;
int correct_answers_total = 0;