/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Teleporter
*/

#include "Teleporter.hpp"

namespace arcade
{
    Teleporter::Teleporter(float pos_x, float pos_y, char texture, Orientation orientation) : AEntity(pos_x, pos_y, texture, orientation)
    {
        _dest_x = 0;
        _dest_y = 0;
    }

    void Teleporter::setDest(float dest_x, float dest_y)
    {
        if (_orientation == Orientation::RIGHT)
        {
            _dest_x = dest_x + 1;
            _dest_y = dest_y;
        }
        else if (_orientation == Orientation::LEFT)
        {
            _dest_x = dest_x - 1;
            _dest_y = dest_y;
        }
    }

    float Teleporter::getDestX() const
    {
        return _dest_x;
    }

    float Teleporter::getDestY() const
    {
        return _dest_y;
    }

    void Teleporter::reset()
    {
    }
}
