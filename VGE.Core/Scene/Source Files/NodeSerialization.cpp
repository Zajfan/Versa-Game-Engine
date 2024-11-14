#include "NodeSerialization.h"
#include "tinyxml2.h"
#include "Pin.h"
#include <any>
#include <typeinfo>

namespace
{
    // Helper function to convert NodeDataType to string
    const char* NodeDataTypeToString(Pin::DataType dataType)
    {
        switch (dataType)
        {
        case Pin::DataType::Integer: return "Integer";
        case Pin::DataType::Float: return "Float";
        case Pin::DataType::String: return "String";
		case Pin::DataType::Boolean: return "Boolean";
		case Pin::DataType::Vector2: return "Vector2";
		case Pin::DataType::Vector3: return "Vector3";
		case Pin::DataType::Vector4: return "Vector4";
		case Pin::DataType::Matrix3x3: return "Matrix3x3";
		case Pin::DataType::Matrix4x4: return "Matrix4x4";
		case Pin::DataType::Quaternion: return "Quaternion";
		case Pin::DataType::Color: return "Color";
		case Pin::DataType::Texture: return "Texture";
		case Pin::DataType::Audio: return "Audio";
		case Pin::DataType::Video: return "Video";
		case Pin::DataType::Animation: return "Animation";
		case Pin::DataType::Font: return "Font";
		case Pin::DataType::Mesh: return "Mesh";
		case Pin::DataType::Material: return "Material";
		case Pin::DataType::Shader: return "Shader";
		case Pin::DataType::Script: return "Script";
		case Pin::DataType::Scene: return "Scene";
		case Pin::DataType::Physics: return "Physics";
		case Pin::DataType::Particle: return "Particle";
		case Pin::DataType::Light: return "Light";
		case Pin::DataType::Camera: return "Camera";
		case Pin::DataType::Animation2D: return "Animation2D";
		case Pin::DataType::Font2D: return "Font2D";
		case Pin::DataType::Mesh2D: return "Mesh2D";
		case Pin::DataType::Material2D: return "Material2D";
		case Pin::DataType::Shader2D: return "Shader2D";
		case Pin::DataType::Script2D: return "Script2D";
		case Pin::DataType::Scene2D: return "Scene2D";
		case Pin::DataType::Physics2D: return "Physics2D";
		case Pin::DataType::Particle2D: return "Particle2D";
		case Pin::DataType::Light2D: return "Light2D";
		case Pin::DataType::Camera2D: return "Camera2D";
		case Pin::DataType::Animation3D: return "Animation3D";
		case Pin::DataType::Font3D: return "Font3D";
		case Pin::DataType::Mesh3D: return "Mesh3D";
		case Pin::DataType::Material3D: return "Material3D";
		case Pin::DataType::Shader3D: return "Shader3D";
		case Pin::DataType::Script3D: return "Script3D";
		case Pin::DataType::Scene3D: return "Scene3D";
		case Pin::DataType::Physics3D: return "Physics3D";
		case Pin::DataType::Particle3D: return "Particle3D";
		case Pin::DataType::Light3D: return "Light3D";
		case Pin::DataType::Camera3D: return "Camera3D";
            // ... add other types as needed
        default: return "Unknown";
        }
    }

