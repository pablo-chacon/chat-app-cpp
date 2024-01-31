//
// Created by pablo-chacon on 2024-01-26.
//

#include <iostream>
#include "ChatApp.h"


int main() {
    // Server instance.
    ChatApp::ChatServer chatServer;

    // Create ChatAppIO instance.
    ChatApp::ChatAppIO chatAppIO("chat_history.txt");

    // Create and delete channels.
    chatServer.createChannel("General");
    chatServer.createChannel("Random");
    chatServer.createChannel("Bad jokes");
    chatServer.deleteChannel("Bad jokes");

    // Saving and reading history.
    ChatApp::Channel generalChannel("General");
    generalChannel.addMessage("User1: Hello customer!");
    generalChannel.addMessage("User2: Hi salesman!");
    chatAppIO.saveChatHistory(generalChannel);

    std::vector<std::string> chatHistory = chatAppIO.readChatHistory();
    for (const auto& line : chatHistory) {
        std::cout << line << "\n";
    }

    // Updating and deleting history.
    chatHistory.emplace_back("User3: What's your offer?");
    chatAppIO.updateChatHistory(chatHistory);

    chatAppIO.deleteChatHistory();

    return 0;
}