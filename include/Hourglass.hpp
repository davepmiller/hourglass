#ifndef CLOCK_HPP
#define CLOCK_HPP


#include <chrono>

#include "Timer.hpp"


namespace hourglass {


std::chrono::system_clock::time_point now();


template< typename T >
std::chrono::system_clock::rep since(
        std::chrono::system_clock::time_point timePoint )
{
    return std::chrono::duration_cast< T >( now() - timePoint ).count();
}


template< typename T >
void sleep( T duration )
{
    std::this_thread::sleep_for( duration );
}


template <typename... Args>
auto seconds( Args && ... args )
    -> decltype( std::chrono::seconds( std::forward< Args >( args ) ... ) )
{
    return std::chrono::seconds( std::forward< Args >( args ) ... );
}


template <typename... Args>
auto milliseconds( Args && ... args )
    -> decltype( std::chrono::milliseconds( std::forward< Args >( args ) ... ) )
{
    return std::chrono::milliseconds( std::forward< Args >( args ) ... );
}


template <typename... Args>
auto microseconds( Args && ... args )
    -> decltype( std::chrono::microseconds( std::forward< Args >( args ) ... ) )
{
    return std::chrono::microseconds( std::forward< Args >( args ) ... );
}


}


#endif // CLOCK_HPP
