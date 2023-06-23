// link questão: https://leetcode.com/problems/shuffle-the-array/
int* shuffle(int* nums, int numsSize, int n, int* returnSize){
   int inicio = 0, meio = n, i = 0;
   int *vetor = ( int * )malloc( 2*n*sizeof( int ) );
   while ( inicio < n){
       vetor[i++] = nums[inicio++];
       vetor[i++] = nums[meio++];
   }
   *returnSize = i;
   return vetor;
}