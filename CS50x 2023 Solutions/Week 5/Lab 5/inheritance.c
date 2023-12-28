// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // Allocate memory for new person
    person *human = malloc(sizeof(person));

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Set parent pointers for current person
        human->parents[0] = parent0;
        human->parents[1] = parent1;
        // Randomly assign current person's alleles based on the alleles of their parents
        int num0 = rand() % 2;
        if (num0 == 0)
        {
            human->alleles[0] = parent0->alleles[0];
        }
        else
        {
            human->alleles[0] = parent0->alleles[1];
        }

        int num1 = rand() % 2;
        if (num1 == 0)
        {
            human->alleles[1] = parent1->alleles[0];
        }
        else
        {
            human->alleles[1] = parent1->alleles[1];
        }
    }

    // If there are no generations left to create
    else
    {
        // Set parent pointers to NULL
        human->parents[0] = NULL;
        human->parents[1] = NULL;
        // Randomly assign alleles
        int allel0 = rand() % 3;
        if (allel0 == 0)
        {
            human->alleles[0] = 'A';
        }
        else if (allel0 == 1)
        {
            human->alleles[0] = 'B';
        }
        else if (allel0 == 2)
        {
            human->alleles[0] = 'O';
        }

        int allel1 = rand() % 3;
        if (allel1 == 0)
        {
            human->alleles[1] = 'A';
        }
        else if (allel1 == 1)
        {
            human->alleles[1] = 'B';
        }
        else if (allel1 == 2)
        {
            human->alleles[1] = 'O';
        }
    }

    // Return newly created person
    return human;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }
    // Free parents recursively
    if (p->parents[0] != NULL && p->parents[0] != NULL)
    {
        free_family(p->parents[0]);
        free_family(p->parents[1]);
    }
    // Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
