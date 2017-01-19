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

    void start( unsigned ms_freq );

    void stop();

    template< typename T >
    void connect( T & observer, void( T::* )() );

    template< typename T >
    static void delayed_function_call(
            T & observer, void( T::* )(), unsigned msDelay );


private:

    std::unique_ptr< Repeater > _repeater;

};


static void execute_after_delay(
        std::function< void() > functionToCall, unsigned msDelay )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( msDelay ) );

    functionToCall();
}


template< typename T >
void Timer::connect( T & functionOwner, void( T::*functionName )() )
{
    _repeater = std::unique_ptr< Repeater >( new Repeater );

    _repeater->set_function( std::bind( functionName, &functionOwner ) );
}


template< typename T >
void Timer::delayed_function_call(
        T & functionOwner, void( T::*functionName )(), unsigned msDelay )
{
    std::thread{
        execute_after_delay,
        std::bind( functionName, &functionOwner ),
        msDelay }
    .detach();
}


}


#endif // TIMER_HPP
