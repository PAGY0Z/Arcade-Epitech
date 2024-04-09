/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** AEvent
*/

#include "AEvent.hpp"

namespace arcade
{
    AEvent::AEvent(Type_e type, float value_x, float value_y)
    {
        _type = type;
        _value_x = value_x;
        _value_y = value_y;
    }

    Type_e AEvent::getType() const
    {
        return _type;
    }

    float AEvent::getValueX() const
    {
        return _value_x;
    }

    float AEvent::getValueY() const
    {
        return _value_y;
    }
}
