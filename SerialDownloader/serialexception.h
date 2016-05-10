#ifndef SERIALEXCEPTION_H
#define SERIALEXCEPTION_H

#include <stdexcept>
#include <QString>

class SerialException: public std::runtime_error
{
    public:
        SerialException(const QString& errorStr);
        ~SerialException();
};

#endif // SERIALEXCEPTION_H
