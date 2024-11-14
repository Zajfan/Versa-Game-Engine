#include <string>
#include <any>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "NodeData.h"
#include "Node.h"
#include "DataTypeUtils.h"
#include "NodeComponent.h"
#include "Event.h"

template <typename T>
void Node::SetInputData(const std::string& pinName, const T& value)
{
    auto it = std::find_if(InputPins.begin(), InputPins.end(),
        [&](const Pin& pin) { return pin.Name == pinName; });

    if (it != InputPins.end())
    {
        if (it->DataType == GetNodeDataType<T>())
        {
            it->Data = value;
        }
        else
        {
            throw std::runtime_error("Input data type mismatch for pin: " + pinName);
        }
    }
    else
    {
        throw std::runtime_error("Input pin not found: " + pinName);
    }
}

template <typename T>
T Node::GetOutputData(const std::string& pinName) const
{
    auto it = std::find_if(OutputPins.begin(), OutputPins.end(),
        [&](const Pin& pin) { return pin.Name == pinName; });

    if (it != OutputPins.end())
    {
        if (it->DataType == GetNodeDataType<T>())
        {
            return std::any_cast<T>(it->Data);
        }
        else
        {
            throw std::runtime_error("Output data type mismatch for pin: " + pinName);
        }
    }
    else
    {
        throw std::runtime_error("Output pin not found: " + pinName);
    }
}
