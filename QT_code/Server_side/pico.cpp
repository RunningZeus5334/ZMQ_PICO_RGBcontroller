#include "pico.h"
#include <zmq.hpp>
#include <QString>
#include <regex>
#include <tcpclient.h>

void Pico::Bentrernet_service(int id,int led) {
    zmq::context_t context(1);

    try {

        //setup to benternet
        zmq::socket_t subscriber(context, ZMQ_SUB);
        zmq::socket_t ventilator(context, ZMQ_PUSH);

        subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");
        ventilator.connect("tcp://benternet.pxl-ea-ict.be:24041");

        std::cout << "Thread " << id << " Ready!" << std::endl;
        //dynamic subsribtion
        std::string send;
        std::string subscription = "RGB_Controller?>Pico" + std::to_string(id) + ">Led" + std::to_string(led) + ">";
        subscriber.setsockopt(ZMQ_SUBSCRIBE, subscription.c_str(), subscription.size());
        //subscriber.setsockopt(ZMQ_SUBSCRIBE, "RGB_Controller?>Pico1>Led1>", 27);
        std::cout <<  subscription    << std::endl;
        zmq::message_t msgb;
        //data format
        std::regex rgx(R"(r (\d{1,3}) g (\d{1,3}) b (\d{1,3}))");

        while (subscriber.connected()&& !stopFlag.load()) {
            subscriber.recv(&msgb);
            std::string received_message(static_cast<char*>(msgb.data()), msgb.size());

            //Data validation
            std::smatch match;
            if (std::regex_search(received_message, match, rgx)) {
                int r = std::stoi(match[1]);
                int g = std::stoi(match[2]);
                int b = std::stoi(match[3]);
                //data is set in r g b. TODO: make function to send to pico
                if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255) {
                    // Valid RGB values received
                    send ="RGB_Controller!>Pico" + std::to_string(id)+ ">changedto: r=" + std::to_string(r) + " g=" + std::to_string(g) + " b=" + std::to_string(b);
                    ventilator.send(send.c_str(), send.size());
                    std::cout << send.c_str() << std::endl;
                    // Implement logic to set the LED colors using r, g, b
                }
            }
            ventilator.send("invalid syntax. syntax should be for example: r 2 g 180 b 255 ", 62);
            // End of data validation
        }
    } catch (zmq::error_t &ex) {
        stop();
    }
}
