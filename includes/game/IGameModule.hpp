/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include "AEvent.hpp"
#include "AEntity.hpp"

#include <vector>

namespace arcade
{
    /**
     * @brief Interface class for game modules.
     */
    class IGameModule
    {
    public:
        /**
         * @brief Virtual destructor for IGameModule.
         */
        virtual ~IGameModule() = default;

        /**
         * @brief Virtual function to check if the game module is running.
         * @return True if the game module is running, false otherwise.
         */
        virtual bool getIsRunning() const = 0;

        /**
         * @brief Virtual function to receive display data.
         * @param data The display data to receive.
         */
        virtual void receiveDisplayData(const struct DisplayData &data) = 0;

        /**
         * @brief Virtual function to get the game data.
         * @return A constant reference to the game data.
         */
        virtual const struct GameData &getGameData() const = 0;

        /**
         * @brief Virtual function to get system events.
         * @return A vector of system events.
         */
        virtual std::vector<AEvent> getSystemEvents() const = 0;

        /**
         * @brief Virtual function to get the player name.
         * @return The player name.
         */
        virtual std::string getPlayerName() const = 0;

        /**
         * @brief Virtual function to set the player name.
         * @param name The player name to set.
         */
        virtual void setPlayerName(const std::string &name) = 0;

        /**
         * @brief Virtual function to get the score.
         * @return The score.
         */
        virtual int getScore() const = 0;

        /**
         * @brief Virtual function to set the score.
         * @param score The score to set.
         */
        virtual void setScore(int score) = 0;

        /**
         * @brief Virtual function to get the highscore.
         * @return The highscore.
         */
        virtual int getHighscore() const = 0;

        /**
         * @brief Virtual function to set the highscore.
         * @param highscore The highscore to set.
         */
        virtual void setHighscore(int highscore) = 0;

        /**
         * @brief Virtual function to get the game name.
         * @return The game name.
         */
        virtual std::string getGameName() const = 0;

        /**
         * @brief Virtual function to set the game name.
         * @param game_to_load The game name to set.
         */
        virtual void setGameName(const std::string &game_to_load) = 0;

        /**
         * @brief Virtual function to get the graphic name.
         * @return The graphic name.
         */
        virtual std::string getGraphicName() const = 0;

        /**
         * @brief Virtual function to set the graphic name.
         * @param graphic_to_load The graphic name to set.
         */
        virtual void setGraphicName(const std::string &graphic_to_load) = 0;
    };
}

#endif /* !IGAMEMODULE_HPP_ */
