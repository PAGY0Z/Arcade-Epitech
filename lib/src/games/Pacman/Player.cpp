/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Player
*/

#include "Player.hpp"

namespace arcade
{
    Player::Player(float pos_x, float pos_y, char texture, Orientation orientation) : AEntity(pos_x, pos_y, texture, orientation)
    {
        _speed_x = orientation == Orientation::LEFT ? -_reference_speed : 0;
        _speed_x = orientation == Orientation::RIGHT ? _reference_speed : _speed_x;
        _speed_y = orientation == Orientation::UP ? -_reference_speed : 0;
        _speed_y = orientation == Orientation::DOWN ? _reference_speed : _speed_y;
        _initial_pos_x = pos_x;
        _initial_pos_y = pos_y;
    }

    void Player::move(float delta_time, std::vector<Wall> walls)
    {
        float new_pos_x = _pos_x + _speed_x * delta_time;
        float new_pos_y = _pos_y + _speed_y * delta_time;

        if (_speed_x == 0)
            new_pos_x = (int)(new_pos_x + 0.5);
        if (_speed_y == 0)
            new_pos_y = (int)(new_pos_y + 0.5);
        for (auto &wall : walls)
        {
            if (collide_with(wall))
            {
                if (_speed_x > 0)
                {
                    new_pos_x = wall.getPosX() - 1;
                    _speed_x = 0;
                }
                if (_speed_x < 0)
                {
                    new_pos_x = wall.getPosX() + 1;
                    _speed_x = 0;
                }
                if (_speed_y > 0)
                {
                    new_pos_y = wall.getPosY() - 1;
                    _speed_y = 0;
                }
                if (_speed_y < 0)
                {
                    new_pos_y = wall.getPosY() + 1;
                    _speed_y = 0;
                }
                break;
            }
        }

        _pos_x = new_pos_x;
        _pos_y = new_pos_y;
    }

    void Player::setOrientation(Orientation orientation, std::vector<Wall> walls)
    {
        if (orientation == _orientation)
            return;

        for (auto &wall : walls)
        {
            if (collide_with(wall))
                return;
        }

        Orientation old_orientation = _orientation;
        float old_speed_x = _speed_x;
        float old_speed_y = _speed_y;
        float old_pos_x = _pos_x;
        float old_pos_y = _pos_y;

        _speed_x = 0;
        _speed_y = 0;
        _pos_x = (int)(_pos_x + 0.5);
        _pos_y = (int)(_pos_y + 0.5);
        _orientation = orientation;

        if (_orientation == Orientation::LEFT)
            _pos_x -= 1;
        if (_orientation == Orientation::RIGHT)
            _pos_x += 1;
        if (_orientation == Orientation::UP)
            _pos_y -= 1;
        if (_orientation == Orientation::DOWN)
            _pos_y += 1;

        for (auto &wall : walls)
        {
            if (collide_with(wall))
            {
                _speed_x = old_speed_x;
                _speed_y = old_speed_y;
                _pos_x = old_pos_x;
                _pos_y = old_pos_y;
                _orientation = old_orientation;
                return;
            }
        }

        _speed_x = orientation == Orientation::LEFT ? -_reference_speed : 0;
        _speed_x = orientation == Orientation::RIGHT ? _reference_speed : _speed_x;
        _speed_y = orientation == Orientation::UP ? -_reference_speed : 0;
        _speed_y = orientation == Orientation::DOWN ? _reference_speed : _speed_y;
        _pos_x = old_pos_x;
        _pos_y = old_pos_y;
        _orientation = orientation;
    }

    void Player::die()
    {
        lives_remaining -= 1;
    }

    int Player::getLivesRemaining() const
    {
        return lives_remaining;
    }

    void Player::respawn()
    {
        _pos_x = _initial_pos_x;
        _pos_y = _initial_pos_y;
        setOrientation(Orientation::LEFT, {});
        setOrientation(Orientation::RIGHT, {});
    }

    void Player::reset()
    {
        _pos_x = _initial_pos_x;
        _pos_y = _initial_pos_y;
        setOrientation(Orientation::LEFT, {});
        setOrientation(Orientation::RIGHT, {});
        lives_remaining = lives_remaining + 1;
        _reference_speed = _reference_speed * 1.1;
    }

    void Player::teleport(Teleporter &teleporter)
    {
        _pos_x = teleporter.getDestX();
        _pos_y = teleporter.getDestY();
        _orientation = teleporter.getOrientation();
    }
}
