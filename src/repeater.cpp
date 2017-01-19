#include <iostream>

#include "repeater.hpp"
#include "hourglass.hpp"
#include "timer.hpp"


using namespace hourglass;


static void notify_thread_failure( const std::exception & e ) {
    std::cerr << "Repeater::start() failed - system could not launch "
                 "thread.\n"
              << e.what() << std::endl;
}


static void join_thread( std::future< void > & future ) {
    if( future.valid() ) {
        future.get();
    }
}


static void repeat(
        const std::atomic_bool * repeating,
        const std::function< void() > & methodToCall,
        unsigned msFrequency ) {
    while( *repeating ) {
        execute_after_delay( methodToCall, msFrequency );
    }
}


Repeater::Repeater()
    :
    function_(),
    repeater_future_(),
    repeating_( false )
{
    // empty
}


void Repeater::set_function( std::function< void() > function ) {
    function_ = function;
}


void Repeater::launch_async( unsigned msFrequency ) {
    try {
        repeating_ = true;
        repeater_future_ = std::async(
                    std::launch::async,
                    repeat,
                    &repeating_,
                    function_,
                    msFrequency );
    } catch( std::exception & e ) {
        notify_thread_failure( e );
    }
}


bool Repeater::is_running() const {
    return repeating_;
}


bool Repeater::is_connected() const {
    return function_ ? true : false;
}


void Repeater::stop() {
    if( repeating_ ) {
        repeating_ = false;
        join_thread( repeater_future_ );
    }
}
