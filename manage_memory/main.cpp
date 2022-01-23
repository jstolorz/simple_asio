#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <asio.hpp>

using asio::ip::tcp;

// Class to manage the memory to be used for handler-based custom allocation.
// It contains a single block of memory which may be returned for allocation
// requests. If the memory is in use when an allocation request is made, the
// allocator delegates allocation to the global heap.
class handler_memory{

    handler_memory()
    : in_use_(false)
    {}

    handler_memory(const handler_memory&) = delete;
    handler_memory& operator=(const handler_memory&) = delete;

    void* allocate(){

    }


private:

    // Storage space used for handler-based custom memory allocation.
    typename std::aligned_storage<1024>::type storage_;

    // Whether the handler-based custom allocation storage has been used.
    bool in_use_;
};

int main(){

    return 0;
}


