#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * shortestCompletingWord(char * licensePlate, char ** words, int wordsSize){
    int i, j, s = 0, licenseSize = strlen ( licensePlate ), tamanho_palavra;
    int add = *licensePlate;
    //bool flag;
    char new[licenseSize], noNumbers[licenseSize];
    strcpy ( new, licensePlate );
    for ( j = 0; j < licenseSize; j++ )
        {
            if ( isdigit( new[j] ) == 0 )
                noNumbers[s++] = new[j];
        }
    
    // for ( i = 0; i < wordsSize; i++ )
    // {
        for ( j = 0; j < licenseSize; j++ )
        {
            if ( isdigit(licensePlate[j]) == 0 )
                noNumbers[s++] = new[j];
        }
    // }
    return ;
}