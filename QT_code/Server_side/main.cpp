#include <zmq.hpp>
#include <QDebug>
#include "pico.h"
#include "QTcpSocket"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

zmq::context_t context(1);

int main( void )
{

    //int port = 1234;
    Pico pico;
    pico.Bentrernet_service();

    return 0;
}


