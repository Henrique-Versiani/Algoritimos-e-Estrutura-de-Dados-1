int lower ( int a, int b )
{
  if ( a < b)
    return a;
  else
    return b;
}

int minCostClimbingStairs(int* cost, int costSize)
{
    int i;
    for ( i = 2; i < costSize; i++ )
      cost[i] += lower ( cost[i - 1], cost[i - 2]);
      
    return lower ( cost[costSize - 1], cost[costSize - 2]);
}