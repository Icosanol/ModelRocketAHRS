#include "serialdevice.h"

SerialDevice::SerialDevice(QSerialPortInfo& portInfo)
{
    port_ = new QSerialPort(portInfo, this);
    port_->setBaudRate(57600);
    port_->setDataBits(QSerialPort::Data8);
    port_->setParity(QSerialPort::NoParity);
    port_->setStopBits(QSerialPort::OneStop);
    bool isOpen = port_->open(QIODevice::ReadWrite);

    if(!isOpen)
    {
        if(port_->error() == QSerialPort::PermissionError)
            throw SerialException("Permission error"); //Got r00t?
        else
            throw SerialException("Serial I/O error");
    }
}

SerialDevice::~SerialDevice()
{
}

void SerialDevice::sendCmd(SerialCommand cmd)
{
    char* dataByte = new char(0);

    switch(cmd)
    {
        case WAIT:
            *dataByte = 'W';
        case COLLECT:
            *dataByte = 'C';
        case ERASE:
            *dataByte = 'E';
        case DUMP:
            *dataByte = 'D';
    };

    port_->write(dataByte, sizeof(dataByte));
}
