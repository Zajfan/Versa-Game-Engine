#ifndef DIALOGUEMANAGER_H
#define DIALOGUEMANAGER_H

#include <string>
#include "NLUResult.h"
#include "KnowledgeBase.h"

class KnowledgeBase;

class DialogueManager {
public:
    DialogueManager();
    // ... (Constructor, destructor, other methods)

    void UpdateState(const NLUResult& nluResult, KnowledgeBase* knowledgeBase);
    std::string GenerateResponse(const std::string& personality, const std::string& emotion);
    void HandleNLUError();
    void HandleDialogueError();
    bool ShouldTriggerAction() const;
    std::string GetActionType() const;
    std::string GetActionParameters() const;
    // ... (Add other methods for dialogue management, e.g., context tracking, response generation)

    // Methods for handling events and generating specific responses
    std::string GenerateLocationBasedResponse(const std::string& location);
    std::string GenerateItemBasedResponse(const std::string& itemName);
    void AdjustDialogueStrategy(const std::string& emotion);
    // ...
};

#endif // DIALOGUEMANAGER_H