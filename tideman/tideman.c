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

// My functions prototypes
bool check_arrows(int start, int current, bool temp_locked[MAX][MAX]);
bool check_cycle(int pair_index);
int get_strength(int pair_index);

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
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count ++;
            } else if (preferences[j][i] < preferences[i][j])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
        }
    }
    return;
}

// Gets strength of a pair
int get_strength(int pair_index)
{
    int winner = pairs[pair_index].winner;
    int loser = pairs[pair_index].loser;
    return preferences[winner][loser] - preferences[loser][winner];
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int temp_max_strength = 0;
    pair temp_pair;
    int finished = 0;
    // bubble sort (descending)
    while (!finished)
    {
        finished = 1;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (get_strength(i) < get_strength(i + 1))
            {
                temp_pair = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp_pair;
                finished = 0;
            }
        }
    }
    return;
}

bool check_arrows(int start, int current, bool temp_locked[MAX][MAX])
{
    if (current == start)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (temp_locked[current][i])
        {
            if (check_arrows(start, i, temp_locked))
            {
                return true;
            }
        }
    }
    return false;
}

// Checks if next pair create endless cycle
// returns true if endless cycle created
// returns false if endless cycle isn't created
bool check_cycle(int pair_index)
{



    // return true;
    // pair temp_pairs[MAX];
    bool temp_locked[MAX][MAX];
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            temp_locked[i][j] = locked[i][j];
        }

    }

    int winner = pairs[pair_index].winner;
    int loser = pairs[pair_index].loser;
    temp_locked[winner][loser] = true;

    int start = pairs[pair_index].winner;
    int current = pairs[pair_index].loser;
    // while (current != start)
    // printf("start=%i  current=%i\n", start, current);

    // for (int _ = 0; _ < pair_count + 3 && current != start; _ ++)
    // {
    //     int changed = 0;
    //     for (int i = 0; i < candidate_count + 3; i++)
    //     {
    //         if (temp_locked[current][i])
    //         {
    //             changed = 1;
    //             current = i;

    //         }
    //     }
    //     if (!changed)
    //     {
    //         return false;
    //     }

    // }
    // return true;

    return check_arrows(start, current, temp_locked);

    // temp_pairs
    // int temp_winner = pairs[0].w;
    // for (int i = 0; i < pair_count; i++)
    // {
    //     for (int j = 0; j < pair_count; j++)
    //     {

    //     }
    // }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // print all pairs
    // printf("pair_count = %i\n", pair_count);
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("pairs[%i].winner = %i   .loser = %i\n", i, pairs[i].winner, pairs[i].loser);
    // }

    for (int i = 0; i < pair_count; i++)
    {
        // int winner = pairs[i].winner;
        // int loser = pairs[i].loser;
        // locked[winner][loser] = true;
        if (!check_cycle(i)) {
            // Add pair to locked
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    // for (int i = 0; i < MAX; i++)
    // {
    //     for (int j = 0; j < MAX; j++)
    //     {
    //         if (locked[i][j])
    //         {
    //             printf("locked[%i][%i] = true\n", i, j);
    //         }
    //     }
    // }
    // bool continue_ = true;
    // for (int i = 0; i < pair_count && continue_; i++)
    // {
    //     for (int j = 0; j < pair_count; j++)
    //     {
    //         int temp_winner = pairs[i];
    //         if (temp_winner == pairs[j].loser)
    //         {
    //             // here
    //         }
    //     }
    // }

    // int i = 1;
    // bool continue_ = true;
    // int counter = 0;
    // printf("debug: tu jeszcze działa\n");
    // while (continue_)
    // {
    //     if (pair_count - 1 < i)
    //     {
    //         break;
    //     }
    //     continue_ = true;
    //     int previous_winner = pairs[i].winner;
    //     int j = 0;
    //     counter = 0;
    //     while (j <= i)
    //     {
    //         if (previous_winner == pairs[j].loser)
    //         {
    //             previous_winner = pairs[j].winner;
    //             counter ++;
    //         }
    //         if (pair_count < counter)
    //         {
    //             continue_ = false;
    //             break;
    //         }
    //         j++;
    //     }
    //     i ++;
    // }
    // counter --;
    // if (counter < 0)
    // {
    //     counter = pair_count;
    // }
    // printf("debug: counter = %i\n", counter);

    // for (i = 0; i < counter; i++)
    // for (i = 0; i < counter; i++)
    // {
    //     int winner = pairs[i].winner;
    //     int loser = pairs[i].loser;
    //     printf("i = %i   winner = %i   loser = %i\n", i, winner, loser);
    //     locked[winner][loser] = true;
    // }
    // return;
                // This code works: :) lock_pairs locks all pairs when no cycles
    // for (i = 0; i < pair_count; i++)
    // {
    //     int winner = pairs[i].winner;
    //     int loser = pairs[i].loser;
    //     locked[winner][loser] = true;
    // }
}

// Print the winner of the election
void print_winner(void)
{
    int winner;
    bool continue_ = true;
    for (int j = 0; j < candidate_count; j++)
    {
        continue_ = true;
        for (int i = 0; i < candidate_count && continue_; i++)
        {
            if (locked[i][j])
            {
                continue_ = false;
            }
        }
        if (continue_)
        {
            winner = j;
        }
    }
    // winner -= 1;
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     printf("candidates[%i] = %s\n", i, candidates[i]);
    // }
    printf("%s\n", candidates[winner]);
    return;
}