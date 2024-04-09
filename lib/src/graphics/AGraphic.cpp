/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** AGraphic
*/

#include "AGraphic.hpp"

namespace arcade
{
    AGraphicException::AGraphicException(const std::string &additionnal_message, const std::string &file_data) : AException("", additionnal_message, file_data)
    {
        _message = "AGraphicException : " + _message;
    }
}
