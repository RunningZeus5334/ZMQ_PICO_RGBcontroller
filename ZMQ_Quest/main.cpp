#include <iostream>
#include <zmq.hpp>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

int main( void )
{
    try
    {
        zmq::context_t context(1);

        //Outgoing message go out through here
        zmq::socket_t ventilator( context, ZMQ_PUSH );
        zmq::socket_t subscriber( context, ZMQ_SUB );
        //        ventilator.connect( "tcp://192.168.2.26:61577" );
        //		ventilator.connect( "tcp://localhost:24041" );
        ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
        subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
        subscriber.setsockopt( ZMQ_SUBSCRIBE,  "example>quest!>Slave Master Thomas Fokkema>", 43 );

        zmq::message_t * msg = new zmq::message_t();


        ventilator.connected();
        sleep( 1000 );
        ventilator.send( "example>quest?>Slave Master Thomas Fokkema>", 44 );
        std::cout << "example>quest?>Slave Master Thomas Fokkema>" << std::endl;

        subscriber.connected();
        subscriber.recv( msg );
        std::cout << "Received : [" << std::string( (char*) msg->data(), msg->size() ) << "]" << std::endl;
        subscriber.setsockopt( ZMQ_SUBSCRIBE,  "example>Begijnenstraat 42!>Slave Master Thomas Fokkema>", 55 );
        ventilator.send( "example>Begijnenstraat 42?>Slave Master Thomas Fokkema>social media>4a523217d62a3c7a5ac3233a3ab5b27cfd57040a>#OhMyGod#WhatTheFuck>", 131 );
        subscriber.connected();
        subscriber.recv( msg );
        std::cout << "Received : [" << std::string( (char*) msg->data(), msg->size() ) << "]" << std::endl;

    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what();
    }

    return 0;
}
