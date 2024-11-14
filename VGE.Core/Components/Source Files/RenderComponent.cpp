#include "RenderComponent.h"
#include "Node.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <freeglut.h>

void RenderComponent::Render()
{
    // Assuming you have a Node* m_owner; in your NodeComponent class
    // and properties like Color, Shape, etc. in your Node class

    // Set color
    glColor3f(m_owner->Color.x, m_owner->Color.y, m_owner->Color.z);

    // Set line width
    glLineWidth(m_owner->BorderThickness);

    switch (m_owner->Shape)
    {
    case Node::NodeShape::Rectangle:
        // Draw rectangle
        glBegin(GL_QUADS);
        glVertex2f(m_owner->Position.x, m_owner->Position.y);
        glVertex2f(m_owner->Position.x + m_owner->Size.x, m_owner->Position.y);
        glVertex2f(m_owner->Position.x + m_owner->Size.x, m_owner->Position.y + m_owner->Size.y);
        glVertex2f(m_owner->Position.x, m_owner->Position.y + m_owner->Size.y);
        glEnd();
        break;
    case Node::NodeShape::Circle:
        // Draw circle
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(m_owner->Position.x + m_owner->Size.x / 2, m_owner->Position.y + m_owner->Size.y / 2);
        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(m_owner->Position.x + m_owner->Size.x / 2 + cos(angle) * m_owner->Size.x / 2,
                m_owner->Position.y + m_owner->Size.y / 2 + sin(angle) * m_owner->Size.y / 2);
        }
        glEnd();
        break;
        // ... add cases for other shapes
    default:
        // Draw default rectangle
        glBegin(GL_QUADS);
        glVertex2f(m_owner->Position.x, m_owner->Position.y);
        glVertex2f(m_owner->Position.x + m_owner->Size.x, m_owner->Position.y);
        glVertex2f(m_owner->Position.x + m_owner->Size.x, m_owner->Position.y + m_owner->Size.y);
        glVertex2f(m_owner->Position.x, m_owner->Position.y + m_owner->Size.y);
        glEnd();
        break;
    }

    // Draw node name
    // Note: OpenGL does not have built-in text rendering, you need to use a library like FreeType or GLUT for text rendering
    // Here is an example using FreeGLUT
    glRasterPos2f(m_owner->Position.x + 10, m_owner->Position.y + 10);
    for (char c : m_owner->Name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Draw icon if available
    if (!m_owner->Icon.empty())
    {
        // TODO: Implement icon loading and drawing
    }
}
