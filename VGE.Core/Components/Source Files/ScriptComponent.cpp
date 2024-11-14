#include "ScriptComponent.h"
#include "Node.h"
#include "Event.h"
#include "ScriptingEngine.h"

#include <any>
#include <iostream>

// Helper functions for loading and compiling scripts

// Constructor
ScriptComponent::ScriptComponent(Node* owner) : NodeComponent(owner) {
    // Initialize scripting-specific properties
    scriptSourceCode = LoadScript("path/to/script");
        CompileScript(scriptSourceCode);
}

// Methods for executing the script, handling events, etc.
void ScriptComponent::Execute() {
    // Check if the script is compiled
    if (!isScriptCompiled) {
        std::cerr << "Script is not compiled. Cannot execute." << std::endl;
        return;
    }

    // Execute the script
    try {
        scriptingEngine->ExecuteScript(compiledScript);
    }
    catch (const std::exception& e) {
        std::cerr << "Script execution failed: " << e.what() << std::endl;
    }
}

void ScriptComponent::HandleEvent(const Event& event) {
    // TODO: Implement event handling logic within the script
    // You might need to expose an API for scripts to register event listeners
}

// ... (Add other methods for interacting with the script)
