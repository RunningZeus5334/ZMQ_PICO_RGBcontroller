#include <iostream>
#include <zmq.hpp>
#include <thread>
#include "rgb_control.h"
#include "pico.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

void recv_red();
void recv_green();
void recv_blue();



RGB_Control Controller = *new RGB_Control;
zmq::context_t context(1);


int main( void )
{
    try
    {


        //std::thread third (recv_blue);

        //third.join();
        char thrd = 1;

        Pico Pico1(thrd);
        Pico1::Colerchange();
    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what();
    }

    return 0;
}


    void recv_blue()
    {

        std::cout << "TEST_blue" << std::endl;

        zmq::socket_t subscriber_blue( context, ZMQ_SUB );
        zmq::socket_t ventilator_blue( context, ZMQ_PUSH );

        subscriber_blue.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
        ventilator_blue.connect( "tcp://benternet.pxl-ea-ict.be:24041" );

        subscriber_blue.setsockopt( ZMQ_SUBSCRIBE,  "RGB_Controller?>Color>Blue", 27 );
        ventilator_blue.connected();

        zmq::message_t * msgb = new zmq::message_t();

        while( subscriber_blue.connected() ){

            subscriber_blue.setsockopt( ZMQ_SUBSCRIBE,  "RGB_Controller?>Color>Blue", 27 );
            subscriber_blue.recv( msgb );

            std::cout << "Received : [" << std::string( (char*) msgb->data(), msgb->size() ) << "]" << std::endl;
            ventilator_blue.send( "RGB_Controller!>Color changed to blue", 38 );
            Controller.change_blue();


        }
    }
