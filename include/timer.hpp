#ifndef TIMER_HPP
#define TIMER_HPP


#include <memory>

#include "repeater.hpp"
#include "hourglass.hpp"


namespace hourglass {


class Timer
{

public:

    Timer() noexcept;

    ~Timer();

    void start( unsigned msFrequency );

    void stop();

    template< typename T >
    void connect( T & observer, void( T::* )() );

    template< typename T >
    static void delayedFunctionCall(
            T & observer, void( T::* )(), unsigned msDelay );


private:

    std::unique_ptr< Repeater > _repeater;

};


static void executeAfterDelay(
        std::function< void() > functionToCall, unsigned msDelay )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( msDelay ) );

    functionToCall();
}


template< typename T >
void Timer::connect( T & functionOwner, void( T::*functionName )() )
{
    _repeater = std::unique_ptr< Repeater >( new Repeater );

    _repeater->setFunction( std::bind( functionName, &functionOwner ) );
}


template< typename T >
void Timer::delayedFunctionCall(
        T & functionOwner, void( T::*functionName )(), unsigned msDelay )
{
    std::thread{
        executeAfterDelay,
        std::bind( functionName, &functionOwner ),
        msDelay }
    .detach();
}


}


#endif // TIMER_HPP
