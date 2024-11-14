// ScriptComponent.h
#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "NodeComponent.h"
#include "VersaScriptingEngine.h" 

class ScriptComponent : public NodeComponent
{
public:
    ScriptComponent(Node* owner);

    // Properties specific to scripting (e.g., script source code, compiled script)
    std::string ScriptPath;
    // ... (Add other properties as needed)

    void Execute() override;
    void HandleEvent(const Event& event) override;

private:
    // ... (Add private members or helper functions as needed)
    std::unique_ptr<VersaScriptingEngine> scriptingEngine;
};

#endif // SCRIPTCOMPONENT_H