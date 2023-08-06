#ifndef QUEUE_H
#define QUEUE_H

#include <queue> // use a partial full path so we don't recursively include this file

namespace cs225 {
    template <class T, class Container = std::deque<T> >
    class queue : public std::queue<T, Container> {
    public:
        static size_t _ctor_count;

        // these are pretty much copied from libc++'s stack header file
        queue() : std::queue<T, Container>() { _ctor_count ++; };
        queue(const queue& q) : std::queue<T, Container>(q) { _ctor_count ++; };
        queue(queue&& q) : std::queue<T, Container>(q) { _ctor_count ++; };

        explicit queue(const Container& c) : std::queue<T, Container>(c) { _ctor_count ++; };
        explicit queue(Container&& c) : std::queue<T, Container>(c) { _ctor_count ++; };

        template <class Alloc> explicit queue(const Alloc& a) : std::queue<T, Container>(a) { _ctor_count ++; }
        template <class Alloc> queue(const Container& c, const Alloc& a) : std::queue<T, Container>(c, a) { _ctor_count ++; }
        template <class Alloc> queue(Container&& c, const Alloc& a) : std::queue<T, Container>(c, a) { _ctor_count ++; }
        template <class Alloc> queue(const queue& c, const Alloc& a) : std::queue<T, Container>(c, a) { _ctor_count ++; }
        template <class Alloc> queue(queue&& c, const Alloc& a) : std::queue<T, Container>(c, a) { _ctor_count ++; }

        queue& operator=(const queue& other) = default;
    };

    template <class T, class Container>
    size_t queue<T, Container>::_ctor_count = 0;
};

#endif

/* vim: set ft=cpp: */
