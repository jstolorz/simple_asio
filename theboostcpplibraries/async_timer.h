#pragma once

#include <asio.hpp>
#include <chrono>
#include <iostream>

using namespace asio;

int run_example() {

    io_service service1;
    io_service service2;

    steady_timer timer1{service1, std::chrono::seconds{3}};

    timer1.async_wait([](const error_code &ec) {
        std::cout << "timer1 3 sec\n";
    });

    steady_timer timer2{service2, std::chrono::seconds{3}};

    timer2.async_wait([](const error_code &ec) {
        std::cout << "timer2 3 sec\n";
    });

   thread thread1{[&service1](){ service1.run();}};
   thread thread2{[&service2](){ service2.run();}};

   thread1.join();
   thread2.join();


    return 0;
}