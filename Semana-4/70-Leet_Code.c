int climbStairs( int n ){
  int fibonacci, a = 0, b = 1, i;
    for ( i = 0; i < n; i++ )
    {
      fibonacci = a + b;
      a = b;
      b = fibonacci;
    }
    return fibonacci;
}