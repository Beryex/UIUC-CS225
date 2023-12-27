/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    // check recur stop conditions
    if(s.empty()) return T();
    // handle main part
    T element = s.top();
    s.pop();
    T result = element + sum(s); 
    // fix the stack
    s.push(element);
    return result;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;

    // Your code here
    int ct = q.size();
    int index = 0;
    int block_num = 1;
    // handle main part
    while(index + block_num <= ct){
        if(block_num % 2 == 1){
            int remain = block_num;
            while(remain-- > 0){
                q2.push(q.front());
                q.pop();
                index++;
            }
            block_num++;
            continue;
        } else {
            int remain = block_num;
            while(remain-- > 0){
                s.push(q.front());
                q.pop();
                index++;
            }
            remain = block_num;
            while(remain-- > 0){
                q2.push(s.top());
                s.pop();
            }
            block_num++;
            continue;
        }
    }
    // handle the rest part
    if(index != ct){
        if(block_num % 2 == 1){
            while(!q.empty()){
                q2.push(q.front());
                q.pop();
            }
        } else {
            int remain = 0;
            while(!q.empty()){
                s.push(q.front());
                q.pop();
                remain++;
            }
            while(remain-- > 0){
                q2.push(s.top());
                s.pop();
            }
        }
    }

    // copy from stack1 to queue q
    q = q2;
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    // check recurance stop conditions
    if(s.empty()){
        return true;
    }
    // handle main part
    T temp1 = s.top(); 
    s.pop();
    retval = (verifySame(s, q));
    T temp2 = q.front();
    retval = temp1 == temp2 && retval;

    // fix the stack
    s.push(temp1);

    // rotate the queue
    q.pop();
    q.push(temp2);

    return retval;
}

}