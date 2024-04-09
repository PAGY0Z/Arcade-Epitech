/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** AGraphic
*/

#ifndef AGRAPHIC_HPP_
#define AGRAPHIC_HPP_

#include "IDisplayModule.hpp"
#include "AException.hpp"

namespace arcade
{
    class AGraphic : public IDisplayModule
    {
    public:
        virtual ~AGraphic() = default;

        virtual bool getIsRunning() const = 0;
        virtual const struct DisplayData &getDisplayData() const = 0;
        virtual void receiveGameData(const struct GameData &data) = 0;
    };

    class AGraphicException : public AException
    {
    public:
        AGraphicException(const std::string &additionnal_message, const std::string &file_data);
        virtual ~AGraphicException() = default;
    };
}
#endif /* !AGRAPHIC_HPP_ */
