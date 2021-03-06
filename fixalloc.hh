#pragma once
#include <memory>
#include <stdlib.h>

using std::size_t;
using std::ptrdiff_t;

template<typename T>
class fixalloc : public std::allocator<T>
{
public:
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T&       reference;
    typedef const T& const_reference;
    typedef T        value_type;

    template<typename T1>
    struct rebind {
        typedef fixalloc<T1> other;
    };

    fixalloc() : mem(NULL)
    { }

    fixalloc(pointer mem) : mem(mem)
    { }

    fixalloc(const fixalloc& other)
        : mem(other.mem)
    { }

    template<typename T1>
    fixalloc(const fixalloc<T1>& other)
        : mem((pointer)other.mem)
    { }

    ~fixalloc() { }

    pointer
    allocate(size_type n, const void* hint = 0) {
        return (pointer)mem;
    }

    void
    deallocate(pointer p, size_type)
    { }
protected:
    void * mem;
};
