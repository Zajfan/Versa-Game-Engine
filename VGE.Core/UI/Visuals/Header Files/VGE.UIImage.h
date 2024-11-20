#ifndef UIIMAGE_H
#define UIIMAGE_H

#include "UIElement.h"
#include <string>

class UIImage : public UIElement
{
public:
    UIImage(const std::string& imagePath);

    void Render(OpenGLRenderer& renderer) override;
    // You might not need to override HandleInput if the image doesn't have any interactive behavior

    // Properties
    std::string ImagePath;

private:
    // ... (Helper functions or member variables)
    // For example:
    // - unsigned int textureID; // To store the OpenGL texture ID
};

#endif // UIIMAGE_H