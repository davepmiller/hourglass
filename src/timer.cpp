#include <iostream>

#include "timer.hpp"


using namespace hourglass;


static void notifyStartFailure() {
    std::cerr << "Reapeater::start() failed - did you call "
                 "Repeater::connect()?"
              << std::endl;
}


static void launchRepeater( Repeater & repeater, unsigned msFrequency ) {
    repeater.isConnected() ?
                repeater.launchAsync( msFrequency ) : notifyStartFailure();
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
    _repeater ? launchRepeater(
                    *_repeater.get(), msFrequency ) : notifyStartFailure();
}


void Timer::stop() {
    if( _repeater ) {
        if( _repeater->isRunning() ) {
            _repeater->stop();
        }
    }
}
