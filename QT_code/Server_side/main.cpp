#include <iostream>
#include <zmq.hpp>
#include <thread>
#include "pico.h"
#include "tcpclient.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif
TcpClient client;
zmq::context_t context(1);

int main( void )
{
    int port = 1234;
    Pico pico(1);
    Pico pico2(2);
    Pico pico3(3);

    client.firstConnect("192.168.2.19", port);

    while (true) {

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    pico.stop();
    pico2.stop();
    pico3.stop();
    return 0;
}


