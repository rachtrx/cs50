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
bool cannot_lock(int winner, int loser);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[i] = rank;
            // printf("rank of candidate %s is %i\n", candidates[i], rank + 1);
            return true;
        }
    }
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int a = 0; a < candidate_count - 1; a++)
    {
        int firstRank = ranks[a];
        for (int b = a + 1; b < candidate_count; b++)
        {
            int secondRank = ranks[b];
            if (firstRank < secondRank)
            {
                preferences[a][b] += 1;
                // printf("candidate %s was chosen over candidate %s\n", candidates[a], candidates[b]);
            }
            else
            {
                preferences[b][a] += 1;
                // printf("candidate %s was chosen over candidate %s\n", candidates[b], candidates[a]);
            }

        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int a = 0; a < candidate_count - 1; a++)
    {
        for (int b = a + 1; b < candidate_count; b++)
        {
            if (preferences[a][b] > preferences[b][a])
            {
                pairs[pair_count].winner = a;
                pairs[pair_count].loser = b;
                pair_count += 1;
                // printf("pair count #%i winner is candidate %s and loser is candidate %s\n", pair_count, candidates[a], candidates[b]);
            }

            else if (preferences[a][b] < preferences[b][a])
            {
                pairs[pair_count].winner = b;
                pairs[pair_count].loser = a;
                pair_count += 1;
                // printf("pair count #%i winner is candidate %s and loser is candidate %s\n", pair_count, candidates[b], candidates[a]);
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // printf("Number of pairs: %i\n", pair_count)
    for (int a = 0; a < pair_count - 1; a++)
    {
        int firstWinner = pairs[a].winner;
        int firstLoser = pairs[a].loser;
        int firstDifference = preferences[firstWinner][firstLoser] - preferences[firstLoser][firstWinner];
        for (int b = a + 1; b < pair_count; b++)
        {
            int secondWinner = pairs[b].winner;
            int secondLoser = pairs[b].loser;
            int secondDifference = preferences[secondWinner][secondLoser] - preferences[secondLoser][secondWinner];
            if (secondDifference > firstDifference)
            {
                pair temporary = pairs[a];
                pairs[a] = pairs[b];
                pairs[b] = temporary;
            }
        }
    }
    for (int c = 0; c < pair_count; c++)
    {
        // printf("The #%i strength of victory is %s over %s\n", c + 1, candidates[pairs[c].winner], candidates[pairs[c].loser]);
    }
    return;
}


bool cannot_lock(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        // printf("there is a loop as candidate %s won candidate %s\n", candidates[loser], candidates[winner]);
        return true;
    }
    else
    {
        for (int i = 0; i < pair_count; i++)
        {
            if (locked[loser][pairs[i].loser])
            {
                int newLoser = pairs[i].loser;
                // printf("lets check because candidate %s is already winning candidate %s\n", candidates[loser], candidates[newLoser]);
                return cannot_lock(winner, newLoser);
            }
            else
            {
                // printf("i have checked that there are no cycles found where %s is already winning %s\n", candidates[loser], candidates[pairs[i].loser]);
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int a = 0; a < pair_count; a++)
        {
            int winner = pairs[a].winner;
            int loser = pairs[a].loser;
            // if (a == 0 || a == 1)
            // {
            //     locked[winner][loser] = true;
            //     printf("candidate %s definitely wins candidate %s\n", candidates[winner], candidates[loser]);
            // }
            // else if (a > 1)
            // {
                if (cannot_lock(winner, loser) == false)
                {
                    locked[winner][loser] = true;
                    // printf("candidate %s definitely wins candidate %s\n", candidates[winner], candidates[loser]);
                }
            }
    return;
}




// {
//     // TODO
//     for (int a = 0; a < pair_count; a++)
//     {
//         int winner = pairs[a].winner;
//         int loser = pairs[a].loser;
//         if (a == 0 || a == 1)
//         {
//             locked[winner][loser] = true;
//         }
//         if (a > 1)
//         {
//             int b = a - 1;
//             int previousWinner = loser;
//             bool cannotLock = false;
//             // loop back to the largest winner
//             while (b > 0)
//             {
//                 if (locked[previousWinner][pairs[b].loser])
//                 {
//                     int previousWinner = pairs[b].loser;
//                 }
//                 b--
//             }
//         }

//     }
//     return;

// }




// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int a = 0; a < candidate_count; a++)
    {
        int counter = 0;
        for (int b = 0; b < candidate_count; b++)
        {
            if (locked[b][a] == true)
            {
                // printf("I'm not sure why, but candidate %s wins candidate %s\n", candidates[b], candidates[a]);
                counter += 1;
            }
        }
        // printf("candidate %s has a counter of %i\n", candidates[a], counter);
        if (counter == 0)
        {
            printf("%s\n", candidates[a]);
        }
    }
    return;
}