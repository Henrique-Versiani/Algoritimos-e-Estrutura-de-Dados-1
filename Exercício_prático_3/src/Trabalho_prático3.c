/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
*/
int fatherX = -1, fatherY = -1;
int depthX = 0, depthY = 0;

void ans( struct TreeNode *cell, int depth, int x, int y, int temp )
{
    if( cell == NULL )
        return;
    if( cell->val == x )
    {
        fatherX = temp;
        depthX = depth;
    }
    if( cell->val == y )
    {
        fatherY = temp;
        depthY = depth;
    }    
    ans( cell->left, depth+1, x, y, cell->val );
    ans( cell->right, depth+1, x, y, cell->val );
}

bool isCousins( struct TreeNode *root, int x, int y )
{
    ans ( root, 0, x, y, 0);
    if ( depthX == depthY && fatherX != fatherY )
        return true;
    return false;
}