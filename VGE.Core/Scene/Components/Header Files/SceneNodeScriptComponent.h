// NodeScriptComponent.h
#ifndef NODESCRIPTCOMPONENT_H
#define NODESCRIPTCOMPONENT_H

#include "NodeComponent.h"
#include "VersaScriptingEngine.h"

#include <string>
#include <memory>
#include <vector>

class NodeScriptComponent : public NodeComponent
{
public:
    NodeScriptComponent(Node* owner);

    // Properties specific to scripting (e.g., script source code, compiled script)
    std::string ScriptPath;
    // ... (Add other properties as needed)

    void Execute() override;
    void HandleEvent(const Event& event) override;

private:
    // ... (Add private members or helper functions as needed)
    std::unique_ptr<VersaScriptingEngine> scriptingEngine; // Use your engine's scripting interface
};

#endif // NODESCRIPTCOMPONENT_H