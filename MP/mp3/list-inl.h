/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <cmath>
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1

  // see clear()
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1

  // delete all listnode
  ListNode* start = head_;
  for(int i = 0; i < size(); i++){
    ListNode* next = start->next;
    delete start;
    start = next;
  }

  // update variable
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1

  // create a new ListNode
  ListNode* new_node = new ListNode(ndata);

  // insrt it to the front
  length_++;
  if (head_ == NULL && tail_ == NULL){
    head_ = tail_ = new_node;
    new_node->next = new_node->prev = NULL; 
  } else {
    ListNode* fir_node = head_;
    head_ = new_node;
    fir_node->prev = new_node;
    new_node->prev = NULL;
    new_node->next = fir_node;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1

  // create a new ListNode
  ListNode* new_node = new ListNode(ndata);

  // insrt it to the back
  length_++;
  if (head_ == NULL && tail_ == NULL){
    head_ = tail_ = new_node;
    new_node->next = new_node->prev = NULL;
  } else {
    ListNode* last_node = tail_;
    tail_ = new_node;
    last_node->next = new_node;
    new_node->prev = last_node;
    new_node->next = NULL;
  }
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1

    // check special case
    if(startPoint == endPoint) return;

    // handle startpoint
    ListNode* head = startPoint->prev;
    if(startPoint->prev != NULL) (startPoint->prev)->next = endPoint;
    startPoint->prev = startPoint->next;
    startPoint->next = endPoint->next;

    // handle points for all points needed to reverse
    ListNode* cur = startPoint->prev;
    while(1){
      ListNode* nextPoint = cur->next;
      cur->next = cur->prev;
      cur->prev = nextPoint;
      if(nextPoint != endPoint){    // so that cur point to the node right before endPoint when while ends
        cur = nextPoint;
        continue;
      }
      break;
    }

    // handle endPoint
    if(endPoint->next != NULL) (endPoint->next)->prev = startPoint;
    endPoint->prev = head;
    endPoint->next = cur;

    // update startPoint and endPoint
    ListNode* ptr3 = endPoint;
    endPoint = startPoint;
    startPoint = ptr3;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  int ct = 0;
  bool if_head = 1;
  ListNode* startPoint = head_;
  while(ct + n <= size()){
    ListNode* endPoint = startPoint;
    int num = n;
    while(--num > 0){
      endPoint = endPoint->next;
    }
    reverse(startPoint, endPoint);
    if(if_head){
      head_ = startPoint;
      if_head = 0;
    }
    if (ct + n == size()){
      tail_ = endPoint;
      return;
    }
    startPoint = endPoint->next;
    ct += n;
  }

  // if rest smaller than n
  ListNode* endPoint = startPoint;
  while(endPoint->next != NULL){
    endPoint = endPoint->next;
  }
  reverse(startPoint, endPoint);
  tail_ = endPoint;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

  ListNode* cur_node = head_;
  while(cur_node->next != tail_ && cur_node->next != NULL){
    ListNode* dePoint = cur_node->next;
    // reconnect at original place
    cur_node->next = dePoint->next;
    (dePoint->next)->prev = cur_node;
    // append the dePoint
    tail_->next = dePoint;
    dePoint->prev = tail_;
    dePoint->next = NULL;
    tail_ = dePoint;
    // update iterator
    cur_node = cur_node->next;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    int ct = splitPoint;
    ListNode* endPoint = start;
    while(--ct > 0){
      endPoint = endPoint->next;
      if(endPoint == NULL){
        printf("bad parameter\n");
        return NULL;
      }
    }
    ListNode* ret = endPoint->next;
    ret->prev = NULL;
    endPoint->next = NULL;
    return ret;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* ret = first;
  while(second != NULL){
    ListNode* next = second->next;
    while(first->next != NULL && first->data < second->data){
      first = first->next;
    }
    if (first->next == NULL && first->data < second->data){
      first->next = second;
      second->prev = first;
      return ret;
    }
    if(first->prev != NULL) (first->prev)->next = second;
    second->prev = first->prev;
    second->next = first;
    first->prev = second;
    if(second->prev == NULL) ret = second;
    second = next;
  }
  return ret;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    // handle recurance stop conditions
    if(start->next == NULL || chainLength <= 1){
      return start;
    }
    
    // handle main part
    ListNode* second = split(start, floor(chainLength / 2));
    start = mergesort(start, floor(chainLength / 2));
    second = mergesort(second, chainLength - floor(chainLength / 2));
    return merge(start,second);
}
