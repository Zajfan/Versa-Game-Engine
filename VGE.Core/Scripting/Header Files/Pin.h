// Pin.h
#ifndef PIN_H
#define PIN_H

#include <string>

class Pin
{
public:
    enum class DataType
    {
        Integer,
        Float,
        String,
        // ... add other data types as needed
    };

    Pin(DataType dataType) : dataType(dataType) {}

    DataType GetDataType() const { return dataType; }

private:
    DataType dataType;
};

#endif // PIN_H
