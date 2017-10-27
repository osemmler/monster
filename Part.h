#ifndef PART_H
#define PART_H

#include "Monster_config.h"
#include "Message.h"

class Prop;

class Part
{
public:
  Part();

  uint8_t getPropCount() const;
  virtual void updateProps();

  bool readProp(const uint8_t & idx, Message &msg);

protected:
  uint8_t propCount;
  Prop ** propArray;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#if defined (ARDUINO)
class Part_Light_LM393 : public Part
{
public:
  Part_Light_LM393(const uint8_t &pin_a, const uint8_t &pin_d);
  ~Part_Light_LM393();

  virtual void updateProps();

private:
  uint8_t m_pin_a;  //analog pin
  uint8_t m_pin_d;  //digital pin
};
#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#if defined (ARDUINO)
#include <DHT.h>
class Part_DHT : public Part
{
public:
  Part_DHT(uint8_t pin, uint8_t type);
  ~Part_DHT();

  virtual void updateProps();

private:
  DHT * dht;
};
#endif

#endif //PART_H