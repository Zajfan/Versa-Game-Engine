#pragma once
#ifndef GRAPHSERIALIZER_H
#define GRAPHSERIALIZER_H

#include "Graph.h"
#include <tinyxml2.h> // Or your preferred XML library

class GraphSerializer
{
public:
    static void Serialize(const Graph& graph, const std::string& filePath);
    static void Deserialize(Graph& graph, const std::string& filePath);

private:
    static tinyxml2::XMLElement* SerializeNode(tinyxml2::XMLDocument& doc, Node* node);
    static Node* DeserializeNode(tinyxml2::XMLElement* nodeElement);
    static tinyxml2::XMLElement* SerializeConnection(tinyxml2::XMLDocument& doc, Connection* connection);
    static Connection* DeserializeConnection(tinyxml2::XMLElement* connectionElement, Graph& graph);
    // ... (Other helper functions as needed)
};

#endif // GRAPHSERIALIZER_H