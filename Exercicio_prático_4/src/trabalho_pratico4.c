#include <stdio.h>
#include <stdlib.h>

void swap(int **a, int **b) {
    int *temp = *a;
    *a = *b;
    *b = temp;
}

int divide(int **arr, int lower, int upper) {
    int pivo = arr[upper][0];
    int i = (lower - 1);

    for (int j = lower; j <= upper - 1; j++) {
        if (arr[j][0] <= pivo)
        {
            i++;
            swap( &arr[i], &arr[j] );
        }
    }
    swap(&arr[i + 1], &arr[upper]);
    return (i + 1);
}


void quickSort(int **arr, int lower, int upper) {
    if (lower < upper) {
        int pi = divide(arr, lower, upper);

        quickSort(arr, lower, pi - 1);
        quickSort(arr, pi + 1, upper);
    }
}

int **merge( int **intervals, int intervalsSize, int *returnSize, int **returnColumnSizes ){
    quickSort(intervals, 0, intervalsSize - 1);

    printf( "[" );
    for (int i = 0; i < intervalsSize; i++)
    {
        printf( "[");
        for (int j = 0; j < 2; j++)
        {
            printf(" %d ", intervals[i][j]);
        }
        printf("]");
    }
    printf("]\n\n");
    
    int **ans = ( int ** )malloc( sizeof( int * ) * intervalsSize );
    ans[0] = intervals[0];
    int top = 1;

    for( int i = 1; i < intervalsSize; i++ ){
        if( intervals[i][0] <= ans[top-1][1] )
            ans[top-1][1] = intervals[i][1]>ans[top-1][1]?intervals[i][1]:ans[top-1][1];
        else
            ans[top++] = intervals[i];
    } 
  
    *returnSize = top;
    *returnColumnSizes = (int*)malloc(sizeof(int)*(*returnSize));

    for(int i = 0;i < *returnSize;i++)
        (*returnColumnSizes)[i] = 2;

    return ans;
}

int main(void)
{
    int interval1[] = {1, 4};
    int interval2[] = {3, 6};
    int interval3[] = {15, 18};
    int interval4[] = {0, 0};
    int interval5[] = {19, 21};
    int interval6[] = {20, 30};
    int *intervals[] = {interval1, interval2, interval3, interval4, interval5, interval6};
    int intervalsSize = 6;
    int returnSize = 0;
    int *returnColumnSize = NULL;

    printf( "[" );
    for (int i = 0; i < intervalsSize; i++)
    {
        printf( "[");
        for (int j = 0; j < 2; j++)
        {
            printf(" %d ", intervals[i][j]);
        }
        printf("]");
    }
    printf("]\n\n");

    int **result = merge(intervals, intervalsSize, &returnSize, &returnColumnSize);
    
    printf( "[" );
    for (int i = 0; i < returnSize; i++)
    {
        printf( "[");
        for (int j = 0; j < returnColumnSize[i]; j++)
        {
            printf(" %d ", result[i][j]);
        }
        printf("]");
    }
    printf("]");
    for (int i = 0; i < returnSize; i++)
        free(result[i]);

    free(result);
    free(returnColumnSize);

    return 0;
}