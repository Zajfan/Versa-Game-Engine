#ifndef NODEDATA_H
#define NODEDATA_H

#include "Node.h"

template <typename T>
void Node::SetInputData(const std::string& pinName, const T& value)
{
    // 1. Find the input pin with the given name
    auto it = std::find_if(InputPins.begin(), InputPins.end(),
        [&](const Pin& pin) { return pin.Name == pinName; });

    if (it != InputPins.end())
    {
        // 2. Check if the pin's data type matches the type of 'value'
        if (it->DataType == GetNodeDataType<T>())
        {
            // 3. Perform data validation
            if (IsValidInput(pinName, value))
            {
                // 4. If the types match, store the value in the pin's data
                it->Data = value;
            }
            else
            {
                // Handle invalid input
                throw std::runtime_error("Invalid input value for pin: " + pinName);
            }
        }
        else
        {
            // 4. If the types don't match, handle the error
            throw std::runtime_error("Input data type mismatch for pin: " + pinName);
        }
    }
    else
    {
        // Handle the case where the pin is not found
        throw std::runtime_error("Input pin not found: " + pinName);
    }
}

template <typename T>
T Node::GetOutputData(const std::string& pinName) const
{
    // 1. Find the output pin with the given name
    auto it = std::find_if(OutputPins.begin(), OutputPins.end(),
        [&](const Pin& pin) { return pin.Name == pinName; });

    if (it != OutputPins.end())
    {
        // 2. Check if the pin's data type matches the requested type T
        if (it->DataType == GetNodeDataType<T>())
        {
            // 3. If the types match, return the pin's data cast to type T
            return std::any_cast<T>(it->Data);
        }
        else
        {
            // 4. If the types don't match, handle the error
            throw std::runtime_error("Output data type mismatch for pin: " + pinName);
        }
    }
    else
    {
        // Handle the case where the pin is not found
        throw std::runtime_error("Output pin not found: " + pinName);
    }
}

#endif // NODEDATA_H
