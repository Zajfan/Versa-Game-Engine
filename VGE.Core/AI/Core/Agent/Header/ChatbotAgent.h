// VersaEngineAI/core/agent/ChatbotAgent.h

#include "Agent.h"
#include "NLUComponent.h"
#include "DialogueManager.h"
#include "KnowledgeBase.h"
#include "Logger.h"
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>
#include <google/cloud/texttospeech/v1/text_to_speech.h> // Include the TTS client library header

namespace {
    auto constexpr kEndpoint = "texttospeech.googleapis.com";
}
namespace gc = ::google::cloud;
namespace tts = ::google::cloud::texttospeech_v1;

namespace VersaEngine {
    namespace AI {

        class ChatbotAgent : public Agent {
        public:
            ChatbotAgent(const std::string& name = "Chatbot", Logger* logger = nullptr);
            ~ChatbotAgent();

            void ProcessUserInput(const std::string& text) override;
            std::string GenerateResponse() override;

            void SetPersonality(const std::string& personalityType);
            void AddKnowledge(const std::string& question, const std::string& answer);
            void ClearConversationHistory();

            const std::vector<std::string>& GetConversationHistory() const { return conversationHistory_; }

            using ActionCallback = std::function<void(const std::string& actionType, const std::string& parameters)>;
            void SetActionCallback(ActionCallback callback);

            void SetEmotion(const std::string& emotion);
            void SetCurrentLocation(const std::string& location);
            void ObserveEvent(const std::string& eventType, const std::string& eventData);

            void SetLanguage(const std::string& languageCode);
            void Speak(const std::string& text);
            std::string Listen();

            void SetUserData(const std::string& userId, const std::string& key, const std::string& value);
            std::string GetUserData(const std::string& userId, const std::string& key) const;

        private:
            std::unique_ptr<NLUComponent> nlu_;
            std::unique_ptr<DialogueManager> dialogue_;
            std::unique_ptr<KnowledgeBase> knowledge_;
            std::string name_;
            std::string personality_;
            std::vector<std::string> conversationHistory_;
            ActionCallback actionCallback_;
            std::string currentEmotion_;
            std::string currentLocation_;
            Logger* logger_;
            std::string languageCode_;
            std::unordered_map<std::string, std::unordered_map<std::string, std::string>> userData_;
        };

    } // namespace AI
} // namespace VersaEngine