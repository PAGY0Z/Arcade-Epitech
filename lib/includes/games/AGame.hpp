/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** AGame
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_

#include "IGameModule.hpp"
#include "AException.hpp"

namespace arcade
{
    class AGame : public IGameModule
    {
    public:
        virtual ~AGame() = default;

        virtual bool getIsRunning() const = 0;
        virtual void receiveDisplayData(const struct DisplayData &data) = 0;
        virtual const struct GameData &getGameData() const = 0;
        virtual std::vector<AEvent> getSystemEvents() const = 0;

        std::string getPlayerName() const final;
        void setPlayerName(const std::string &name) final;

        int getScore() const final;
        void setScore(int score) final;

        int getHighscore() const final;
        void setHighscore(int highscore) final;

        std::string getGameName() const final;
        void setGameName(const std::string &game_to_load) final;

        std::string getGraphicName() const final;
        void setGraphicName(const std::string &graphic_to_load) final;

    protected:
        std::string _player_name;
        int _score = 0;
        int _highscore = 0;
        std::string _game_name;
        std::string _graphic_name;
        bool _is_highscore_set = false;
    };

    class AGameException : public AException
    {
    public:
        AGameException(const std::string &additionnal_message, const std::string &file_data);
        virtual ~AGameException() = default;
    };
}

#endif /* !AGAME_HPP_ */
