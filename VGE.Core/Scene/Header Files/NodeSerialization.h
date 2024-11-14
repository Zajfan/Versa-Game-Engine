#ifndef NODESERIALIZATION_H
#define NODESERIALIZATION_H

#include "Node.h" 
#include <tinyxml2.h>

class NodeSerialization
{
public:
    static std::string Serialize(const Node& node);
    static void Deserialize(Node& node, const std::string& xmlData);
	static void SerializeToFile(const Node& node, const std::string& filename);
	static void DeserializeFromFile(Node& node, const std::string& filename);

private:
    // Helper functions for serializing/deserializing specific properties
    static void SerializeProperties(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* parentElement, const Node& node);
    static void DeserializeProperties(tinyxml2::XMLElement* parentElement, Node& node);
	static void SerializeComponents(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* parentElement, const Node& node);
	static void DeserializeComponents(tinyxml2::XMLElement* parentElement, Node& node);
	static void SerializePins(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* parentElement, const std::vector<Pin>& pins);
	static void DeserializePins(tinyxml2::XMLElement* parentElement, std::vector<Pin>& pins);
	static void SerializePin(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* parentElement, const Pin& pin);
	static void DeserializePin(tinyxml2::XMLElement* parentElement, Pin& pin);
	static std::string NodeDataTypeToString(Pin::DataType dataType);
	static Pin::DataType StringToNodeDataType(const std::string& dataTypeStr);

	// Helper functions for converting XML to/from string/file
	static tinyxml2::XMLDocument ConvertToXMLDocument(const std::string& xmlData);
	static std::string ConvertToXMLString(tinyxml2::XMLDocument& doc);
	static void ConvertToXMLFile(tinyxml2::XMLDocument& doc, const std::string& filename);
	static tinyxml2::XMLDocument LoadXMLFile(const std::string& filename);

    // ... (Add other helper functions as needed)
};

#endif // NODESERIALIZATION_H