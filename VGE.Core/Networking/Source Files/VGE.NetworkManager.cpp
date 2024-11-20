#include "../Header Files/VGE.NetworkManager.h"
#include <iostream>

namespace VGE {

NetworkManager& NetworkManager::getInstance() {
    static NetworkManager instance;
    return instance;
}

void NetworkManager::connectToServer(const std::string& address, uint16_t port) {
    // Simulate network connection
    std::cout << "Connecting to server at " << address << ":" << port << std::endl;
    // Add connection logic
}

void NetworkManager::disconnectFromServer() {
    // Simulate network disconnection
    std::cout << "Disconnecting from server" << std::endl;
    // Add disconnection logic
}

void NetworkManager::sendData(const NetworkPacket& packet) {
    // Simulate sending data
    std::cout << "Sending data: " << packet.data.size() << " bytes" << std::endl;
    // Add data sending logic
}

void NetworkManager::registerCallback(NetworkCallback callback) {
    m_callbacks.push_back(callback);
}

void NetworkManager::processNetworkEvents() {
    // Simulate processing network events
    for (const auto& callback : m_callbacks) {
        NetworkPacket packet;
        packet.data = {0x01, 0x02, 0x03}; // Example data
        callback(NetworkEvent::DATA_RECEIVED, packet);
    }
    std::cout << "Processing network events" << std::endl;
}

} // namespace VGE
