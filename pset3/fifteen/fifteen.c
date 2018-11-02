#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define DIM_MIN 3
#define DIM_MAX 9


int board[DIM_MAX][DIM_MAX];


int d;


void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    greet();

    init();

    while (true)
    {
        clear();

        draw();

        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        if (won())
        {
            printf("ftw!\n");
            break;
        }

        printf("Tile to move: ");
        int tile = GetInt();
        
        if (tile == 0)
        {
            break;
        }

        fprintf(file, "%i\n", tile);
        fflush(file);

        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        usleep(500000);
    }
    
    fclose(file);

    return 0;
}

void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

void init(void)
{
    int tiles_number = (d * d) - 1;
    bool is_even = d * d % 2 ? false : true;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (is_even && tiles_number == 2)
            {
                board[i][j] = 1;
            }
            else if (is_even && tiles_number == 1)
            {
                board[i][j] = 2;
            }
            else
            {
                board[i][j] = tiles_number;
            }
            tiles_number--;
        }
    }
    
}

void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 0)
            {
                printf("%2c", '_');
            }
            else
            {
                printf("%2d", board[i][j]);
            }
            printf(" ");
        }
        printf("\n");
    }
}

bool move(int tile)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                if (i - 1 >= 0 && board[i - 1][j] == 0)
                {
                    board[i - 1][j] = tile;
                    board[i][j] = 0;
                }
                else if (i + 1 < d && board[i + 1][j] == 0)
                {
                    board[i + 1][j] = tile;
                    board[i][j] = 0;
                }
                else if (j - 1 >= 0 && board[i][j - 1] == 0)
                {
                    board[i][j - 1] = tile;
                    board[i][j] = 0;
                }
                else if (j + 1 < d && board[i][j + 1] == 0)
                {
                    board[i][j + 1] = tile;
                    board[i][j] = 0;
                }
                else
                {
                    return false;
                }
                return true;
            }
        }
    }
    return false;
}

bool won(void)
{
    int win_tiles = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == win_tiles)
            {
                win_tiles++;
            }
            else if (win_tiles == d * d && board[i][j] == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}