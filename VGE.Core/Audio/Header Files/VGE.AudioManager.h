#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace VGE {

class AudioClip {
public:
    AudioClip(const std::string& filePath);
    void play();
    void stop();
    void pause();
    void setVolume(float volume);
    float getVolume() const;

private:
    std::string m_filePath;
    float m_volume;
    // Add audio data and playback state
};

class AudioManager {
public:
    static AudioManager& getInstance();

    void loadAudioClip(const std::string& name, const std::string& filePath);
    std::shared_ptr<AudioClip> getAudioClip(const std::string& name);
    void playAudioClip(const std::string& name);
    void stopAudioClip(const std::string& name);
    void setGlobalVolume(float volume);

private:
    AudioManager() = default;
    std::unordered_map<std::string, std::shared_ptr<AudioClip>> m_audioClips;
    float m_globalVolume;
};

} // namespace VGE
