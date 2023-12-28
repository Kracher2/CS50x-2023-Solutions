#include "cs50.h"
#include <stdio.h>
#include <string.h>

#define MAX 9

int preferences[MAX][MAX];

bool locked[MAX][MAX];

typedef struct
{
    int winner;
    int loser;
} pair;

string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair sorted_pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void swap(int a, int b);
bool circle(int a, int b);

int main(int argc, string argv[])
{

    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void)
{
    int npairs = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[npairs].winner = i;
                pairs[npairs].loser = j;
                pair_count++;
                npairs++;
            }
        }
    }
}

void sort_pairs(void)
{
    int x = 0;
    int npairs = 0;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[j].winner][pairs[j].loser])
            {
                x++;
            }
        }
        if (x == pair_count - (npairs + 1))
        {
            swap(npairs, i);
            npairs++;
        }
        x = 0;
    }
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!circle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool win = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                win = false;
            }
        }
        if (win == true)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
}

void swap(int a, int b)
{
    pair temp = pairs[a];
    pairs[a] = pairs[b];
    pairs[b] = temp;
}

bool circle(int a, int b)
{
    if (locked[b][a] == true)
    {
        return true;
    }
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[i][a] == true)
        {
            return circle(i, b);
        }
    }
    return false;
}
