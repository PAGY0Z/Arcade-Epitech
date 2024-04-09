/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Wall
*/

#include "Wall.hpp"

namespace arcade
{
    Wall::Wall(float pos_x, float pos_y, char texture, Orientation orientation, bool is_temporary) : AEntity(pos_x, pos_y, texture, orientation)
    {
        _is_temporary = is_temporary;
    }

    bool Wall::getIsTemporary() const
    {
        return _is_temporary;
    }

    bool Wall::getIsOpen() const
    {
        return _is_open;
    }

    void Wall::open()
    {
        _is_open = true;
    }

    void Wall::update(float deltaTime)
    {
        if (_is_temporary)
        {
            if (!_is_open)
            {
                _time_to_open -= deltaTime;
                if (_time_to_open <= 0)
                {
                    open();
                }
            }
        }
    }

    void Wall::reset()
    {
        _is_open = false;
        _time_to_open = 10;
    }
}
