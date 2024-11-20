#include "../Header Files/AssetSystem.h"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <random>
#include <thread>
#include <queue>

namespace VGE {

namespace fs = std::filesystem;

// Asset Cache implementation
class AssetCache {
public:
    AssetCache(size_t maxSize) : m_maxSize(maxSize) {}

    bool add(const std::string& uuid, std::vector<uint8_t>&& data) {
        if (m_currentSize + data.size() > m_maxSize) {
            // Evict oldest entries until we have enough space
            while (!m_accessQueue.empty() && m_currentSize + data.size() > m_maxSize) {
                auto oldestUuid = m_accessQueue.front();
                m_accessQueue.pop();
                auto it = m_cache.find(oldestUuid);
                if (it != m_cache.end()) {
                    m_currentSize -= it->second.size();
                    m_cache.erase(it);
                }
            }
        }

        m_cache[uuid] = std::move(data);
        m_accessQueue.push(uuid);
        m_currentSize += m_cache[uuid].size();
        return true;
    }

    const std::vector<uint8_t>* get(const std::string& uuid) {
        auto it = m_cache.find(uuid);
        if (it != m_cache.end()) {
            // Update access order
            m_accessQueue.push(uuid);
            return &it->second;
        }
        return nullptr;
    }

    void remove(const std::string& uuid) {
        auto it = m_cache.find(uuid);
        if (it != m_cache.end()) {
            m_currentSize -= it->second.size();
            m_cache.erase(it);
        }
    }

    void clear() {
        m_cache.clear();
        std::queue<std::string>().swap(m_accessQueue);
        m_currentSize = 0;
    }

private:
    size_t m_maxSize;
    size_t m_currentSize{0};
    std::unordered_map<std::string, std::vector<uint8_t>> m_cache;
    std::queue<std::string> m_accessQueue;
};

// AssetManager implementation
bool AssetManager::initialize(const std::string& assetRoot) {
    if (m_initialized) {
        return false;
    }

    m_assetRoot = assetRoot;
    if (!fs::exists(m_assetRoot)) {
        try {
            fs::create_directories(m_assetRoot);
        } catch (const std::exception&) {
            return false;
        }
    }

    // Initialize asset cache (1GB default size)
    m_cache = std::make_unique<AssetCache>(1024 * 1024 * 1024);

    m_initialized = true;
    return true;
}

void AssetManager::shutdown() {
    // Unload all assets
    auto loadedAssets = getLoadedAssets();
    for (const auto& uuid : loadedAssets) {
        unloadAsset(uuid);
    }

    m_cache->clear();
    m_loaders.clear();
    m_metadata.clear();
    m_loadedAssets.clear();
    m_initialized = false;
}

bool AssetManager::loadAsset(const std::string& path, bool async) {
    if (!m_initialized) return false;

    std::string uuid = generateUUID();
    
    if (async) {
        // Launch async loading task
        std::thread([this, path, uuid]() {
            loadAssetInternal(path, uuid);
        }).detach();
        return true;
    }
    
    return loadAssetInternal(path, uuid);
}

bool AssetManager::loadAssetInternal(const std::string& path, const std::string& uuid) {
    // Dispatch load start event
    Engine::getInstance().dispatchEvent(AssetEvent(AssetEvent::Type::LOAD_START, uuid));

    // Determine asset type
    AssetType type = getAssetTypeFromExtension(path);
    if (type == AssetType::UNKNOWN) {
        Engine::getInstance().dispatchEvent(AssetEvent(AssetEvent::Type::LOAD_FAILED, uuid));
        return false;
    }

    // Find appropriate loader
    auto loaderIt = m_loaders.find(type);
    if (loaderIt == m_loaders.end()) {
        Engine::getInstance().dispatchEvent(AssetEvent(AssetEvent::Type::LOAD_FAILED, uuid));
        return false;
    }

    // Load asset
    auto asset = loaderIt->second->load(path);
    if (!asset || !asset->initialize()) {
        Engine::getInstance().dispatchEvent(AssetEvent(AssetEvent::Type::LOAD_FAILED, uuid));
        return false;
    }

    // Create metadata
    AssetMetadata metadata;
    metadata.uuid = uuid;
    metadata.path = path;
    metadata.type = type;
    metadata.version = Version{1, 0, 0};
    metadata.isLoaded = true;

    // Store asset and metadata
    m_loadedAssets[uuid] = std::move(asset);
    m_metadata[uuid] = std::move(metadata);

    // Dispatch load success event
    Engine::getInstance().dispatchEvent(AssetEvent(AssetEvent::Type::LOAD_SUCCESS, uuid));
    return true;
}

void AssetManager::unloadAsset(const std::string& uuid) {
    auto assetIt = m_loadedAssets.find(uuid);
    if (assetIt != m_loadedAssets.end()) {
        assetIt->second->shutdown();
        m_loadedAssets.erase(assetIt);
        m_cache->remove(uuid);
        
        auto metaIt = m_metadata.find(uuid);
        if (metaIt != m_metadata.end()) {
            metaIt->second.isLoaded = false;
        }

        Engine::getInstance().dispatchEvent(AssetEvent(AssetEvent::Type::UNLOAD, uuid));
    }
}

bool AssetManager::reloadAsset(const std::string& uuid) {
    auto metaIt = m_metadata.find(uuid);
    if (metaIt == m_metadata.end()) {
        return false;
    }

    std::string path = metaIt->second.path;
    unloadAsset(uuid);
    return loadAssetInternal(path, uuid);
}

bool AssetManager::saveAsset(const std::string& uuid) {
    auto assetIt = m_loadedAssets.find(uuid);
    auto metaIt = m_metadata.find(uuid);
    
    if (assetIt == m_loadedAssets.end() || metaIt == m_metadata.end()) {
        return false;
    }

    auto loaderIt = m_loaders.find(metaIt->second.type);
    if (loaderIt == m_loaders.end()) {
        return false;
    }

    return loaderIt->second->save(metaIt->second.path, assetIt->second.get());
}

IAsset* AssetManager::getAsset(const std::string& uuid) {
    auto it = m_loadedAssets.find(uuid);
    return it != m_loadedAssets.end() ? it->second.get() : nullptr;
}

const AssetMetadata* AssetManager::getAssetMetadata(const std::string& uuid) const {
    auto it = m_metadata.find(uuid);
    return it != m_metadata.end() ? &it->second : nullptr;
}

std::vector<std::string> AssetManager::getLoadedAssets() const {
    std::vector<std::string> result;
    result.reserve(m_loadedAssets.size());
    
    for (const auto& pair : m_loadedAssets) {
        result.push_back(pair.first);
    }
    
    return result;
}

std::vector<std::string> AssetManager::findAssetsByType(AssetType type) const {
    std::vector<std::string> result;
    
    for (const auto& pair : m_metadata) {
        if (pair.second.type == type) {
            result.push_back(pair.first);
        }
    }
    
    return result;
}

void AssetManager::registerLoader(AssetType type, std::unique_ptr<IAssetLoader> loader) {
    if (loader) {
        m_loaders[type] = std::move(loader);
    }
}

void AssetManager::unregisterLoader(AssetType type) {
    m_loaders.erase(type);
}

void AssetManager::enableHotReload(bool enable) {
    m_hotReloadEnabled = enable;
    if (enable) {
        watchAssetDirectory();
    }
}

void AssetManager::checkForModifications() {
    if (!m_hotReloadEnabled) return;
    processHotReload();
}

std::string AssetManager::importAsset(const std::string& sourcePath, const std::string& targetPath) {
    if (!fs::exists(sourcePath)) {
        return "";
    }

    // Create target directory if it doesn't exist
    fs::path targetDir = fs::path(targetPath).parent_path();
    if (!fs::exists(targetDir)) {
        try {
            fs::create_directories(targetDir);
        } catch (const std::exception&) {
            return "";
        }
    }

    // Copy file to asset directory
    try {
        fs::copy_file(sourcePath, targetPath, fs::copy_options::overwrite_existing);
    } catch (const std::exception&) {
        return "";
    }

    // Load the asset
    return loadAsset(targetPath) ? generateUUID() : "";
}

bool AssetManager::exportAsset(const std::string& uuid, const std::string& targetPath) {
    auto assetIt = m_loadedAssets.find(uuid);
    if (assetIt == m_loadedAssets.end()) {
        return false;
    }

    std::vector<uint8_t> data;
    if (!assetIt->second->serialize(data)) {
        return false;
    }

    try {
        std::ofstream file(targetPath, std::ios::binary);
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

std::string AssetManager::generateUUID() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static const char* chars = "0123456789abcdef";

    std::string uuid;
    uuid.reserve(36);

    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            uuid += '-';
        } else {
            uuid += chars[dis(gen)];
        }
    }

