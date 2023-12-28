#include "cs50.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LISTSIZE 1000
#define EXACT 2
#define CLOSE 1
#define WRONG 0
#define GREEN "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m"

string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize");
        return 1;
    }

    int wordsize = atoi(argv[1]);

    if (wordsize < 5 || wordsize > 8)
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8");
        return 1;
    }

    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    int guesses = wordsize + 1;
    printf(GREEN "This is WORDLE50" RESET "\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    for (int i = 0; i < guesses; i++)
    {
        string guess = get_guess(wordsize);

        int status[wordsize];

        for (int j = 0; j < wordsize; j++)
        {
            status[j] = 0;
        }

        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        print_word(guess, wordsize, status);

        if (score == EXACT * wordsize)
        {
            printf("You won!\n");
            break;
        }
        else if (i == wordsize)
        {
            printf("The word was: %s\n", choice);
        }
    }

    return 0;
}

string get_guess(int wordsize)
{
    string guess;

    do
    {
        guess = get_string("Input a %i-letter word: ", wordsize);
    }
    while (strlen(guess) != wordsize);

    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;
    for (int l = 0; l < wordsize; l++)
    {
        for (int m = 0; m < wordsize; m++)
        {
            if (guess[l] == choice[m])
            {
                if (l == m)
                {
                    status[l] = 2;
                    break;
                }
                status[l] = 1;
            }
        }
    }
    for (int n = 0; n < wordsize; n++)
    {
        score += status[n];
    }
    return score;
}

void print_word(string guess, int wordsize, int status[])
{

    for (int q = 0; q < wordsize; q++)
    {
        if (status[q] == 2)
        {
            printf(GREEN "%c" RESET, guess[q]);
        }
        else if (status[q] == 1)
        {
            printf(YELLOW "%c" RESET, guess[q]);
        }
        else
        {
            printf(RED "%c" RESET, guess[q]);
        }
    }

    printf("\n");
    return;
}
