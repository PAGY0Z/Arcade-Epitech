/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include <memory>
#include <filesystem>
#include "AException.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "AEvent.hpp"
#include "AEntity.hpp"
#include "DLManager.hpp"
#include <fstream>

namespace arcade
{
    /**
     * @brief Class representing the core functionality of the arcade system.
     */
    class Core
    {
    private:
        IDisplayModule *_display;                           /**< Pointer to the current display module. */
        IGameModule *_game;                                 /**< Pointer to the current game module. */
        DLManager<IDisplayModule> *_display_dl_manager;     /**< Pointer to the display module dynamic library manager. */
        DLManager<IGameModule> *_game_dl_manager;           /**< Pointer to the game module dynamic library manager. */

        /**
         * @brief Helper function to get the files in a directory.
         * @param directory The directory path.
         * @return A vector containing the names of files in the directory.
         */
        std::vector<std::string> getFilesInDirectory(const std::string &directory);

        // Functions for loading libraries
        std::string getNextGameLibrary(std::string currentLib);
        std::string getPreviousGameLibrary(std::string currentLib);
        std::string getNextGraphicLibrary(std::string currentLib);
        std::string getPreviousGraphicLibrary(std::string currentLib);

        // Function for handling system events
        void receiveSystemEvents(const std::vector<AEvent> &events);

        // Functions for handling high scores
        bool writeHighScore(int score, const std::string& libName, const std::string& playerName);
        int parseHighScore(const std::string& libName);
        std::string getGameName(const std::string& libName);

    public:
        /**
         * @brief Constructor for Core.
         * @param lib_path The path to the directory containing dynamic libraries.
         */
        Core(const std::string &lib_path);

        /**
         * @brief Destructor for Core.
         */
        ~Core();

        /**
         * @brief Function to run the arcade system.
         * @return An integer indicating the exit status of the system.
         */
        int run();
    };

    /**
     * @brief Exception class specifically for Core-related errors.
     */
    class CoreException : public AException
    {
    public:
        /**
         * @brief Constructor for CoreException.
         * @param additionnal_message Additional message associated with the exception.
         * @param file_data Information about the file, line number, and function where the exception occurred.
         */
        CoreException(const std::string &additionnal_message, const std::string &file_data);

        /**
         * @brief Virtual destructor for CoreException.
         */
        virtual ~CoreException() = default;
    };
}

#endif /* !CORE_HPP_ */
