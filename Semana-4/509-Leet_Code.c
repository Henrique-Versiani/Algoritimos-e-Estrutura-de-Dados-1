int fib( int n ){
    int fibonacci, a = 0, b = 1, i;
    for ( i = 1; i < n; i++ )
    {
        fibonacci = a + b;
        a = b;
        b = fibonacci;
    }
    if ( n == 0 )
        fibonacci = 0;
    else if ( n == 1 )
        fibonacci = 1;
    return fibonacci;
}