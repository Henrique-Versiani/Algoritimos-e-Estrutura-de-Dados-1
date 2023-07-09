#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool judgeCircle( char * moves ){
    int x = 0, y = 0, i;
    for ( i = 0; i < strlen( moves ); i++)
    {
        if ( moves[i] == 'U' )
            y += 1;
        else if ( moves[i] == 'D' )
            y -= 1;
        else if ( moves[i] == 'L' )
            x -= 1;
        else if ( moves[i] == 'R' )
            x += 1;
    }

    if ( x == 0 && y == 0 )
        return true;
    else
        return false;
}