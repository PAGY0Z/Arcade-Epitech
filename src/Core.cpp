/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Core
*/

#include "Core.hpp"
#include "AException.hpp"
#include <filesystem>

namespace arcade
{
    Core::Core(const std::string &lib_path)
    {
        try
        {
            _display_dl_manager = new DLManager<IDisplayModule>(1);
            if (_display_dl_manager == nullptr)
                throw CoreException("Failed to create DLManager<IDisplayModule>", FILE_DATA);
            _game_dl_manager = new DLManager<IGameModule>(0);
            if (_game_dl_manager == nullptr)
                throw CoreException("Failed to create DLManager<IGameModule>", FILE_DATA);
            _display = _display_dl_manager->loadLibrary(lib_path);
            _game = _game_dl_manager->loadLibrary("./lib/arcade_menu.so");
            _game->setGameName("./lib/arcade_pacman.so");
            _game->setGraphicName(lib_path);
        }
        catch (const AException &except)
        {
            std::cerr << except.what() << std::endl;
            exit(except.getReturnValue());
        }
    }

    Core::~Core()
    {
        if (_display)
            _display_dl_manager->unloadLibrary(_display);
        if (_game)
            _game_dl_manager->unloadLibrary(_game);
        _display_dl_manager->~DLManager();
        _game_dl_manager->~DLManager();
        delete _display_dl_manager;
        delete _game_dl_manager;
    }

    int Core::run()
    {
        std::string gameName = "";
        std::string playerName = "";
        std::string graphicName = "";
        try
        {
            while (true)
            {
                if (!_display->getIsRunning())
                    break;
                if (!_game->getIsRunning())
                {
                    gameName = _game->getGameName();
                    playerName = _game->getPlayerName();
                    graphicName = _game->getGraphicName();
                    writeHighScore(_game->getScore(), gameName, playerName);
                    _game_dl_manager->unloadLibrary(_game);
                    _game = _game_dl_manager->loadLibrary(gameName);
                    _display_dl_manager->unloadLibrary(_display);
                    _display = _display_dl_manager->loadLibrary(graphicName);
                    _game->setGameName(gameName);
                    _game->setGraphicName(graphicName);
                    _game->setPlayerName(playerName);
                    _game->setHighscore(parseHighScore(gameName));
                }
                _game->receiveDisplayData(_display->getDisplayData());
                _display->receiveGameData(_game->getGameData());
                receiveSystemEvents(_game->getSystemEvents());
            }
            return 0;
        }
        catch (const AException &except)
        {
            std::cerr << except.what() << std::endl;
            return except.getReturnValue();
        }
    }

