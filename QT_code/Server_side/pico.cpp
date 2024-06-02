#include "pico.h"
#include <zmq.hpp>
#include <QString>
#include <regex>

QTcpSocket Server;

void Pico::Bentrernet_service() {
    zmq::context_t context(1);

    try {
        int led = 0;
        //setup to benternet
        zmq::socket_t subscriber(context, ZMQ_SUB);
        zmq::socket_t ventilator(context, ZMQ_PUSH);

        subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");
        ventilator.connect("tcp://benternet.pxl-ea-ict.be:24041");

        //dynamic subsribtion
        std::string send;
        std::string subscription = "RGB_Controller?>Pico";
        subscriber.setsockopt(ZMQ_SUBSCRIBE, subscription.c_str(), subscription.size());
        //subscriber.setsockopt(ZMQ_SUBSCRIBE, "RGB_Controller?>Pico1>Led1>", 27);
        std::cout <<  subscription    << std::endl;
        zmq::message_t msgb;
        //data format
        std::regex rgx(R"(r (\d{1,3}) g (\d{1,3}) b (\d{1,3}))");
        std::regex ledRgx(R"(Led(\d+))");

        std::smatch match;
        std::smatch ledMatch;

        while (subscriber.connected() ) {
            subscriber.recv(&msgb);
            std::string received_message(static_cast<char*>(msgb.data()), msgb.size());

            //Data validation led
            if (std::regex_search(received_message, ledMatch, ledRgx)) {
                led = std::stoi(ledMatch[1]);
            } else {
                std::cerr << "Error: LED number not found" << std::endl;

            }
            //Data validation rgb
            if (std::regex_search(received_message, match, rgx)) {
                int r = std::stoi(match[1]);
                int g = std::stoi(match[2]);
                int b = std::stoi(match[3]);

                if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255) {
                    // Valid RGB values received
                    send ="RGB_Controller!>Pico1> Led" + std::to_string(led)+ " changedto: r=" + std::to_string(r) + " g=" + std::to_string(g) + " b=" + std::to_string(b);
                    ventilator.send(send.c_str(), send.size());
                    std::cout << send.c_str() << std::endl;
                    Pico::Send(led,r,g,b);
                    // Implement logic to set the LED colors using r, g, b
                }
            }
            ventilator.send("invalid syntax. syntax should be for example: r 2 g 180 b 255 ", 62);
            // End of data validation
        }
    } catch (zmq::error_t &ex) {


    }
}


void Pico::Send(int i, int r, int g, int b){
    Server.connectToHost("192.168.2.13",(uint) 1234);
    if(!Server.waitForConnected(5000))
    {
        qDebug() << "Error: " << Server.errorString();
    }
    else{
        qDebug() << "Connected to server";
    }


    std::string send ="i=" + std::to_string(i)+ " r=" + std::to_string(r) + " g=" + std::to_string(g) + " b=" + std::to_string(b) + "\n";
    QByteArray dataToSend = QByteArray::fromStdString(send);
    Server.write(dataToSend);
    qDebug() << "Sended" << send;
    Server.flush();
    Server.disconnect();

}

