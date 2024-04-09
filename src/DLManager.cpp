/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** DLManager
*/

#include "DLManager.hpp"

namespace arcade
{
    DLManagerException::DLManagerException(const std::string &additionnal_message, const std::string &file_data) : AException("", additionnal_message, file_data)
    {
        _message = "DLManagerException : " + _message;
    }
}
