#include <iostream>
#include <zmq.hpp>
#include <thread>
#include "rgb_control.h"
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




        //zmq::socket_t subscriber( context, ZMQ_SUB );


        //ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
        //subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );

        //subscriber.setsockopt( ZMQ_SUBSCRIBE,  "RGB_Controller?>Color>Red", 26 );

        //zmq::message_t * msg = new zmq::message_t();
        std::string message;

        //ventilator.connected();

        std::thread first (recv_red);
        std::thread second (recv_green);
        std::thread third (recv_blue);


        first.join();
        second.join();
        third.join();
       /* while( subscriber.connected() ){
            std::cout << "TEST" << std::endl;
            subscriber.recv( msg );
            message = std::string( (char*) msg->data(), msg->size() );
            if(msg != nullptr){
                std::cout << "Received : [" << std::string( (char*) msg->data(), msg->size() ) << "]" << std::endl;
                ventilator.send( "RGB_Controller!>Color changed to red", 37 );
            }

            if(message == "RGB_Controller?>Color>Red"){
                Controller.change_red();
                ventilator.send( "RGB_Controller!>Color changed to red", 37 );

            }
            else if (message == "RGB_Controller?>Color>Green") {
                 Controller.change_green();
                ventilator.send( "RGB_Controller!>Color changed to green", 39 );

            }
            else if (message == "RGB_Controller?>Color>Blue") {
                 Controller.change_blue();
                ventilator.send( "RGB_Controller>Color changed to blue", 38 );

            }
        }*/

       /* while( subscriber.connected() ){

            subscriber.setsockopt( ZMQ_SUBSCRIBE,  "RGB_Controller?>Color>Red", 26 );
            subscriber.recv( msg );
            if(msg != nullptr){
                std::cout << "Received : [" << std::string( (char*) msg->data(), msg->size() ) << "]" << std::endl;
                ventilator.send( "RGB_Controller!>Color changed to red", 37 );
                Controller.change_red();
            }

            subscriber.setsockopt( ZMQ_SUBSCRIBE,  "RGB_Controller?>Color>Green", 28 );
            subscriber.recv( msg );
            if(msg != nullptr){
                std::cout << "Received : [" << std::string( (char*) msg->data(), msg->size() ) << "]" << std::endl;
                ventilator.send( "RGB_Controller!>Color changed to green", 39 );
                Controller.change_green();
            }

            subscriber.setsockopt( ZMQ_SUBSCRIBE,  "RGB_Controller?>Color>Blue", 27 );
            subscriber.recv( msg );
            if(msg != nullptr){
                std::cout << "Received : [" << std::string( (char*) msg->data(), msg->size() ) << "]" << std::endl;
                ventilator.send( "RGB_Controller!>Color changed to blue", 38 );
                Controller.change_blue();
            }
        }*/


        /*ventilator.connected();
        sleep( 1000 );
        ventilator.send( "example>quest?>Slave Master Thomas Fokkema>", 44 );
        std::cout << "example>quest?>Slave Master Thomas Fokkema>" << std::endl;

        subscriber.connected();

        subscriber.recv( msg );

        std::cout << "Received : [" << std::string( (char*) msg->data(), msg->size() ) << "]" << std::endl;
        */


    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what();
    }

    return 0;
}





    void recv_red()
    {

        std::cout << "TEST_red" << std::endl;

        zmq::socket_t subscriber_red( context, ZMQ_SUB );
        zmq::socket_t ventilator_red( context, ZMQ_PUSH );

        subscriber_red.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
        ventilator_red.connect( "tcp://benternet.pxl-ea-ict.be:24041" );

        subscriber_red.setsockopt( ZMQ_SUBSCRIBE,  "RGB_Controller?>Color>Red", 26 );
        ventilator_red.connected();

        zmq::message_t * msgr = new zmq::message_t();

        while( subscriber_red.connected() ){

            subscriber_red.setsockopt( ZMQ_SUBSCRIBE,  "RGB_Controller?>Color>Red", 26 );
            subscriber_red.recv( msgr );

            std::cout << "Received : [" << std::string( (char*) msgr->data(), msgr->size() ) << "]" << std::endl;
            ventilator_red.send( "RGB_Controller!>Color changed to red", 37 );
            Controller.change_red();


        }
    }

    void recv_green()
    {

        std::cout << "TEST_green" << std::endl;

        zmq::socket_t subscriber_green( context, ZMQ_SUB );
        zmq::socket_t ventilator_green( context, ZMQ_PUSH );

        subscriber_green.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
        ventilator_green.connect( "tcp://benternet.pxl-ea-ict.be:24041" );

        subscriber_green.setsockopt( ZMQ_SUBSCRIBE,  "RGB_Controller?>Color>Green", 28 );
        ventilator_green.connected();

        zmq::message_t * msgg = new zmq::message_t();

        while( subscriber_green.connected() ){

            subscriber_green.setsockopt( ZMQ_SUBSCRIBE,  "RGB_Controller?>Color>Green", 28 );
            subscriber_green.recv( msgg );

            std::cout << "Received : [" << std::string( (char*) msgg->data(), msgg->size() ) << "]" << std::endl;
            ventilator_green.send( "RGB_Controller!>Color changed to green", 38 );
            Controller.change_green();


        }
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
