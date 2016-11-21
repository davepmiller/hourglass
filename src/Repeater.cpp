#include <iostream>

#include "Repeater.hpp"
#include "Hourglass.hpp"


using namespace hourglass;


static void notifyThreadFailure()
{
    std::cerr << "Repeater::start() failed - system could not launch "
                 "thread."
              << std::endl;
}


static void joinThread( std::future< void > & future )
{
    if( future.valid() )
    {
        future.get();
    }
}


static void execute(
        const std::atomic_bool * repeating,
        const std::function< void() > & methodToCall,
        unsigned msFrequency )
{
    while( *repeating )
    {
        hourglass::sleep( std::chrono::milliseconds( msFrequency ) );

        methodToCall();
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


void Repeater::setFunction( std::function<void ()> function )
{
    _function = function;
}


void Repeater::launchAsync( unsigned msFrequency )
{
    try
    {
        _repeating = true;

        _repeaterFuture = std::async(
                    std::launch::async,
                    execute,
                    &_repeating,
                    _function,
                    msFrequency );
    }
    catch( ... )
    {
        notifyThreadFailure();
    }
}


bool Repeater::isRunning() const
{
    return _repeating;
}


bool Repeater::isConnected() const
{
    return _function ? true : false;
}


void Repeater::stop()
{
    if( _repeating )
    {
        _repeating = false;

        joinThread( _repeaterFuture );
    }
}
