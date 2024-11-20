#include "GraphSerializer.h"

void GraphSerializer::Serialize(const Graph& graph, const std::string& filePath)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root = doc.NewElement("Graph");
    doc.InsertEndChild(root);

    // ... (Serialization logic for nodes and connections, 
    //      similar to what we discussed earlier, but now within 
    //      the GraphSerializer class)

    doc.SaveFile(filePath.c_str());
}

void GraphSerializer::Deserialize(Graph& graph, const std::string& filePath)
{
    // ... (Deserialization logic for nodes and connections)
}

// ... (Implementations for helper functions: SerializeNode, DeserializeNode, 
//      SerializeConnection, DeserializeConnection, etc.)