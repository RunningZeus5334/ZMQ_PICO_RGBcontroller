#ifndef PICO_H
#define PICO_H

///#include <iostream>
#include <ostream>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

class Pico
{
public:
    Pico(int id) : id(id), stopFlag(false), thread(&Pico::run, this) {
         std::cout << "Thread " << id << " started." << std::endl;
    }

    ~Pico() {
        stop();
        if (thread.joinable()) {
            thread.join();
        }
        std::cout << "Thread " << id << " joined." << std::endl;
    }
    void Start(std::thread ,int id, int led);
    void Bentrernet_service(int id, int led);
    void stop() {
        stopFlag.store(true);
    }

private:
    int id;
    int led = 1;
    std::atomic<bool> stopFlag;
    std::thread thread;

    void run() {

        Pico::Bentrernet_service(id,led);

    }
};



#endif // PICO_H
