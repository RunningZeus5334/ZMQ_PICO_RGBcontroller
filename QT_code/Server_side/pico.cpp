#include "pico.h"
#include <zmq.hpp>
#include <QString>
#include <iostream>

Pico::Pico(char thrd) {
    zmq::context_t context(1);
    // listens to benternet for colorchange request
    zmq::socket_t subscriber( context, ZMQ_SUB );
    zmq::socket_t ventilator( context, ZMQ_PUSH );

    subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
    ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );

    QString subscribe = ("RGB_Controller?>Pico");
    QString myNumber = QString::number(thrd);

    subscribe += myNumber;
    subscriber.setsockopt( ZMQ_SUBSCRIBE, &subscribe, sizeof(subscribe) );
    std::cout << &subscribe << std::endl;

    zmq::message_t * msgr = new zmq::message_t();

    while( subscriber.connected() ){


        subscriber.recv( msgr );

        ventilator.send( "RGB_Controller!>Color changed to red", 37 );



    }

}


void Colerchange(unsigned char R, unsigned char G, unsigned char B, unsigned char N ){

   // sends rgb data to the Pico W using Tcp
}
