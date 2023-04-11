#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

    for (int c = 0; c < candidate_count; c++)
    {
        if (strcmp(name, candidates[c]) == 0)
        {
            ranks[rank] = c;
            return true;
        }

    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int c = 0; c < candidate_count; c++) // Loop through each rank in ranks (same length as candidate count)
    {
        for (int d = 0; d < candidate_count; d++) // Loop through each candidate in candidates
        {
            if (strcmp(candidates[ranks[c]], candidates[d]) == 0)
                // If the current candidate in candidates matches the current candidate in ranks: Add the voter's preference against the remaning candidates in the rank.
            {
                for (int e = c + 1; e < candidate_count; e++) // Loop through the remaining candidates in the rank
                {
                    for (int f = 0; f < candidate_count; f++) //loop through all candidates in candidates
                    {
                        if (strcmp(candidates[ranks[e]], candidates[f]) == 0)
                            // when the remaining candidates in rank match the candidate in candidates, add the candidate [f] as the loser in the preference against the first match [d]
                        {
                            preferences[d][f] += 1;
                        }
                    }
                }
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int c = 0; c < candidate_count; c++) // Loop over candidates
    {
        for (int d = c + 1; d < candidate_count; d++) // Loop over candidates again to match combinations
        {
            if (preferences[c][d] > preferences[d][c])
            {
                pairs[pair_count].winner = c;
                pairs[pair_count].loser = d;
                pair_count += 1;
            }
            else if (preferences[c][d] < preferences[d][c])
            {
                pairs[pair_count].winner = d;
                pairs[pair_count].loser = c;
                pair_count += 1;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int counter = -1; counter != 0;)
    {
        counter = 0;
        for (int c = 0; c < (pair_count - 1); c++)
        {
            if (preferences[pairs[c].winner][pairs[c].loser] < preferences[pairs[c + 1].winner][pairs[c + 1].loser])
            {
                pair swap1 = pairs[c];
                pair swap2 = pairs[c + 1];
                pairs[c] = swap2;
                pairs[c + 1] = swap1;
                counter += 1;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int c = 0; c < pair_count; c++)
    {
        if (!cycle(pairs[c].winner, pairs[c].loser))
        {
            locked[pairs[c].winner][pairs[c].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    string winner;
    for (int c = 0; c < candidate_count; c++)
    {
        int counter = 0;
        for (int d = 0; d < candidate_count; d++)
        {
            if (locked[d][c] == true)
            {
                counter += 1;
            }
        }
        if (counter == 0)
        {
            winner = candidates[c];
        }
    }
    printf("%s\n", winner);
}

bool cycle(int winner, int loser)
{

    if (winner == loser)
    {
        return true;
    }

    for (int i = 0; i < pair_count; i++)
    {
        if (loser == pairs[i].winner && locked[pairs[i].winner][pairs[i].loser] == true)
        {
            if (cycle(winner, pairs[i].loser))
            {
                return true;
            }
        }
    }

    return false;
}