    // Helper function to convert string to NodeDataType
    Pin::DataType StringToNodeDataType(const char* str)
    {
        if (strcmp(str, "Integer") == 0) return Pin::DataType::Integer;
        if (strcmp(str, "Float") == 0) return Pin::DataType::Float;
        if (strcmp(str, "String") == 0) return Pin::DataType::String;
		if (strcmp(str, "Boolean") == 0) return Pin::DataType::Boolean;
		if (strcmp(str, "Vector2") == 0) return Pin::DataType::Vector2;
		if (strcmp(str, "Vector3") == 0) return Pin::DataType::Vector3;
		if (strcmp(str, "Vector4") == 0) return Pin::DataType::Vector4;
		if (strcmp(str, "Matrix3x3") == 0) return Pin::DataType::Matrix3x3;
		if (strcmp(str, "Matrix4x4") == 0) return Pin::DataType::Matrix4x4;
		if (strcmp(str, "Quaternion") == 0) return Pin::DataType::Quaternion;
		if (strcmp(str, "Color") == 0) return Pin::DataType::Color;
		if (strcmp(str, "Texture") == 0) return Pin::DataType::Texture;
		if (strcmp(str, "Audio") == 0) return Pin::DataType::Audio;
		if (strcmp(str, "Video") == 0) return Pin::DataType::Video;
		if (strcmp(str, "Animation") == 0) return Pin::DataType::Animation;
		if (strcmp(str, "Font") == 0) return Pin::DataType::Font;
		if (strcmp(str, "Mesh") == 0) return Pin::DataType::Mesh;
		if (strcmp(str, "Material") == 0) return Pin::DataType::Material;
		if (strcmp(str, "Shader") == 0) return Pin::DataType::Shader;
		if (strcmp(str, "Script") == 0) return Pin::DataType::Script;
		if (strcmp(str, "Scene") == 0) return Pin::DataType::Scene;
		if (strcmp(str, "Physics") == 0) return Pin::DataType::Physics;
		if (strcmp(str, "Particle") == 0) return Pin::DataType::Particle;
		if (strcmp(str, "Light") == 0) return Pin::DataType::Light;
		if (strcmp(str, "Camera") == 0) return Pin::DataType::Camera;
		if (strcmp(str, "Animation2D") == 0) return Pin::DataType::Animation2D;
		if (strcmp(str, "Font2D") == 0) return Pin::DataType::Font2D;
		if (strcmp(str, "Mesh2D") == 0) return Pin::DataType::Mesh2D;
		if (strcmp(str, "Material2D") == 0) return Pin::DataType::Material2D;
		if (strcmp(str, "Shader2D") == 0) return Pin::DataType::Shader2D;
		if (strcmp(str, "Script2D") == 0) return Pin::DataType::Script2D;
		if (strcmp(str, "Scene2D") == 0) return Pin::DataType::Scene2D;
		if (strcmp(str, "Physics2D") == 0) return Pin::DataType::Physics2D;
		if (strcmp(str, "Particle2D") == 0) return Pin::DataType::Particle2D;
		if (strcmp(str, "Light2D") == 0) return Pin::DataType::Light2D;
		if (strcmp(str, "Camera2D") == 0) return Pin::DataType::Camera2D;
		if (strcmp(str, "Animation3D") == 0) return Pin::DataType::Animation3D;
		if (strcmp(str, "Font3D") == 0) return Pin::DataType::Font3D;
		if (strcmp(str, "Mesh3D") == 0) return Pin::DataType::Mesh3D;
		if (strcmp(str, "Material3D") == 0) return Pin::DataType::Material3D;
		if (strcmp(str, "Shader3D") == 0) return Pin::DataType::Shader3D;
		if (strcmp(str, "Script3D") == 0) return Pin::DataType::Script3D;
		if (strcmp(str, "Scene3D") == 0) return Pin::DataType::Scene3D;
		if (strcmp(str, "Physics3D") == 0) return Pin::DataType::Physics3D;
		if (strcmp(str, "Particle3D") == 0) return Pin::DataType::Particle3D;
		if (strcmp(str, "Light3D") == 0) return Pin::DataType::Light3D;
		if (strcmp(str, "Camera3D") == 0) return Pin::DataType::Camera3D;
        // ... add other types as needed
        return Pin::DataType::Integer; // Default fallback
    }
}

std::string NodeSerialization::Serialize(const Node& node)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root = doc.NewElement("Node");
    doc.InsertEndChild(root);

    // ... (Serialize node properties - same as before)

    // ... (Serialize components - same as before)

    // Serialize input and output pins
    tinyxml2::XMLElement* inputPinsElement = doc.NewElement("InputPins");
    root->InsertEndChild(inputPinsElement);
    for (const Pin& pin : node.InputPins)
    {
        tinyxml2::XMLElement* pinElement = doc.NewElement("Pin");
        pinElement->SetAttribute("Name", pin.Name.c_str());
        pinElement->SetAttribute("DataType", NodeDataTypeToString(pin.DataType)); // Use helper function

        // Serialize pin data using std::any_cast 
        try {
            if (pin.Data.has_value()) {
                if (pin.DataType == Pin::DataType::Integer) {
                    pinElement->SetAttribute("Value", std::any_cast<int>(pin.Data));
                }
                else if (pin.DataType == Pin::DataType::Float) {
                    pinElement->SetAttribute("Value", std::any_cast<float>(pin.Data));
                }
                // ... add other types as needed
                else {
                    // Handle unsupported types or serialize as string if possible
                    // ...
                }
            }
        }
        catch (const std::bad_any_cast& e) {
            std::cerr << "Error serializing pin data: " << e.what() << std::endl;
        }

        inputPinsElement->InsertEndChild(pinElement);
    }

    // ... (Serialize output pins - similar to input pins)

    // ... (Convert and return XML string - same as before)
}

void NodeSerialization::Deserialize(Node& node, const std::string& xmlData)
{
    // ... (Deserialize node properties - same as before)

    // ... (Deserialize components - same as before)

    // Deserialize input pins
    tinyxml2::XMLElement* inputPinsElement = root->FirstChildElement("InputPins");
    if (inputPinsElement)
    {
        for (tinyxml2::XMLElement* pinElement = inputPinsElement->FirstChildElement("Pin"); pinElement != nullptr; pinElement = pinElement->NextSiblingElement("Pin"))
        {
            Pin pin;
            pin.Name = pinElement->Attribute("Name");
            pin.DataType = StringToNodeDataType(pinElement->Attribute("DataType")); // Use helper function

            // Deserialize pin data based on DataType
            if (pin.DataType == Pin::DataType::Integer) {
                pin.Data = pinElement->IntAttribute("Value");
            }
            else if (pin.DataType == Pin::DataType::Float) {
                pin.Data = pinElement->FloatAttribute("Value");
            }
            // ... add other types as needed

            node.InputPins.push_back(pin);
        }
    }

    // ... (Deserialize output pins - similar to input pins)
}