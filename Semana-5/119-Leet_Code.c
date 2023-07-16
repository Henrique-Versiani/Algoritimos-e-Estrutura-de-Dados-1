int *getRow( int rowIndex, int *returnSize ){
    *returnSize = rowIndex + 1;

    int i, j, **pascal_line = ( int ** )malloc( ( rowIndex + 1 ) * sizeof( int * ) );
    for ( i = 0; i < ( rowIndex + 1 ); i++ )
    {
        pascal_line[i] = ( int * )malloc( ( i + 1 ) * sizeof( int ) );
        pascal_line[i][0] = 1;//<------first
        pascal_line[i][i] = 1;//<-------last

        for ( j = 0; j < i - 1; j++ )
            pascal_line[i][j + 1] = pascal_line[i - 1][j] + pascal_line[i - 1][j + 1];
    }

    return pascal_line[rowIndex];
}