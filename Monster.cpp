#include "Monster.h"

Monster::Monster()
{
    partCount = 0;
    buffIdx = 0;
}

Monster::~Monster()
{
    for(int i=0; i<partCount; i++) delete partArray[i];
    delete partArray;

#if defined(ARDUINO) || defined(RASPBERRY)
    delete radio;
#endif
}

void Monster::setup()
{
    // start serial communication
#if defined (ARDUINO)
    Serial.begin(9600);
#elif defined (DESKTOP)
    struct termios tio;
    const char * ttyPort = "/dev/ttyUSB0";

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL; // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    tty_fd=open(ttyPort, O_RDWR | O_NONBLOCK);
    cfsetospeed(&tio,B9600);
    cfsetispeed(&tio,B9600);
    tcsetattr(tty_fd,TCSANOW,&tio);
#endif

#if defined(ARDUINO) || defined(RASPBERRY)
    // start wireless communication
    radio = new RF24(9,10);
    radio->begin();
    radio->setPALevel(RF24_PA_MAX);
    radio->setChannel(0x76);
    radio->openWritingPipe(0xF0F0F0F0E1LL);
    radio->enableDynamicPayloads();
    radio->powerUp();
    //radio->printDetails();
#endif
}

void Monster::readAllProps()
{
    // read all props from all parts
    for(int i=0; i<partCount; i++)
    {
        Part * part = partArray[i];
        part->updateProps();

        for(int j=0; j<part->getPropCount(); j++)
        {
            // read message
            Message msg;
            msg.partId = i;
            part->readProp(j, msg);

            // send message
#if defined (ARDUINO)
            Serial.write(msg.data,MSG_SIZE);
            //for(int i=0; i<MSG_SIZE; i++) Serial.print(msg.data[i],HEX);
            Serial.println();
#endif
        }
    }
}

bool Monster::readMessage(Message &msg)
{
#ifdef DESKTOP
    uint8_t c;
    while (read(tty_fd,&c,1)>0)
    {
        if (buffIdx<MSG_SIZE)
        {
            buff[buffIdx++] = c;
        }
        else if (c=='\n')
        {
            buffIdx = 0;
            memcpy(msg.data, buff, MSG_SIZE);
            return true;
        }
    }
#endif
    return false;
}
