#include <iostream>
#include <memory>

#include "Hourglass.hpp"


struct test_object
{
    test_object() : count( 0 ) {}

    ~test_object(){ std::cout << "~test_object()" << std::endl; }

    void increment(){ std::cout << ++count << std::endl; }

    int count;
};

int main( int, char * [] )
{
    hourglass::Timer timer;

    test_object obj;

    timer.connect( obj, &test_object::increment );

    timer.start( 500 );

    hourglass::Timer::delayedFunctionCall( obj, &test_object::increment, 2 );

    hourglass::sleep( hourglass::seconds( 3 ) );

    timer.stop();

    hourglass::sleep( hourglass::milliseconds( 3000 ) );

    timer.start( 500 );

    hourglass::sleep( hourglass::microseconds( 3000000 ) );

    return 0;
}
