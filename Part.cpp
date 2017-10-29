#include "Part.h"
#include "Prop.h"
#include "Message.h"

Part::Part()
{
  propCount = 0;
}

uint8_t Part::getPropCount() const
{
  return propCount;
}

bool Part::readProp(const uint8_t & idx, Message &msg)
{
  if(idx>=propCount) return false;
  Prop * prop = propArray[idx];
  msg.type = MSG_READ;
  msg.propId = idx;
  msg.propType = prop->type;
  msg.propMode = prop->mode;
  msg.valueSize = prop->valueSize;
  memcpy(&msg.value, prop->value, msg.valueSize);
  return true;
}

void Part::updateProps()
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#if defined (ARDUINO)
Part_Light_LM393::Part_Light_LM393(const uint8_t &pin_a, const uint8_t &pin_d)
{
  m_pin_a = pin_a;
  m_pin_d = pin_d;

  propCount = 2;
  propArray = new Prop*[propCount];

  propArray[0] = propFactory<int>(Prop::LIGHT_A, Prop::READ, 0);
  propArray[1] = propFactory<bool>(Prop::LIGHT_D, Prop::READ, false);
}

Part_Light_LM393::~Part_Light_LM393()
{
  for(int i=0; i<propCount; i++) delete propArray[i];
  delete propArray;
}

void Part_Light_LM393::updateProps()
{
  int light_a = analogRead(m_pin_a);
  *(int*)(propArray[0]->value) = light_a;

  bool light_d = digitalRead(m_pin_d);
  *(bool*)(propArray[1]->value) = light_d;
}
#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#if defined (ARDUINO)
Part_DHT::Part_DHT(uint8_t pin, uint8_t type)
{
  dht = new DHT(pin,type);
  dht->begin();

  propCount = 2;
  propArray = new Prop*[propCount];

  propArray[0] = propFactory<float>(Prop::TEMP, Prop::READ, 0.0);
  propArray[1] = propFactory<float>(Prop::HUM, Prop::READ, 0.0);
}

Part_DHT::~Part_DHT()
{
  delete dht;
}

void Part_DHT::updateProps()
{
  float temp = dht->readTemperature();
  if (isnan(temp)) temp = 0;
  *(float*)(propArray[0]->value) = temp;

  float hum = dht->readHumidity();
  if (isnan(hum)) hum = 0;
  *(float*)(propArray[1]->value) = hum;
}
#endif
