#include "serialexception.h"

SerialException::SerialException(const QString& errorStr)
    :std::runtime_error(errorStr.toStdString())
{
}

SerialException::~SerialException()
{
}
