[![Build Status](https://travis-ci.org/DaveyLaser/hourglass.png)](https://travis-ci.org/DaveyLaser/hourglass)
[![Coverage Status](https://coveralls.io/repos/github/DaveyLaser/hourglass/badge.svg?branch=master)](https://coveralls.io/github/DaveyLaser/hourglass?branch=master)
[![License](https://img.shields.io/badge/license-%20BSD--3-blue.svg)](../master/LICENSE)

# hourglass
C++ Async Timer

## Install
```
$ git clone https://github.com/DaveyLaser/hourglass.git
$ cd hourglass
$ mkdir build && cd build
$ cmake ..
$ make
```

## Use
```bash
$ cd examples/hello
$ mkdir build && cd build && cmake .. && make
$ ./hello
```
### From example/hello
```c++
#include <iostream>
#include "timer.hpp"

struct Observer
{
    Observer() : count( 0 ) {}
    int count;
    void cb () 
    {
        std::cout << "Hello world, for the " << count++ << "th time!\n";
    }
};

int main()
{
    Observer o;
    hourglass::Timer t;
    t.connect( o, &Observer::cb );
    t.start( 200 /*ms*/ );
    hourglass::sleep( hourglass::seconds( 1 ) );
}
```
