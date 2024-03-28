#ifndef RGB_CONTROL_H
#define RGB_CONTROL_H

class RGB_Control
{
public:
    RGB_Control();
    // met deze functies kun je de rgb led aanpassen van kleur -> future: pwm kunnen instellen
    void change_red();
    void change_green();
    void change_blue();

};

#endif // RGB_CONTROL_H

