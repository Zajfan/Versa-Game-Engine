#include "LuaScriptingEngine.h"

LuaScriptingEngine::LuaScriptingEngine()
{
    L = luaL_newstate(); // Create a new Lua state
    luaL_openlibs(L);    // Open the standard Lua libraries
}

LuaScriptingEngine::~LuaScriptingEngine()
{
    if (L) {
        lua_close(L); // Close the Lua state
    }
}

bool LuaScriptingEngine::LoadScript(const std::string& scriptPath)
{
    // Load the Lua script from file
    if (luaL_dofile(L, scriptPath.c_str()) != LUA_OK) {
        // Handle script loading error
        std::cerr << "Failed to load Lua script: " << lua_tostring(L, -1) << std::endl;
        return false;
    }
    return true;
}

bool LuaScriptingEngine::CompileScript(const std::string& scriptCode)
{
    // Compile the Lua script code (optional)
    // ... (You might not need this if you're executing scripts directly)
    return true;
}

void LuaScriptingEngine::ExecuteScript()
{
    // Execute the Lua script
    // ... (Call a specific function or execute the entire script)
}

// ... (Implement other methods for variable access, function calls, etc.)