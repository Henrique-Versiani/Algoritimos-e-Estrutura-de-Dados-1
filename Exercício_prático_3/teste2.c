#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void ans( struct TreeNode *cell, int depth, int x, int y, int temp );
bool isCousins( struct TreeNode *root, int x, int y );
struct TreeNode *createNode( int val );

int fatherX = -1, fatherY = -1;
int depthX, depthY;

int main( void ) {
    struct TreeNode *root = createNode( 1 );
    root->left = createNode( 3 );
    root->right = createNode( 2 );
    root->right->right = createNode( 4 );
    root->right->left = createNode( 7 );
    root->right->right->left = createNode( 5 );
    root->right->right->left->right = createNode( 8 );
    root->right->right->right = createNode( 6 );
    root->right->right->right->right = createNode( 9 );

    int x = 9;
    int y = 8;

    if ( isCousins( root, x, y ) )
        printf( "%d and %d are cousins.\n", x, y );
    else
        printf( "%d and %d are not cousins.\n", x, y );

    
    free( root->left );
    free( root->right->left );
    free( root->right->right->left->right );
    free( root->right->right->left );
    free( root->right->right->right->right );
    free( root->right->right->right );
    free( root->right->right );
    free( root->right );
    free( root );

    return 0;
}

void ans( struct TreeNode *cell, int depth, int x, int y, int temp )
{
    if ( cell == NULL )
        return;
    if ( cell->val == x )
    {
        fatherX = temp;
        depthX = depth;
    }
    if ( cell->val == y )
    {
        fatherY = temp;
        depthY = depth;
    }
    ans( cell->left, depth + 1, x, y, cell->val );
    ans( cell->right, depth + 1, x, y, cell->val );
}

bool isCousins( struct TreeNode *root, int x, int y )
{
    ans( root, 0, x, y, 0 );
    if ( depthX == depthY && fatherX != fatherY )
        return true;
    return false;
}

struct TreeNode *createNode( int val )
{
    struct TreeNode *newNode = ( struct TreeNode * )malloc( sizeof( struct TreeNode ) );
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}