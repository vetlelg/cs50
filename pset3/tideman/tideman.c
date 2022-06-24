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
bool recursion(int n, int i, int j);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory. Selection sort.
void sort_pairs(void)
{
    
    for (int k = 0; k < pair_count; k++)
    {
        int strength = 0;
        int x;
        pair pair_tmp;
        bool sort = false;
        for (int n = k + 1; n < pair_count - 1; n++) // Iterate through pairs
        {
            int i = pairs[n].winner;
            int j = pairs[n].loser;
            if (preferences[i][j] > strength) // If larger than previous pairs, save strength of victory and pair index. Also set sort to true.
            {
                strength = preferences[i][j];
                sort = true;
                x = n;
            }
        }
        if (sort) // Switch the order of the pairs in the array
        {
            pair_tmp = pairs[x];
            pairs[x] = pairs[k];
            pairs[k] = pair_tmp;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int n = 0; n < pair_count; n++) // Iterate through the pairs
    {
        int i = pairs[n].winner;
        int j = pairs[n].loser;
        if (recursion(n, i, j) == true) // Call recursion which checks for cycle. If it returns true, skip the pair
        {
            continue;
        }
        locked[i][j] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner = 500;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                for (int n = 0; n < candidate_count; n++)
                {
                    if (locked[n][i])
                    {
                        break;
                    }
                    else if (n == candidate_count - 1)
                    {
                        winner = i;
                    }
                }
                
            }
        }
    }
    printf("%s\n", candidates[winner]);
    return;
}

// Check for cycles. Return true if it creates cycles. Return false if not.
bool recursion(int n, int i, int j)
{
    for (int k = 0; k <= n; k++) // Iterate through pairs until pair n
    {
        if (locked[j][pairs[k].loser] == true) // Check if the loser of pair n is the winner of pair k, and if it has been locked
        {
            if (i == pairs[k].loser) // If loser of pair k is equal to i, return true
            {
                return true;
            }
            else if (recursion(n, i, pairs[k].loser) == true)
            {
                return true; // If recursion returns true, return true
            }
        }
    }
    return false; // Else return false
}

