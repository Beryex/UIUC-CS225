/**
 * @file quackfun.h
 * Contains the QuackFun namespace definition.
 */

#ifndef STACKFUN_H
#define STACKFUN_H

#include "stack"
#include "queue"

using cs225::stack;
using cs225::queue;

/**
 * Namespace to contain the stack and queue functions for this lab.
 */
namespace QuackFun
{
    template <typename T>
    T sum(stack<T>& s);

    template <typename T>
    void scramble(queue<T>& q);

    template <typename T>
    bool verifySame(stack<T>& s, queue<T>& q);
}

#include "quackfun.cpp"
#endif
