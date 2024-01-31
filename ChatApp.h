//
// Created by pablo-chacon on 2024-01-26.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


#ifndef CHAT_APP_FINAL_CHATAPP_H
#define CHAT_APP_FINAL_CHATAPP_H


/**
 * This project is based on:
 * https://tldp.org/LDP/LG/issue74/tougher.html
 * namespace to prevent conflict.
 */
namespace ChatApp {

    /**
    * @class Channel
    * Chat channel, name and history.
    */
    class Channel {
    private:
        std::string name;
        std::vector<std::string> messages;

    public:
        /**
        * Constructs channel
        * @param channelName
        */
        Channel(const std::string& channelName) : name(channelName) {}

        /**
        * Return channelName
        * @return std::string.
        */
        std::string getName() const { return name; }

        /**
        * Add message.
        * @param message
        */
        void addMessage(const std::string& message) { messages.push_back(message); }

        /**
        * Returns history.
        * @return std::vector<std::string>
        */
        [[nodiscard]] std::vector<std::string> getChatHistory() const { return messages; }
    };

    /**
    * @class ChatServer
    * Represents a chat server that manages multiple chat channels.
    */
    class ChatServer {
    private:
        std::vector<Channel*> channels;

    public:
        /**
        * Creates channel.
        * @param channelName
        */
        void createChannel(const std::string& channelName) {
            Channel* newChannel = new Channel(channelName);
            channels.push_back(newChannel);
        }

        /**
        * Delete channel.
        * @param channelName
        */
        void deleteChannel(const std::string& channelName) {
            for (auto it = channels.begin(); it != channels.end(); ++it) {
                if ((*it)->getName() == channelName) {
                    delete *it;
                    channels.erase(it);
                    break;
                }
            }
        }

        /**
        * Returns channel list.
        * @return std::vector<std::string>
        */
        std::vector<std::string> getChannelList() const {
            std::vector<std::string> channelList;
            for (const auto& channel : channels) {
                channelList.push_back(channel->getName());
            }
            return channelList;
        }
    };

    /**
    * @class ChatAppIO
    * input/output operations.
    */
    class ChatAppIO {
    private:
        std::string filename;

    public:
        /**
        * Constructs ChatIO object.
        * @param file
        ChatAppIO(const std::string& file) : filename(file) {}

        /**
        * Saves history.
        * @param channel
        */
        void saveChatHistory(const Channel& channel) {
            std::ofstream file(filename, std::ios::app);
            if (file.is_open()) {
                file << "Channel: " << channel.getName() << "\n";
                for (const auto& message : channel.getChatHistory()) {
                    file << message << "\n";
                }
                file << "\n";
                file.close();
            }
        }

        /**
        * Reads history.
        * @return std::vector<std::string>
        */
        std::vector<std::string> readChatHistory() {
            std::vector<std::string> chatHistory;
            std::ifstream file(filename);
            if (file.is_open()) {
                std::string line;
                while (std::getline(file, line)) {
                    chatHistory.push_back(line);
                }
                file.close();
            }
            return chatHistory;
        }

        /**
        * Update history.
        * @param chatHistory
        */
        void updateChatHistory(const std::vector<std::string>& chatHistory) {
            std::ofstream file(filename);
            if (file.is_open()) {
                for (const auto& line : chatHistory) {
                    file << line << "\n";
                }
                file.close();
            }
        }

        /**
        * Delete history.
        */
        void deleteChatHistory() {
            remove(filename.c_str());
        }
    };
}

#endif //CHAT_APP_FINAL_CHATAPP_H
