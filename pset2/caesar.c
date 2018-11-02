#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You should provide a TRUE command line argument!");
        return 1;
    } 
    else {
        int key = atoi(argv[1]);

        string message = GetString();
        
        int ASCII_A = 65;
        int ascii_a = 97;
        int len_alphabet = 26;
        
        for (int i = 0, n = strlen(message); i < n; i++) {
        
            if (isupper(message[i]))
                printf("%c", ((message[i] - ASCII_A + key) % len_alphabet) + ASCII_A);
                
            else if (islower(message[i]))
                printf("%c", ((message[i] - ascii_a + key) % len_alphabet) + ascii_a);
            
            else
                printf("%c", message[i]);
        }
    }
    
    printf("\n");
    return 0;
}
