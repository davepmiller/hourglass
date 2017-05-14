#include <chrono>
#include "gtest/gtest.h"
#include "timer.hpp"
#include "hourglass.hpp"


TEST( Timer, start_stop )
{
    struct Observer
    {
        bool called = false;
        void cb(){
            called = true;
        }
    };
    Observer o;
    hourglass::Timer t;
    t.connect( o, &Observer::cb );
    t.start( 1 );
    usleep( 1500 );
    t.stop();
    ASSERT_EQ( o.called, true );
}

TEST( Timer, delayed_function_call )
{
    struct Observer
    {
        bool called = false;
        void cb(){
            called = true;
        }
    };
    Observer o;
    hourglass::Timer::delayed_function_call( o, &Observer::cb, 1 );
    usleep( 1500 );
    ASSERT_EQ( o.called, true );
}

TEST( Timer, now )
{
    auto start = hourglass::now();
    auto stop = hourglass::now();
    std::chrono::duration<double> diff = stop-start;
    ASSERT_LT( diff.count(), 1.0 );
}