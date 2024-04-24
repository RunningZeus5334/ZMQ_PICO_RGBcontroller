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
            ventilator.send( "RGB_Controller?>Color>Red", 26 );
            std::cout << "Pushed : [RGB_Controller?>Color>Red]" << std::endl;

            sleep( 5000);
            ventilator.send( "RGB_Controller?>Color>Green", 28 );
            std::cout << "Pushed : [RGB_Controller?>Color>Green]" << std::endl;

            sleep( 5000);
            ventilator.send( "RGB_Controller?>Color>Blue", 27 );
            std::cout << "Pushed : [RGB_Controller?>Color>Blue]" << std::endl;

            sleep( 5000);
            ventilator.send( "RGB_Controller?>Color>Green", 28 );
            std::cout << "Pushed : [RGB_Controller?>Color>Green]" << std::endl;

            sleep( 5000);
            ventilator.send( "RGB_Controller?>Color>Blue", 27 );
            std::cout << "Pushed : [RGB_Controller?>Color>Blue]" << std::endl;

            sleep( 5000);
            ventilator.send( "RGB_Controller?>Color>Red", 26 );
            std::cout << "Pushed : [RGB_Controller?>Color>Red]" << std::endl;
                    }
	}
	catch( zmq::error_t & ex )
	{
		std::cerr << "Caught an exception : " << ex.what();
	}

	return 0;
}
