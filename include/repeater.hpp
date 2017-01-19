#ifndef REPEATER_HPP
#define REPEATER_HPP


#include <functional>
#include <chrono>
#include <atomic>
#include <future>

namespace hourglass {


class Repeater
{

public:

    Repeater();

    void set_function( std::function< void() > function );

    void launch_async( unsigned msFrequency );

    void stop();

    bool is_running() const;

    bool is_connected() const;


private:

    std::function< void( void ) > function_;

    std::future< void > repeater_future_;

    std::atomic_bool repeating_;

};


}


#endif // REPEATER_HPP
