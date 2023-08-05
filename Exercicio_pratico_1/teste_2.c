#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *shortestCompletingWord( char *licensePlate, char **words, int wordsSize );

int main( void ){

    char licensePlate[] = "1s3 456";
    char *words[4] = {"looks","pest","stew","show"};
    int size = 4;

    char *answer = shortestCompletingWord( licensePlate, words, size );
    printf( "The shortest is: %s", answer );

    return 0;
}

char *shortestCompletingWord(char * licensePlate, char ** words, int wordsSize){
    int i, j = 0, count = 0, Size_LP = strlen( licensePlate );
    char only_letters[strlen( licensePlate )];

    for ( i = 0; i < Size_LP; i++ ) {
        if ( isdigit( licensePlate[i] ) == 0 && licensePlate[i] != ' ' ) {//<---Insere apenas quando não for número ou espaço
                                                                   
            only_letters[j++] = tolower( licensePlate[i] );//<------------------licensePlate sem númuros, espaços e letras maiúsculas
            count++;
        }
        only_letters[j] = '\0';//<----------------------------------------------marca o final da string
    }

    char *shortestWord[wordsSize];//<-------------------------------------------variável que vai receber cada string compatível
    int saveCount = count, k = 0, l = 0;
    int flag[15][wordsSize];
    int Size_words;
    for ( i = 0; i < wordsSize; i++ ) {//<--------------------------------------percorre cada palavra da words[i]
        count = saveCount;//<---------------------------------------------------renova o valor de cont
        Size_words = strlen( words[i] );
        for ( j = 0; j < saveCount; j++ ) {//<----------------------------------percorre a string only_letters
            for ( k = 0; k < Size_words; k++ ) {//<-----------------------------percorre caractere a caractere do words[i]
                if ( only_letters[j] == words[i][k] && flag[k][i] != -1 ) {
                    count--;
                    flag[k][i] = -1;
                    break;
                }
            }
        }
        if( count == 0 )
            shortestWord[l++] = words[i];//<------------------------------------armazena cada palavra compatível;
    }

    int Size_SW;
    int Size_curr;
    Size_SW = strlen( shortestWord[0] );
    j = 0;

    for ( i = 0; i < l; i++ ) {//<----------------------------------------------percorre a shortestWord para descobrir a menor
        Size_curr = strlen( shortestWord[i] );
        if( Size_SW > Size_curr ) {
            Size_SW = strlen( shortestWord[i] );
            j = i;//<-----------------------------------------------------------armazena a posição do menor
        }
    }
    return shortestWord[j];
}