/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** AGame
*/

#include "AGame.hpp"

namespace arcade
{
    std::string AGame::getPlayerName() const
    {
        return _player_name;
    }

    void AGame::setPlayerName(const std::string &name)
    {
        _player_name = name;
    }

    int AGame::getScore() const
    {
        return _score;
    }

    void AGame::setScore(int score)
    {
        _score = score;
    }

    int AGame::getHighscore() const
    {
        return _highscore;
    }

    void AGame::setHighscore(int highscore)
    {
        _highscore = highscore;
        _is_highscore_set = true;
    }

    std::string AGame::getGameName() const
    {
        return _game_name;
    }

    void AGame::setGameName(const std::string &game_name)
    {
        _game_name = game_name;
    }

    std::string AGame::getGraphicName() const
    {
        return _graphic_name;
    }

    void AGame::setGraphicName(const std::string &graphic_name)
    {
        _graphic_name = graphic_name;
    }

    AGameException::AGameException(const std::string &additionnal_message, const std::string &file_data) : AException("", additionnal_message, file_data)
    {
        _message = "AGameException : " + _message;
    }
}
