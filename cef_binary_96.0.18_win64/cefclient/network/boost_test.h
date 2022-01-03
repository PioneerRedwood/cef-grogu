#pragma once
#include <malloc.h>         // "_alloca" can't find at boost/socket_ops.ipp
#include "boost/asio.hpp" 

namespace client {
namespace network {
class LittleTimer {
public:
    LittleTimer(uint32_t delay)
        : delay_(delay)
    {}

    void Start() {
        context_.run();

        Tick();
    }

private:
    void Tick() {
        // when timer execute 10 times, exit
        if (count_++ > 10) {
            return;
        }

        timer_.expires_from_now(boost::posix_time::seconds(delay_));
        timer_.async_wait(
            [&](auto& ec) {
                if (ec) {
                    return;
                }

                //std::cout << "hello, new year !\n";

                // call it again
                Tick();
            }
        );
    }
private:
    boost::asio::io_context context_;
    boost::asio::deadline_timer timer_{context_};
    uint32_t delay_;
    uint32_t count_ = 0;
};


}
}