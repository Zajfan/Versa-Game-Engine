#ifndef NODEVISUALS_H
#define NODEVISUALS_H

#include "glm/glm.hpp"

// Assuming this enum is defined elsewhere (e.g., in Node.h or a separate header)
enum class NodeShape { Rectangle, RoundedRectangle, Circle, Custom };

// Define visual properties of a Node
struct NodeVisuals
{
    NodeShape Shape;
    glm::vec3 Color;
    glm::vec3 BorderColor;
    glm::vec3 BackgroundColor;
    glm::vec3 ShadowColor;
    glm::vec3 GridColor;
    // ... (Other color properties for grid lines, dots, etc.)
    std::string Icon;
    std::string Tooltip;
    bool IsCollapsed;
    float BorderThickness;
    // ... (Other properties related to visual appearance: ShowLabel, ShowIcon, etc.) 
};

#endif // NODEVISUALS_H