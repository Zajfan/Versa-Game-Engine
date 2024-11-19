// ScriptComponent.h
#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "VersaScriptingEngine.h" 

class ScriptComponent : public ScriptComponent
{
public:
	ScriptComponent();
	~ScriptComponent();
	void LoadScript(const std::string& scriptPath);
	void ExecuteScript();
	void RegisterFunction(const std::string& functionName, std::any(*function)(const std::vector<std::any>&));
	void SetVariable(const std::string& name, const std::any& value);
	std::any GetVariable(const std::string& name) const;
	std::any CallFunction(const std::string& functionName, const std::vector<std::any>& args);
	void StartScript();
	void PauseScript();
	void ResumeScript();
	void StopScript();
	void ResetScript();
	void UnloadScript();
	void ReloadScript();
	void CompileScript();
	bool IsScriptCompiled() const;
	bool IsScriptLoaded() const;
	bool IsScriptRunning() const;
	bool IsScriptPaused() const;
};


#endif // SCRIPTCOMPONENT_H