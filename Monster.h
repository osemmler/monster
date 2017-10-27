#ifndef MONSTER_H
#define MONSTER_H

#include "Monster_config.h"
#include "Part.h"
#include "Message.h"

class Monster
{
public:
    Monster();
    ~Monster();

    void setup();
    void readAllProps();
    bool readMessage(Message &msg);

protected:
    uint8_t partCount;
    Part ** partArray;

private:
    int monsterId;
    uint8_t * pipeR;
    uint8_t * pipeW;

    uint8_t buffIdx;
    uint8_t buff[MSG_SIZE];

#if defined(ARDUINO) || defined(RASPBERRY)
    RF24 * radio;
#elif defined(DESKTOP)
    int tty_fd;
#endif
};

#endif //MONSTER_H
