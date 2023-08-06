/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    // call recursive helper function
    mirror(root);
    return;
}

/**
 * Private helper function for the public mirror function.
 * @param subRoot The current node in the recursion
 */
template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // handle left subtree
    mirror(subRoot->left);

    // handle right subtree
    mirror(subRoot->right);

    // mirror current node
    Node* left_ptr = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = left_ptr;
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // call recursive helper function
    T base = root->elem;
    bool head = true;
    return isOrdered(root, base, head);
}

/**
 * Private helper function for the public isOrdered function.
 * @param subRoot The current node in the recursion
 * @param base the base value to he compared
 * @param head check if the head element
 */
template <typename T>
bool BinaryTree<T>::isOrdered(const Node* subRoot, T &base, bool &head) const
{
    // Base case - null node
    if (subRoot->left == NULL && subRoot->right == NULL){
        bool ret = base <= subRoot->elem || head;
        base = subRoot->elem;
        head = false;
        return ret;
    }

    // hanlde left subtree
    bool result1 = true;
    if(subRoot->left != NULL) result1 = isOrdered(subRoot->left, base, head);

    // handle current node
    bool result = base <= subRoot->elem || head;
    base = subRoot->elem;
    head = false;

    // handle right subtree
    bool result2 = true;
    if(subRoot->right != NULL) result2 = isOrdered(subRoot->right, base, head);

    return (result1 && result2 && result);
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    vector<T> one_path;
    if(root == NULL) return;
    // call helper function to find all paths
    printPaths(root, paths, one_path);
}

/**
* Private helper function for the public printPaths function.
* @param subRoot The current node in the recursion
* @param paths vector of vectors that contains path of nodes
* @param one_path vector that contains one path of nodes
*/
template <typename T>
void BinaryTree<T>::printPaths(const Node* subRoot, vector<vector<T>> &paths, vector<T> &one_path) const{
    // check base case
    if(subRoot->left == NULL && subRoot->right == NULL){
        one_path.push_back(subRoot->elem);
        paths.push_back(one_path);
        return;
    }

    // handle current node
    one_path.push_back(subRoot->elem);
    // handle left subtree
    if(subRoot->left != NULL){
        printPaths(subRoot->left, paths, one_path);
        one_path.pop_back();
    }
    // handle right subtree
    if(subRoot->right != NULL){
        printPaths(subRoot->right, paths, one_path);
        one_path.pop_back();
    }
}



/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    int sum = 0;
    int depth = -1;
    // call recursive helper function
    sumDistances(root, sum, depth);
    return sum;
}

/**
* Private helper function for the public printPaths function.
* @param subRoot The current node in the recursion
* @param sum the result to be calculated
* @param depth the depth of the current node
*/
template <typename T>
void BinaryTree<T>::sumDistances(const Node* subRoot, int &sum, int &depth) const{
    depth++;
    // check base case
    if(subRoot== NULL){
        return;
    }

    // handle current node
    sum += depth;

    // handle left subtree
    sumDistances(subRoot->left, sum, depth);
    depth--;

    // handle right subtree
    sumDistances(subRoot->right, sum, depth);
    depth--;
}