    void Core::receiveSystemEvents(const std::vector<AEvent> &events)
    {
        std::string gameName = "";
        std::string graphicName = "";
        std::string playerName = "";
        std::string nextGameName = "";
        std::string nextGraphicName = "";
        for (auto &event : events)
        {
            if (event.getType() == Type_e::NUM8)
            {
                gameName = _game->getGameName();
                playerName = _game->getPlayerName();
                graphicName = _game->getGraphicName();
                nextGameName = getNextGameLibrary(gameName);
                _game_dl_manager->unloadLibrary(_game);
                _game = _game_dl_manager->loadLibrary(nextGameName);
                gameName = nextGameName;
                _game->setGameName(gameName);
                _game->setGraphicName(graphicName);
                _game->setPlayerName(playerName);
                _game->setHighscore(parseHighScore(gameName));
            }
            else if (event.getType() == Type_e::NUM2)
            {
                gameName = _game->getGameName();
                playerName = _game->getPlayerName();
                graphicName = _game->getGraphicName();
                nextGameName = getPreviousGameLibrary(gameName);
                _game_dl_manager->unloadLibrary(_game);
                _game = _game_dl_manager->loadLibrary(nextGameName);
                gameName = nextGameName;
                _game->setGameName(gameName);
                _game->setGraphicName(graphicName);
                _game->setPlayerName(playerName);
                _game->setHighscore(parseHighScore(gameName));
            }
            else if (event.getType() == Type_e::NUM4)
            {
                graphicName = _game->getGraphicName();
                nextGraphicName = getPreviousGraphicLibrary(graphicName);
                _display_dl_manager->unloadLibrary(_display);
                _display = _display_dl_manager->loadLibrary(nextGraphicName);
                graphicName = nextGraphicName;
                _game->setGraphicName(graphicName);
            }
            else if (event.getType() == Type_e::NUM6)
            {
                graphicName = _game->getGraphicName();
                nextGraphicName = getNextGraphicLibrary(graphicName);
                _display_dl_manager->unloadLibrary(_display);
                _display = _display_dl_manager->loadLibrary(nextGraphicName);
                graphicName = nextGraphicName;
                _game->setGraphicName(graphicName);
            }
            else if (event.getType() == Type_e::NUM5)
            {
                gameName = _game->getGameName();
                playerName = _game->getPlayerName();
                graphicName = _game->getGraphicName();
                nextGameName = gameName;
                _game_dl_manager->unloadLibrary(_game);
                _game = _game_dl_manager->loadLibrary(nextGameName);
                gameName = nextGameName;
                _game->setGameName(gameName);
                _game->setGraphicName(graphicName);
                _game->setPlayerName(playerName);
                _game->setHighscore(parseHighScore(gameName));
            }
            else if (event.getType() == Type_e::NUM0)
            {
                gameName = _game->getGameName();
                playerName = _game->getPlayerName();
                graphicName = _game->getGraphicName();
                nextGameName = "./lib/arcade_menu.so";
                _game_dl_manager->unloadLibrary(_game);
                _game = _game_dl_manager->loadLibrary(nextGameName);
                gameName = nextGameName;
                _game->setGameName(gameName);
                _game->setGraphicName(graphicName);
                _game->setPlayerName(playerName);
                _game->setHighscore(parseHighScore(gameName));
            }
            else if (event.getType() == Type_e::ESCAPE)
            {
                _display_dl_manager->unloadLibrary(_display);
                _game_dl_manager->unloadLibrary(_game);
                exit(0);
            }
            else if (event.getType() == Type_e::GET_HIGHSCORE)
            {
                int highscore = parseHighScore(_game->getGameName());
                _game->setHighscore(highscore);
            }
            else if (event.getType() == Type_e::GET_NEXT_GAME_LIBRARY)
            {
                std::string nextLib = getNextGameLibrary(_game->getGameName());
                int highscore = parseHighScore(nextLib);
                _game->setGameName(nextLib);
                _game->setHighscore(highscore);
            }
            else if (event.getType() == Type_e::GET_PREVIOUS_GAME_LIBRARY)
            {
                std::string nextLib = getPreviousGameLibrary(_game->getGameName());
                int highscore = parseHighScore(nextLib);
                _game->setGameName(nextLib);
                _game->setHighscore(highscore);
            }
            else if (event.getType() == Type_e::GET_NEXT_GRAPHIC_LIBRARY)
            {
                _game->setGraphicName(getNextGraphicLibrary(_game->getGraphicName()));
            }
            else if (event.getType() == Type_e::GET_PREVIOUS_GRAPHIC_LIBRARY)
            {
                _game->setGraphicName(getPreviousGraphicLibrary(_game->getGraphicName()));
            }
        }
    }

    std::vector<std::string> Core::getFilesInDirectory(const std::string &directory)
    {
        std::vector<std::string> files;
        for (const auto &entry : std::filesystem::directory_iterator(directory))
        {
            if (entry.is_regular_file())
                if (entry.path().extension() == ".so")
                    files.push_back(entry.path());
        }
        return files;
    }

    std::string Core::getNextGameLibrary(std::string currentLib)
    {
        std::vector<std::string> files = getFilesInDirectory("lib/");
        std::string nextLib = currentLib;
        bool found = false;
        int index = 0;

        for (int i = 0; i < (int)files.size(); i++)
        {
            if (files[i] == currentLib)
            {
                index = i;
                found = true;
                break;
            }
        }

        int i = index;
        if (found) {
            do {
                i = (i + 1) % (int)files.size();
                if (_game_dl_manager->isLibraryUsingInterface(files[i]))
                {
                    nextLib = files[i];
                    break;
                }
            } while (i != index);
        } else {
            for (int i = 0; i < (int)files.size(); i++)
            {
                if (_game_dl_manager->isLibraryUsingInterface(files[i]))
                {
                    nextLib = files[i];
                    break;
                }
            }
        }
        return nextLib;
    }

std::string Core::getPreviousGameLibrary(std::string currentLib)
{
    std::vector<std::string> files = getFilesInDirectory("lib/");
    std::string nextLib = currentLib;
    bool found = false;
    int index = 0;

    for (int i = 0; i < (int)files.size(); i++)
    {
        if (files[i] == currentLib)
        {
            index = i;
            found = true;
            break;
        }
    }

    if (found) {
        int i = index;
        do {
            i = (i - 1 + files.size()) % files.size();
            if (_game_dl_manager->isLibraryUsingInterface(files[i]))
            {
                nextLib = files[i];
                break;
            }
        } while (i != index);
    } else {
        for (int i = 0; i < (int)files.size(); i++)
        {
            if (_game_dl_manager->isLibraryUsingInterface(files[i]))
            {
                nextLib = files[i];
                break;
            }
        }
    }
    return nextLib;
}

