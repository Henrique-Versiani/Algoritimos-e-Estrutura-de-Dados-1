#include <stdio.h>
#include <stdlib.h>

void Quick_sort( int array[], int left, int right )
{
    int mid, tmp, i, j;
    i = left;
    j = right;
    mid = array[( left + right ) / 2];

    do
    {
        while( array[i] < mid )
            i++;
        while( mid < array[j] )
            j--;
        if(i <= j)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    }while( i <= j );

    if( left < j )
        Quick_sort( array, left, j );
    if( i < right )
        Quick_sort( array, i, right );
}

int thirdMax(int* nums, int numsSize){
    if( numsSize == 1 )
        return nums[0];
    int *array = ( int * )malloc( sizeof( int ) * numsSize );

    for( int i = 0; i < numsSize; i++ )
        array[i] = nums[i];

    int stop = 2;
    Quick_sort( array, 0, (numsSize - 1));
    int Max = array[numsSize - 1];
    int equal = array[numsSize - 1];

    for( int i = ( numsSize - 1 ); i >= 0; i-- )
    {
        if( array[i] == equal )
            stop++;
        else
            equal = array[i];
        stop--;
        if( stop == 0 )
            return array[i];
    }

    return Max;
}

int main( void )
{
    int array[4] = {2,2,1,3};
    int ans = thirdMax(array, 4);
    printf( "Answer: %d", ans );
}