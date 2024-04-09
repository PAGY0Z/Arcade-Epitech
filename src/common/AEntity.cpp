/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** AEntity
*/

#include "AEntity.hpp"

namespace arcade
{
    AEntity::AEntity(float pos_x, float pos_y, char texture, Orientation orientation)
    {
        _pos_x = pos_x;
        _pos_y = pos_y;
        _texture = texture;
        _orientation = orientation;
    }

    float AEntity::getPosX() const
    {
        return _pos_x;
    }

    float AEntity::getPosY() const
    {
        return _pos_y;
    }

    char AEntity::getTexture() const
    {
        return _texture;
    }

    Orientation AEntity::getOrientation() const
    {
        return _orientation;
    }

    void AEntity::setOrientation(Orientation orientation)
    {
        _orientation = orientation;
    }

    void AEntity::setTexture(char texture)
    {
        _texture = texture;
    }

    bool AEntity::collide_with(AEntity other)
    {
        int other_x = other.getPosX() + 0.5;
        int other_y = other.getPosY() + 0.5;
        int this_x = _pos_x + 0.5;
        int this_y = _pos_y + 0.5;

        if (other_x == this_x && other_y == this_y)
            return true;
        return false;
    }

    void AEntity::setPosX(float pos_x)
    {
        _pos_x = pos_x;
    }

    void AEntity::setPosY(float pos_y)
    {
        _pos_y = pos_y;
    }
}
