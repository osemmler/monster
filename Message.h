#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>

#define MSG_SIZE    32
#define MSG_READ    0x80

union Message
{
  uint8_t data[MSG_SIZE];
  struct
  {
    uint8_t type;
    uint8_t monsterId;
    uint8_t partId;
    uint8_t propId;
    uint8_t propType;
    uint8_t propMode;
    uint8_t valueSize;
    uint8_t value; // use as pointer
  };

  Message()
  {
    memset(data, 0, MSG_SIZE);
  }
};

#endif
