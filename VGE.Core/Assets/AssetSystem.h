#pragma once

#include "VGE.Core.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

namespace VGE {

// Forward declarations
class IAsset;
class IAssetLoader;
class AssetCache;

// Asset types
enum class AssetType {
    UNKNOWN,
    TEXTURE,
    MESH,
    MATERIAL,
    SHADER,
    AUDIO,
    SCRIPT,
    PREFAB,
    SCENE,
    ANIMATION,
    FONT,
    CONFIG
};

// Asset metadata
struct AssetMetadata {
    std::string uuid;
    std::string path;
    AssetType type;
    Version version;
    size_t size;
    std::string checksum;
    bool isLoaded{false};
    bool isModified{false};
    std::vector<std::string> dependencies;
};

// Asset events
class AssetEvent : public Event {
public:
    enum class Type {
        LOAD_START,
        LOAD_SUCCESS,
        LOAD_FAILED,
        UNLOAD,
        MODIFIED,
        DELETED
    };

    AssetEvent(Type type, const std::string& assetId) 
        : m_type(type), m_assetId(assetId) {}

    const char* getType() const override {
        switch (m_type) {
            case Type::LOAD_START: return "ASSET_LOAD_START";
            case Type::LOAD_SUCCESS: return "ASSET_LOAD_SUCCESS";
            case Type::LOAD_FAILED: return "ASSET_LOAD_FAILED";
            case Type::UNLOAD: return "ASSET_UNLOAD";
            case Type::MODIFIED: return "ASSET_MODIFIED";
            case Type::DELETED: return "ASSET_DELETED";
            default: return "UNKNOWN";
        }
    }

    const std::string& getAssetId() const { return m_assetId; }

private:
    Type m_type;
    std::string m_assetId;
};

// Asset interface
class IAsset {
public:
    virtual ~IAsset() = default;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
    virtual const char* getType() const = 0;
    virtual bool serialize(std::vector<uint8_t>& data) const = 0;
    virtual bool deserialize(const std::vector<uint8_t>& data) = 0;
};

// Asset loader interface
class IAssetLoader {
public:
    virtual ~IAssetLoader() = default;
    virtual bool canLoad(const std::string& path) const = 0;
    virtual std::unique_ptr<IAsset> load(const std::string& path) = 0;
    virtual bool save(const std::string& path, const IAsset* asset) = 0;
};

// Asset Manager class
class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;

    bool initialize(const std::string& assetRoot);
    void shutdown();

    // Asset operations
    bool loadAsset(const std::string& path, bool async = false);
    void unloadAsset(const std::string& uuid);
    bool reloadAsset(const std::string& uuid);
    bool saveAsset(const std::string& uuid);

    // Asset queries
    IAsset* getAsset(const std::string& uuid);
    const AssetMetadata* getAssetMetadata(const std::string& uuid) const;
    std::vector<std::string> getLoadedAssets() const;
    std::vector<std::string> findAssetsByType(AssetType type) const;

    // Asset registration
    void registerLoader(AssetType type, std::unique_ptr<IAssetLoader> loader);
    void unregisterLoader(AssetType type);

    // Hot reloading
    void enableHotReload(bool enable);
    void checkForModifications();

    // Asset operations
    std::string importAsset(const std::string& sourcePath, const std::string& targetPath);
    bool exportAsset(const std::string& uuid, const std::string& targetPath);

private:
    std::string generateUUID() const;
    AssetType getAssetTypeFromExtension(const std::string& path) const;
    bool loadAssetInternal(const std::string& path, const std::string& uuid);
    void watchAssetDirectory();
    void processHotReload();

    std::string m_assetRoot;
    std::unique_ptr<AssetCache> m_cache;
    std::unordered_map<AssetType, std::unique_ptr<IAssetLoader>> m_loaders;
    std::unordered_map<std::string, AssetMetadata> m_metadata;
    std::unordered_map<std::string, std::unique_ptr<IAsset>> m_loadedAssets;
    bool m_hotReloadEnabled{false};
    bool m_initialized{false};
};

} // namespace VGE
