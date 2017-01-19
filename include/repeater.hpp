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

    void setFunction( std::function< void() > function );

    void launchAsync( unsigned msFrequency );

    void stop();

    bool isRunning() const;

    bool isConnected() const;


private:

    std::function< void( void ) > _function;

    std::future< void > _repeaterFuture;

    std::atomic_bool _repeating;

};


}


#endif // REPEATER_HPP
