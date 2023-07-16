int **generate( int numRows, int *returnSize, int **returnColumnSizes ){
    *returnSize = numRows;
    *returnColumnSizes = ( int * )malloc( numRows * sizeof( int ) );

    int i, j, **pascal_line = ( int ** )malloc( numRows * sizeof( int * ) );
    for ( i = 0; i < numRows; i++ )
    {
        ( *returnColumnSizes )[i] = i + 1;
        pascal_line[i] = ( int * )malloc( (i + 1) * sizeof( int ) );
        pascal_line[i][0] = 1;//<------primeiro
        pascal_line[i][i] = 1;//<-------último

        for ( j = 0; j < i - 1; j++ )
            pascal_line[i][j + 1] = pascal_line[i - 1][j] + pascal_line[i - 1][j + 1];
    }

    return pascal_line;
}