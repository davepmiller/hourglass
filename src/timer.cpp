#include <iostream>

#include "timer.hpp"


using namespace hourglass;


static void notify_start_failure() {
    std::cerr << "Reapeater::start() failed - did you call "
                 "Repeater::connect()?"
              << std::endl;
}


static void launch_repeater( Repeater & repeater, unsigned ms_freq ) {
    repeater.is_connected() ?
                repeater.launch_async( ms_freq ) : notify_start_failure();
}


Timer::Timer() noexcept
    :
    _repeater( nullptr )
{
    // empty
}


Timer::~Timer() {
    stop();
}


void Timer::start( unsigned msFrequency ) {
    _repeater ? launch_repeater(
                    *_repeater.get(), msFrequency ) : notify_start_failure();
}


void Timer::stop() {
    if( _repeater ) {
        if( _repeater->is_running() ) {
            _repeater->stop();
        }
    }
}