    return uuid;
}

AssetType AssetManager::getAssetTypeFromExtension(const std::string& path) const {
    std::string ext = fs::path(path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".tga") return AssetType::TEXTURE;
    if (ext == ".obj" || ext == ".fbx" || ext == ".gltf") return AssetType::MESH;
    if (ext == ".mat") return AssetType::MATERIAL;
    if (ext == ".glsl" || ext == ".hlsl" || ext == ".shader") return AssetType::SHADER;
    if (ext == ".wav" || ext == ".mp3" || ext == ".ogg") return AssetType::AUDIO;
    if (ext == ".lua" || ext == ".js" || ext == ".py") return AssetType::SCRIPT;
    if (ext == ".prefab") return AssetType::PREFAB;
    if (ext == ".scene") return AssetType::SCENE;
    if (ext == ".anim") return AssetType::ANIMATION;
    if (ext == ".ttf" || ext == ".otf") return AssetType::FONT;
    if (ext == ".json" || ext == ".yaml" || ext == ".xml") return AssetType::CONFIG;

    return AssetType::UNKNOWN;
}

void AssetManager::watchAssetDirectory() {
    // TODO: Implement file system watcher
    // This would typically use platform-specific APIs (e.g., ReadDirectoryChangesW on Windows)
    // or a cross-platform library like std::filesystem
}

void AssetManager::processHotReload() {
    // TODO: Implement hot reload processing
    // This would check for file modifications and reload assets as needed
}

} // namespace VGE
