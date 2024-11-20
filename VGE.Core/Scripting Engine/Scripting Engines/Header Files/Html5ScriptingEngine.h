#ifndef HTML5SCRIPTINGENGINE_H
#define HTML5SCRIPTINGENGINE_H

#include <string>
#include <any>
#include <vector>

class Html5ScriptingEngine
{
public:
    virtual ~Html5ScriptingEngine() = default;

    // Methods for loading, compiling, and executing scripts
    virtual bool LoadScript() = 0;
    virtual bool LoadScript(const std::string& scriptPath) = 0;
    virtual bool CompileScript(const std::string& scriptCode) = 0;
    virtual bool CompileScriptFromFile(const std::string& scriptPath) = 0;
    virtual void ExecuteScript() = 0;
    virtual void ExecuteScriptFromFile() = 0;
    virtual void ExecuteScriptFromFile(const std::string& scriptPath) = 0;
    virtual void ExecuteScript(const std::string& scriptCode) = 0;

    // Methods for checking the state of the scripting engine
    virtual bool IsScriptCompiled() const = 0;
    virtual bool IsScriptLoaded() const = 0;
    virtual bool IsScriptRunning() const = 0;
    virtual bool IsScriptPaused() const = 0;

    // Methods for controlling the execution of the script
    virtual void StartScript() = 0;
    virtual void PauseScript() = 0;
    virtual void ResumeScript() = 0;
    virtual void StopScript() = 0;
    virtual void ResetScript() = 0;
    virtual void UnloadScript() = 0;
    virtual void ReloadScript() = 0;
    virtual void CompileScript() = 0;

    // Methods for registering script functions
    virtual void RegisterFunction(const std::string& functionName, std::any(*function)(const std::vector<std::any>&)) = 0;

    // Methods for getting/setting script variables
    virtual void SetVariable(const std::string& name, const std::any& value) = 0;
    virtual std::any GetVariable(const std::string& name) const = 0;

    // Methods for calling script functions
    virtual std::any CallFunction(const std::string& functionName, const std::vector<std::any>& args) = 0;

    // ... (Add other methods as needed, e.g., for error handling, debugging)
};

#endif // HTML5SCRIPTINGENGINE_H
