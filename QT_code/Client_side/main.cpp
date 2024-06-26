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
        //zmq::socket_t subscriber( context, ZMQ_SUB );
//      ventilator.connect( "tcp://192.168.2.28:55978" );
//		ventilator.connect( "tcp://localhost:24041" );
        ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
        //subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );

        //zmq::message_t * msg = new zmq::message_t();
        //subscriber.setsockopt( ZMQ_SUBSCRIBE,  "prime", 6 );

		while( ventilator.connected() )
		{

            sleep( 5000);
            ventilator.send( "RGB_Controller?>Pico1>Leds>r 2 g 180 b 255", 44 );
            std::cout << "Pushed : [RGB_Controller?>Color" << std::endl;
            sleep( 5000);
            ventilator.send( "RGB_Controller?>Pico1>Leds>r 255 g 10 b 5", 44 );
            std::cout << "Pushed : [RGB_Controller?>Color" << std::endl;
            sleep( 5000);
            ventilator.send( "RGB_Controller?>Pico1>Leds>r 60 g 255 b 90", 44 );
            std::cout << "Pushed : [RGB_Controller?>Color" << std::endl;
            sleep( 5000);
            ventilator.send( "RGB_Controller?>Pico1>Led1>r 255 g 50 b 0", 44 );
            std::cout << "Pushed : [RGB_Controller?>Color" << std::endl;
            sleep( 5000);
            ventilator.send( "RGB_Controller?>Pico1>Led2>r 0 g 90 b 150", 44 );
            std::cout << "Pushed : [RGB_Controller?>Color" << std::endl;
            sleep( 5000);
            ventilator.send( "RGB_Controller?>Pico1>Led3>r 160 g 0 b 255", 44 );
            std::cout << "Pushed : [RGB_Controller?>Color" << std::endl;

                    }
	}
	catch( zmq::error_t & ex )
	{
		std::cerr << "Caught an exception : " << ex.what();
	}

    return 0;
}
