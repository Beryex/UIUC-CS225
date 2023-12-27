/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* target = t->right;
    t->right = target->left;
    target->left = t;
    t = target;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* target = t->left;
    t->left = target->right;
    target->right = t;
    t = target;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if(subtree == NULL) return;
    int balance = height(subtree->right) - height(subtree->left);
    while(balance > 1 || balance < -1){
        // rotate the subtree
        if(balance > 1){
            int right_balance = height(subtree->right->right) - height(subtree->right->left);
            if(right_balance == 1){
                rotateLeft(subtree);
            } else {
                rotateRightLeft(subtree);
            }
        }
        if(balance < -1){
            int left_balance = height(subtree->left->left) - height(subtree->left->right);
            if(left_balance == 1){
                rotateRight(subtree);
            } else {
                rotateLeftRight(subtree);
            }
        }
        // update tree height
        if(subtree->left != NULL) subtree->left->height = 1 + max(height(subtree->left->left), height(subtree->left->right));
        if(subtree->right != NULL) subtree->right->height = 1 + max(height(subtree->right->left), height(subtree->right->right));
        subtree->height = 1 + max(height(subtree->left), height(subtree->right));
        // recheck balance
        balance = height(subtree->right) - height(subtree->left);
    }
    // update height even no rotation occurs
    if(subtree->left != NULL) subtree->left->height = 1 + max(height(subtree->left->left), height(subtree->left->right));
    if(subtree->right != NULL) subtree->right->height = 1 + max(height(subtree->right->left), height(subtree->right->right));
    subtree->height = 1 + max(height(subtree->left), height(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // check basecase
    if(subtree == NULL){
        subtree = new Node(key, value);
    } else if(key < subtree->key){
        insert(subtree->left, key, value);
        rebalance(subtree);
    } else if(key > subtree->key){
        insert(subtree->right, key, value);
        rebalance(subtree);
    } else if(key == subtree->key){
        // return if the element already exists
        return;
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL) return;

    if (key < subtree->key) {
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree; subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            remove_two_children(subtree->left, subtree);
        } else {
            /* one-child remove */
            if(subtree->left != NULL){
                Node* target = subtree;
                subtree = subtree->left;
                delete target;
            } else {
                Node* target = subtree;
                subtree = subtree->right;
                delete target;
            }
        }
    }
}

template <class K, class V>
int AVLTree<K, V>::height(const Node* node) const{
    if(node == NULL) return -1;
    return node->height;
}

template <class K, class V>
void AVLTree<K, V>::remove_two_children(Node*& subtree, Node*& root){
    // check basecase
    if(subtree->right == NULL){
        swap(subtree, root);
        if (subtree->left == NULL) {
            /* no-child remove */
            delete subtree; subtree = NULL;
        } else {
            /* one-child remove */
            Node* target = subtree;
            subtree = subtree->left;
            delete target;
        }
        return;
    }

    // recur to find IOP
    remove_two_children(subtree->right, root);

    // rebalance
    rebalance(subtree);
}
