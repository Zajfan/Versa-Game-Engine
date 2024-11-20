#include "../Platform/Header Files/VGE.WindowsPlatform.h"
#include <gtest/gtest.h>

namespace VGE {

class WindowsPlatformTests : public ::testing::Test {
protected:
    void SetUp() override {
        platform = std::make_unique<WindowsPlatform>();
        platform->initialize();
    }

    void TearDown() override {
        platform->shutdown();
    }

    std::unique_ptr<WindowsPlatform> platform;
};

TEST_F(WindowsPlatformTests, Initialization) {
    EXPECT_TRUE(platform->initialize());
}

TEST_F(WindowsPlatformTests, FileExists) {
    EXPECT_FALSE(platform->fileExists("nonexistent_file.txt"));
}

TEST_F(WindowsPlatformTests, CreateAndRemoveDirectory) {
    std::string testDir = "test_dir";
    EXPECT_TRUE(platform->createDirectory(testDir));
    EXPECT_TRUE(platform->removeDirectory(testDir));
}

TEST_F(WindowsPlatformTests, CreateAndDeleteFile) {
    std::string testFile = "test_file.txt";
    std::ofstream outFile(testFile);
    outFile << "test";
    outFile.close();
    EXPECT_TRUE(platform->fileExists(testFile));
    EXPECT_TRUE(platform->deleteFile(testFile));
}

// Add more tests for other functionalities as needed

} // namespace VGE
