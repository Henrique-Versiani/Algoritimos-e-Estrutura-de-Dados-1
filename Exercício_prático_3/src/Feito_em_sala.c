/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
*/
bool motherOfTwo ( struct TreeNode *cell )
{
    if ( cell->left != NULL && cell->right != NULL )
        return true;
    else
        return false;
}

bool isCousins(struct TreeNode *root, int x, int y){
    struct TreeNode *cellLeft, *cellRight;
    int depthL = 1, depthR = 1, depthGrand = 0;
    while ( !motherOfTwo ( root ) )
    {
        if ( root->left != NULL )
            root = root->left;
        else if ( root->right != NULL )
            root = root->right;
        else
            return false;
        depthGrand++;
    }

        cellLeft = root->left;  
        if( cellLeft->left != NULL && ( cellLeft->left->val == x || cellLeft->left->val == y ) ){
            cellLeft = cellLeft->left;
            depthL++;
        }
        else if( cellLeft->right != NULL ){
            cellLeft = cellLeft->right;
            depthL++;
        }

        cellRight = root->right;
        if( cellRight->left != NULL && ( cellRight->left->val == x || cellRight->left->val == y ) ){
            cellRight = cellRight->left;
            depthR++;
        }
        else if( cellRight->right != NULL ){
            cellRight = cellRight->right;
            depthR++;
        }

    if ( ( cellLeft->val == x || cellLeft->val == y ) && ( cellRight->val == x || cellRight->val == y ) && ( depthL - 2 == depthGrand && depthR - 2 == depthGrand) )
        return true;
    else
        return false;
}