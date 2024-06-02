#ifndef PICO_H
#define PICO_H

///#include <iostream>

#include <ostream>
#include <iostream>

#include <atomic>
#include <chrono>
#include "QTcpSocket"

class Pico
{
public:
    Pico(){}
    void Bentrernet_service();
    void Send(int i, int r, int g, int b);
private:


};



#endif // PICO_H
