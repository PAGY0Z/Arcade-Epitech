/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include "AEvent.hpp"
#include "AEntity.hpp"

#include <vector>

namespace arcade
{
    /**
     * @brief Interface class for display modules.
     */
    class IDisplayModule
    {
    public:
        /**
         * @brief Virtual destructor for IDisplayModule.
         */
        virtual ~IDisplayModule() = default;

        /**
         * @brief Virtual function to check if the display module is running.
         * @return True if the display module is running, false otherwise.
         */
        virtual bool getIsRunning() const = 0;

        /**
         * @brief Virtual function to get the display data.
         * @return A constant reference to the display data.
         */
        virtual const struct DisplayData &getDisplayData() const = 0;

        /**
         * @brief Virtual function to receive game data.
         * @param data The game data to receive.
         */
        virtual void receiveGameData(const struct GameData &data) = 0;
    };
}

#endif /* !IDISPLAYMODULE_HPP_ */
