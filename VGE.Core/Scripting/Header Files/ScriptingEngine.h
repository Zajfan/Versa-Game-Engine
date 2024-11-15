#pragma once

#include <string>
#include <any>

namespace VGE
{
	class ScriptingEngine
	{
	public:
		virtual ~ScriptingEngine() {}
		virtual bool LoadScript() = 0;
		virtual bool LoadScript(const std::string& scriptPath) = 0;
		virtual bool CompileScript(const std::string& scriptCode) = 0;
		virtual bool CompileScriptFromFile(const std::string& scriptPath) = 0;
		virtual void ExecuteScript() = 0;
		virtual void ExecuteScript(const std::string& scriptCode) = 0;
		virtual void ExecuteScriptFromFile() = 0;
		virtual void ExecuteScriptFromFile(const std::string& scriptPath) = 0;
		virtual void StartScript() = 0;
		virtual void PauseScript() = 0;
		virtual void StopScript() = 0;
		virtual bool IsScriptLoaded() const = 0;
		virtual bool IsScriptCompiled() const = 0;
		virtual bool IsScriptRunning() const = 0;
		virtual bool IsScriptPaused() const = 0;
		virtual void SetScriptVariable(const std::string& name, const std::string& value) = 0;
		virtual void RegisterFunction(const std::string& functionName, std::any(*function)(const std::vector<std::any>&)) = 0;
		virtual void SetVariable(const std::string& name, const std::any& value) = 0;
		virtual std::any GetVariable(const std::string& name) = 0;
		virtual void SetFunction(const std::string& functionName, std::any(*function)(const std::vector<std::any>&)) = 0;
		virtual std::any CallFunction(const std::string& functionName, const std::vector<std::any>& args) = 0;
		virtual void SetGlobalVariable(const std::string& name, const std::any& value) = 0;
		virtual std::any GetGlobalVariable(const std::string& name) = 0;
		virtual void SetGlobalFunction(const std::string& functionName, std::any(*function)(const std::vector<std::any>&)) = 0;
		virtual std::any CallGlobalFunction(const std::string& functionName, const std::vector<std::any>& args) = 0;

	};
}


