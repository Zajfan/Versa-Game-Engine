#include "NodeSerialization.h"
#include "Pin.h"
#include "Node.h"
#include "NodeComponent.h"
#include "NodeDataType.h"
#include "tinyxml2/tinyxml2.h"

#include <any>
#include <typeinfo>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <string_view>
#include <algorithm>
#include <optional>

// Namespace for helper functions and constants
namespace NodeSerializationUtils {
    // Mapping DataType enum to string for easy serialization
    const std::unordered_map<Pin::DataType, std::string_view> dataTypeToStringMap {
        { Pin::DataType::Integer, "Integer" },
        { Pin::DataType::Float, "Float" },
        { Pin::DataType::String, "String" },
        { Pin::DataType::Boolean, "Boolean" },
        { Pin::DataType::Vector2, "Vector2" },
        // ... continue adding other data types as needed
    };

    // Reverse mapping from string to DataType enum for deserialization
    const std::unordered_map<std::string_view, Pin::DataType> stringToDataTypeMap {
        { "Integer", Pin::DataType::Integer },
        { "Float", Pin::DataType::Float },
        { "String", Pin::DataType::String },
        { "Boolean", Pin::DataType::Boolean },
        { "Vector2", Pin::DataType::Vector2 },
        // ... continue adding other data types as needed
    };

    // Converts a DataType enum to its corresponding string
    std::string_view NodeDataTypeToString(Pin::DataType dataType) {
        auto it = dataTypeToStringMap.find(dataType);
        return it != dataTypeToStringMap.end() ? it->second : "Unknown";
    }

    // Converts a string to its corresponding DataType enum
    Pin::DataType StringToNodeDataType(std::string_view str) {
        auto it = stringToDataTypeMap.find(str);
        return it != stringToDataTypeMap.end() ? it->second : Pin::DataType::Integer; // Fallback to Integer
    }
}

// Serializes a Node to an XML string format
std::string NodeSerialization::Serialize(const Node& node) {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root = doc.NewElement("Node");
    doc.InsertEndChild(root);

    // Serialize node properties and components
    SerializeProperties(doc, root, node);
    SerializeComponents(doc, root, node);

    // Serialize input and output pins
    SerializePins(doc, root, node.InputPins, "InputPins");
    SerializePins(doc, root, node.OutputPins, "OutputPins");

    return ConvertToXMLString(doc);
}

// Helper function to serialize pins
void NodeSerialization::SerializePins(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* parent, const std::vector<Pin>& pins, const char* pinType) {
    tinyxml2::XMLElement* pinsElement = doc.NewElement(pinType);
    parent->InsertEndChild(pinsElement);

    for (const Pin& pin : pins) {
        tinyxml2::XMLElement* pinElement = doc.NewElement("Pin");
        pinElement->SetAttribute("Name", pin.Name.c_str());
        pinElement->SetAttribute("DataType", NodeSerializationUtils::NodeDataTypeToString(pin.DataType).data());

        // Attempt to serialize pin data based on its type
        try {
            if (pin.Data.has_value()) {
                // Casting and setting the attribute based on DataType
                if (pin.DataType == Pin::DataType::Integer) {
                    pinElement->SetAttribute("Value", std::any_cast<int>(pin.Data));
                } else if (pin.DataType == Pin::DataType::Float) {
                    pinElement->SetAttribute("Value", std::any_cast<float>(pin.Data));
                }
                // Add more types as necessary
            }
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Error serializing pin data: " << e.what() << std::endl;
        }

        pinsElement->InsertEndChild(pinElement);
    }
}

// Deserializes a Node from an XML string format
void NodeSerialization::Deserialize(Node& node, const std::string& xmlData) {
    tinyxml2::XMLDocument doc = ConvertToXMLDocument(xmlData);
    tinyxml2::XMLElement* root = doc.FirstChildElement("Node");
    
    if (!root) {
        throw std::runtime_error("Invalid XML format: Missing Node root element");
    }

    // Deserialize properties, components, and pins
    DeserializeProperties(root, node);
    DeserializeComponents(root, node);
    DeserializePins(root->FirstChildElement("InputPins"), node.InputPins);
    DeserializePins(root->FirstChildElement("OutputPins"), node.OutputPins);
}

// Helper function to deserialize pins from XML
void NodeSerialization::DeserializePins(tinyxml2::XMLElement* pinsElement, std::vector<Pin>& pins) {
    if (!pinsElement) return;

    for (tinyxml2::XMLElement* pinElement = pinsElement->FirstChildElement("Pin"); pinElement != nullptr; pinElement = pinElement->NextSiblingElement("Pin")) {
        Pin pin;
        pin.Name = pinElement->Attribute("Name");
        pin.DataType = NodeSerializationUtils::StringToNodeDataType(pinElement->Attribute("DataType"));

        // Deserialize pin data based on DataType
        if (pin.DataType == Pin::DataType::Integer) {
            pin.Data = pinElement->IntAttribute("Value");
        } else if (pin.DataType == Pin::DataType::Float) {
            pin.Data = pinElement->FloatAttribute("Value");
        }
        // Add other types as needed

        pins.push_back(pin);
    }
}
