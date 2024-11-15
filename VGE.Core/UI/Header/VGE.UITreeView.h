#ifndef UITREEVIEW_H
#define UITREEVIEW_H

#include "UIElement.h"
#include <vector>
#include <string>
#include <memory>

class UITreeViewItem;

class UITreeView : public UIElement
{
public:
    UITreeView();

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Methods to manage items
    UITreeViewItem* AddItem(const std::string& text, UITreeViewItem* parent = nullptr);
    void RemoveItem(UITreeViewItem* item);
    void Clear();

private:
    // ... (Helper functions or member variables)
    std::vector<std::unique_ptr<UITreeViewItem>> rootItems_;
};

class UITreeViewItem : public UIElement
{
public:
    UITreeViewItem(const std::string& text, UITreeView* parentTreeView);

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Properties
    std::string Text;
    bool IsExpanded = false;
    UITreeViewItem* Parent = nullptr;
    std::vector<std::unique_ptr<UITreeViewItem>> Children;

private:
    UITreeView* parentTreeView_; // Pointer to the parent tree view
    // ... (Helper functions or member variables)
};

#endif // UITREEVIEW_H