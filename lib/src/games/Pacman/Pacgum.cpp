/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Pacgum
*/

#include "Pacgum.hpp"

namespace arcade
{
    Pacgum::Pacgum(float pos_x, float pos_y, char texture, Orientation orientation, bool is_super) : AEntity(pos_x, pos_y, texture, orientation)
    {
        _is_super = is_super;
        _is_eaten = false;
    }

    bool Pacgum::getIsEaten() const
    {
        return _is_eaten;
    }

    void Pacgum::eaten()
    {
        _is_eaten = true;
    }

    bool Pacgum::getIsSuper() const
    {
        return _is_super;
    }

    void Pacgum::reset()
    {
        _is_eaten = false;
    }
}
