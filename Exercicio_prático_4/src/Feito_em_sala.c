#include <stdio.h>
#include <stdlib.h>
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
  int count = 0;
  int i = 0, j = 0;
  int temp = intervalsSize;
  do
  {
    if( intervals[i][j + 1] >= intervals[i + 1][j] )
    {
      intervals[i][j + 1] = intervals[i + 1][j + 1];
      intervalsColSize[i] = intervals[i][j + 1] - intervals[i][j];
      temp--;
    }
    i++;
  }while( count < intervalsSize );
  
  int **ans = ( int ** )malloc( sizeof( int * ) * temp );
  for( int i = 0; i < temp; i++ )
  {
    ans = (int * )malloc( sizeof( int ) * 2 );
    for( int j = 0; j < 2; j++ )
    {
      ans[i][j] = intervals[i][j];
    }
  
  }
  
  return ans;
}