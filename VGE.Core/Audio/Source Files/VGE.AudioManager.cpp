#include "../Header Files/VGE.AudioManager.h"
#include <iostream>

namespace VGE {

AudioClip::AudioClip(const std::string& filePath) : m_filePath(filePath), m_volume(1.0f) {
    // Load audio data from file
    std::cout << "Loading audio clip from: " << filePath << std::endl;
}

void AudioClip::play() {
    // Play audio
    std::cout << "Playing audio clip: " << m_filePath << std::endl;
}

void AudioClip::stop() {
    // Stop audio
    std::cout << "Stopping audio clip: " << m_filePath << std::endl;
}

void AudioClip::pause() {
    // Pause audio
    std::cout << "Pausing audio clip: " << m_filePath << std::endl;
}

void AudioClip::setVolume(float volume) {
    m_volume = volume;
    // Adjust volume
    std::cout << "Setting volume to: " << volume << " for audio clip: " << m_filePath << std::endl;
}

float AudioClip::getVolume() const {
    return m_volume;
}

AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

void AudioManager::loadAudioClip(const std::string& name, const std::string& filePath) {
    m_audioClips[name] = std::make_shared<AudioClip>(filePath);
}

std::shared_ptr<AudioClip> AudioManager::getAudioClip(const std::string& name) {
    return m_audioClips[name];
}

void AudioManager::playAudioClip(const std::string& name) {
    if (m_audioClips.find(name) != m_audioClips.end()) {
        m_audioClips[name]->play();
    }
}

void AudioManager::stopAudioClip(const std::string& name) {
    if (m_audioClips.find(name) != m_audioClips.end()) {
        m_audioClips[name]->stop();
    }
}

void AudioManager::setGlobalVolume(float volume) {
    m_globalVolume = volume;
    // Adjust global volume
    std::cout << "Setting global volume to: " << volume << std::endl;
}

} // namespace VGE
