#ifndef PROP_H
#define PROP_H

struct Prop
{
  enum ePropType {NONE, LIGHT_A, LIGHT_D, TEMP, HUM};
  enum ePropMode {READ, WRITE, READ_WRITE};

  ePropType type;
  ePropMode mode;
  uint8_t * value;
  uint8_t valueSize;

  Prop()
  {
      type = NONE;
      mode = READ;
      value = 0;
      valueSize = 0;
  }
};

template<typename T>
Prop * propFactory(const Prop::ePropType &t, const Prop::ePropMode &m, const T &v)
{
  Prop * p = new Prop();
  p->type = t;
  p->mode = m;
  p->valueSize = sizeof(T);
  p->value = malloc(p->valueSize);
  memset(p->value,0,p->valueSize);
  return p;
}

#endif //PROP_H
