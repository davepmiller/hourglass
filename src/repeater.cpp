#include <iostream>

#include "repeater.hpp"
#include "hourglass.hpp"
#include "timer.hpp"


using namespace hourglass;


static void notifyThreadFailure( const std::exception & e ) {
    std::cerr << "Repeater::start() failed - system could not launch "
                 "thread.\n"
              << e.what() << std::endl;
}


static void joinThread( std::future< void > & future ) {
    if( future.valid() ) {
        future.get();
    }
}


static void repeat(
        const std::atomic_bool * repeating,
        const std::function< void() > & methodToCall,
        unsigned msFrequency ) {
    while( *repeating ) {
        executeAfterDelay( methodToCall, msFrequency );
    }
}


Repeater::Repeater()
    :
    _function(),
    _repeaterFuture(),
    _repeating( false )
{
    // empty
}


void Repeater::setFunction( std::function< void() > function ) {
    _function = function;
}


void Repeater::launchAsync( unsigned msFrequency ) {
    try {
        _repeating = true;
        _repeaterFuture = std::async(
                    std::launch::async,
                    repeat,
                    &_repeating,
                    _function,
                    msFrequency );
    } catch( std::exception & e ) {
        notifyThreadFailure( e );
    }
}


bool Repeater::isRunning() const {
    return _repeating;
}


bool Repeater::isConnected() const {
    return _function ? true : false;
}


void Repeater::stop() {
    if( _repeating )
    {
        _repeating = false;

        joinThread( _repeaterFuture );
    }
}
