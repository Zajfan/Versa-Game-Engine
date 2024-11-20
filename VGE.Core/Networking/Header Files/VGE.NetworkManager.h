#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>

namespace VGE {

enum class NetworkEvent {
    CONNECTED,
    DISCONNECTED,
    DATA_RECEIVED,
    ERROR
};

struct NetworkPacket {
    std::vector<uint8_t> data;
};

class NetworkManager {
public:
    using NetworkCallback = std::function<void(NetworkEvent, const NetworkPacket&)>;

    static NetworkManager& getInstance();

    void connectToServer(const std::string& address, uint16_t port);
    void disconnectFromServer();
    void sendData(const NetworkPacket& packet);
    void registerCallback(NetworkCallback callback);
    void processNetworkEvents();

private:
    NetworkManager() = default;
    std::vector<NetworkCallback> m_callbacks;
    // Add network connection details and state
};

} // namespace VGE