    std::string Core::getNextGraphicLibrary(std::string currentLib)
    {
        std::vector<std::string> files = getFilesInDirectory("lib/");
        std::string nextLib = currentLib;
        bool found = false;
        int index = 0;

        for (int i = 0; i < (int)files.size(); i++)
        {
            if (files[i] == currentLib)
            {
                index = i;
                found = true;
                break;
            }
        }

        int i = index;
        if (found) {
            do {
                i = (i + 1) % (int)files.size();
                if (_display_dl_manager->isLibraryUsingInterface(files[i]))
                {
                    nextLib = files[i];
                    break;
                }
            } while (i != index);
        } else {
            for (int i = 0; i < (int)files.size(); i++)
            {
                if (_display_dl_manager->isLibraryUsingInterface(files[i]))
                {
                    nextLib = files[i];
                    break;
                }
            }
        }
        return nextLib;
    }

    std::string Core::getPreviousGraphicLibrary(std::string currentLib)
    {
        std::vector<std::string> files = getFilesInDirectory("lib/");
        std::string nextLib = currentLib;
        bool found = false;
        int index = 0;

        for (int i = 0; i < (int)files.size(); i++)
        {
            if (files[i] == currentLib)
            {
                index = i;
                found = true;
                break;
            }
        }

        if (found) {
            int i = index;
            do {
                i = (i - 1 + files.size()) % files.size();
                if (_display_dl_manager->isLibraryUsingInterface(files[i]))
                {
                    nextLib = files[i];
                    break;
                }
            } while (i != index);
        } else {
            for (int i = 0; i < (int)files.size(); i++)
            {
                if (_display_dl_manager->isLibraryUsingInterface(files[i]))
                {
                    nextLib = files[i];
                    break;
                }
            }
        }
        return nextLib;
    }


    std::string Core::getGameName(const std::string &libName)
    {
        std::size_t startPos = libName.find_first_of('_');
        std::size_t endPos = libName.find_last_of('.');
        std::string name = libName.substr(startPos + 1, endPos - startPos - 1);

        return name;
    }

    bool Core::writeHighScore(int score, const std::string &libName, const std::string &playerName)
    {
        std::string gameName = getGameName(libName);
        std::ofstream file;
        std::string scoreLine;

        try {
            file.open("assets/highscores/" + gameName, std::ios::app);
            if (file.fail())
            {
                throw CoreException("could not open file: " + libName, FILE_DATA);
                return false;
            }
            if (playerName.length() > 10)
            {
                throw CoreException("Player name is too long: " + playerName, FILE_DATA);
                return false;
            }
        } catch (const arcade::AException &except) {
            std::cerr << except.what() << std::endl;
            exit(except.getReturnValue());
        }
        scoreLine = playerName + ":" + std::to_string(score) + "\n";
        file << scoreLine;
        file.close();
        return true;
    }

    int Core::parseHighScore(const std::string &libName)
    {
        std::ifstream file;
        std::string gameName = getGameName(libName);
        std::string scoreLine = "";
        int score = -1;
        int max = -1;

        if (!std::filesystem::exists("assets/highscores")) {
            std::filesystem::create_directory("assets/highscores/");
        }
        try
        {
            file.open("assets/highscores/" + gameName, std::ios::app);
            if (file.fail())
            {
                throw CoreException("could not open file: " + libName, FILE_DATA);
            }
        }
        catch (const arcade::AException &except)
        {
            std::cerr << except.what() << std::endl;
            exit(except.getReturnValue());
        }

        while (getline(file, scoreLine))
        {
            score = atoi(scoreLine.substr(scoreLine.find_last_of(':') + 1).c_str());
            max = (score > max) ? score : max;
        }
        return max;
    }

    CoreException::CoreException(const std::string &additionnal_message, const std::string &file_data) : AException("", additionnal_message, file_data)
    {
        _message = "CoreException : " + _message;
    }
}
