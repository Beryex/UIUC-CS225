/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    // assume input curDim is always valid
    if(first[curDim] == second[curDim]) {
      return first < second;
    } else {
      return first[curDim] < second[curDim];
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    // cumpute distance
    double curDistance = 0;
    double potential_Distance = 0;
    for(unsigned i = 0; i < Dim; i++){
      curDistance += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      potential_Distance += (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    
    // check distance
    if(potential_Distance == curDistance) {
      return potential < currentBest;
    } else {
      return potential_Distance < curDistance;
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> sort_vector = newPoints;
    size = 0;
    root = NULL;
    
    // start recursion
    construct(root, 0, sort_vector);
}


template <int Dim>
void KDTree<Dim>::construct(KDTreeNode*& subtree, int d, vector<Point<Dim>> sort_vector){
  // check stop condition
  if(sort_vector.empty()) return;

  // handle current node
  Point<Dim> point = find_k_smallest(d, sort_vector);
  subtree = new KDTreeNode(point);
  size++;
  unsigned median_index = (sort_vector.size() - 1) / 2;

  // check special case
  if(sort_vector.size() == 1) return;

  // handle left subtree
  vector<Point<Dim>> left_vector;
  left_vector.assign(sort_vector.begin(), sort_vector.begin() + median_index);
  construct(subtree->left, (d + 1) % Dim, left_vector);

  // handle right subtree
  vector<Point<Dim>> right_vector;
  right_vector.assign(sort_vector.begin() + median_index + 1, sort_vector.end());
  construct(subtree->right, (d + 1) % Dim, right_vector);
}

template <int Dim>
Point<Dim> KDTree<Dim>::find_k_smallest(int d, vector<Point<Dim>>& sort_vector){
  // check special cases
  Point<Dim> temp;
  if(sort_vector.size() == 1) return sort_vector[0];

  // find the median point, which is ceil(n/2) smallest element
  unsigned target = (sort_vector.size() - 1) / 2;
  unsigned pivot = 0;
  unsigned smaller_index = sort_vector.size() - 1;
  unsigned larger_index = pivot + 1;
  while(1){
    while(1){                           
      // update smaller_index
      unsigned right_bound = smaller_index + 1;
      while(smallerDimVal(sort_vector[pivot], sort_vector[smaller_index], d)){
        smaller_index--;
      }
      if(smaller_index == pivot)  break;
      // update larger_index
      while(!smallerDimVal(sort_vector[pivot], sort_vector[larger_index], d)){
        larger_index++;
        if(larger_index >= right_bound) break;
      }
      // swap if satisfies requirement
      if(larger_index < smaller_index){
        temp = sort_vector[smaller_index];
        sort_vector[smaller_index] = sort_vector[larger_index];
        sort_vector[larger_index] = temp;
      } else {
        break;
      }
    }
    // swap pivot and smaller index
    temp = sort_vector[smaller_index];
    sort_vector[smaller_index] = sort_vector[pivot];
    sort_vector[pivot] = temp;
    if(target == smaller_index) return sort_vector[smaller_index];
    if(target < smaller_index){
      pivot = 0;
      smaller_index = smaller_index - 1;
      larger_index = pivot + 1;
    } else {
      pivot = smaller_index + 1;
      smaller_index = sort_vector.size() - 1;
      larger_index = pivot + 1;
    }
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  root = copy(other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this != &rhs){
    clear(root);
    root = copy(rhs.root);
    size = rhs.size;
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
  size = 0;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subtree){
  // check stop condition
  if(subtree == NULL) return;

  // handle left subtree
  clear(subtree->left);

  // handle right subtree
  clear(subtree->right);

  // handle current node
  delete subtree; subtree = NULL;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode* subtree){
  if(subtree == NULL) return NULL;

  KDTreeNode* newNode = new KDTreeNode(subtree->point);
  newNode->left = copy(subtree->left);
  newNode->right = copy(subtree->right);
  return newNode;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> currentBest;
    double radius = -1;
    if(root != NULL) findNearestNeighbor(root, currentBest, query, radius, 0);
    return currentBest;
}

template <int Dim>
void KDTree<Dim>::findNearestNeighbor(const KDTreeNode* subtree, Point<Dim>& currentBest, 
                                      const Point<Dim>& query, double& radius, int d) const
{
    // check stop condition
    if(subtree->left == NULL && subtree->right == NULL){
      if(radius == -1 || shouldReplace(query, currentBest, subtree->point)){
        currentBest = subtree->point;
        double sum = 0;
        for(unsigned i = 0; i < Dim; ++i){
          sum += sqrt((currentBest[i] - query[i]) * (currentBest[i] - query[i]));
        }
        radius = sum;
      }
      return;
    }

    // handle main part
    if(smallerDimVal(query, subtree->point, d)){
      if(subtree->left != NULL)   findNearestNeighbor(subtree->left, currentBest, query, radius, (d + 1) % Dim);
    } else {
      if(subtree->right != NULL)  findNearestNeighbor(subtree->right, currentBest, query, radius, (d + 1) % Dim);
    }

    // check main node in this dimension
    if(radius == -1 || shouldReplace(query, currentBest, subtree->point)){
      currentBest = subtree->point;
      double sum = 0;
      for(unsigned i = 0; i < Dim; ++i){
        sum += sqrt((currentBest[i] - query[i]) * (currentBest[i] - query[i]));
      }
      radius = sum;
    }
    
    // check other plane
    if(smallerDimVal(query, subtree->point, d) && query[d] + radius >= subtree->point[d]){
      if(subtree->right != NULL) findNearestNeighbor(subtree->right, currentBest, query, radius, (d + 1) % Dim);
    }
    if(!smallerDimVal(query, subtree->point, d) && query[d] - radius <= subtree->point[d]){
      if(subtree->left != NULL) findNearestNeighbor(subtree->left, currentBest, query, radius, (d + 1) % Dim);
    }
}

