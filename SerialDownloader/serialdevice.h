#ifndef SERIALDEVICE_H
#define SERIALDEVICE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "serialexception.h"

enum SerialCommand
{
    WAIT,
    COLLECT,
    ERASE,
    DUMP
};

class SerialDevice: public QObject
{
    Q_OBJECT

    public:
      SerialDevice(QSerialPortInfo& portInfo);
      ~SerialDevice();
      void sendCmd(SerialCommand cmd);
    private:
      QSerialPort* port_;
};

#endif // SERIALDEVICE_H
