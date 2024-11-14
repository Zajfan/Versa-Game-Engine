#ifndef UIFILEDIALOG_H
#define UIFILEDIALOG_H

#include "UIElement.h"
#include <string>
#include <functional>

class UIFileDialog : public UIElement
{
public:
    enum class DialogType { Open, Save };
    enum class Result { OK, Cancel };

    UIFileDialog(DialogType type, const std::string& title, const std::string& initialDirectory = "", const std::string& filter = "");

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Properties
    std::string Title;
    std::string InitialDirectory;
    std::string Filter; // File type filter (e.g., "Text Files (*.txt)|*.txt|All Files (*.*)|*.*")
    std::string SelectedFilePath;
    Result DialogResult = Result::Cancel; // Initially set to Cancel

    // Callback function to be called when the dialog is closed
    std::function<void(Result result, const std::string& filePath)> OnCloseCallback;

private:
    // ... (Helper functions or member variables)
    // For example:
    // - std::vector<std::string> fileEntries_; // To store the list of files in the current directory
    // - int selectedFileIndex_; // To track the selected file in the list
};

#endif // UIFILEDIALOG_H