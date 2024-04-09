/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Ghost
*/

#include "Ghost.hpp"
#include <iostream>

namespace arcade
{
    Ghost::Ghost(float pos_x, float pos_y, char texture, Orientation orientation, float asleep_time) : AEntity(pos_x, pos_y, texture, orientation)
    {
        _is_scared = false;
        _is_alive = true;
        _is_asleep = true;
        _asleep_time = asleep_time;
        asleep_time_reference = asleep_time;
        _initial_pos_x = pos_x;
        _initial_pos_y = pos_y;
        _reference_speed = normal_speed;
        _speed_x = orientation == Orientation::LEFT ? -_reference_speed : 0;
        _speed_x = orientation == Orientation::RIGHT ? _reference_speed : _speed_x;
        _speed_y = orientation == Orientation::UP ? -_reference_speed : 0;
        _speed_y = orientation == Orientation::DOWN ? _reference_speed : _speed_y;
    }

    bool Ghost::getIsScared() const
    {
        return _is_scared;
    }

    void Ghost::scare(std::vector<Wall> walls)
    {
        if (_is_alive == false)
            return;
        if (_is_asleep)
            return;
        _is_scared = true;
        _time_scared = 10;
        _reference_speed = scared_speed;
        _texture = 's';
        _path.clear();
        AEntity target(_initial_pos_x, _initial_pos_y, '?', Orientation::RIGHT);
        createPathWrapper(walls, target, *this);
    }

    void Ghost::die(std::vector<Wall> walls)
    {
        if (_is_alive == false)
            return;
        _is_alive = false;
        _is_asleep = false;
        _asleep_time = 0;
        _is_scared = false;
        _time_scared = 0;
        _reference_speed = dead_speed;
        _texture = '!';
        _path.clear();
        AEntity target(_initial_pos_x, _initial_pos_y, '?', Orientation::RIGHT);
        createPathWrapper(walls, target, *this);
    }

    void Ghost::goBackToNormal(std::vector<Wall> walls, AEntity target)
    {
        _is_scared = false;
        _time_scared = 0;
        _is_asleep = false;
        _asleep_time = 0;
        _is_alive = true;
        _reference_speed = normal_speed;
        _texture = 'g';
        _path.clear();
        createPathWrapper(walls, target, *this);
    }

    void Ghost::move(float delta_time, std::vector<Wall> walls)
    {
        if (_is_asleep)
            return;
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
                if (wall.getIsTemporary())
                    if (wall.getIsOpen())
                        continue;
                if (_speed_x > 0)
                {
                    new_pos_x = wall.getPosX() - 1;
                    _speed_x = 0;
                    _path.clear();
                }
                if (_speed_x < 0)
                {
                    new_pos_x = wall.getPosX() + 1;
                    _speed_x = 0;
                    _path.clear();
                }
                if (_speed_y > 0)
                {
                    new_pos_y = wall.getPosY() - 1;
                    _speed_y = 0;
                    _path.clear();
                }
                if (_speed_y < 0)
                {
                    new_pos_y = wall.getPosY() + 1;
                    _speed_y = 0;
                    _path.clear();
                }
                break;
            }
        }

        _pos_x = new_pos_x;
        _pos_y = new_pos_y;
    }

    bool Ghost::changeDirection(Orientation orientation, std::vector<Wall> walls)
    {
        if (orientation == _orientation)
            return true;

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
            if (wall.getIsTemporary())
            {
                if (wall.getIsOpen())
                    continue;
            }
            if (collide_with(wall))
            {
                _speed_x = old_speed_x;
                _speed_y = old_speed_y;
                _pos_x = old_pos_x;
                _pos_y = old_pos_y;
                _orientation = old_orientation;
                return false;
            }
        }

        _speed_x = orientation == Orientation::LEFT ? -_reference_speed : 0;
        _speed_x = orientation == Orientation::RIGHT ? _reference_speed : _speed_x;
        _speed_y = orientation == Orientation::UP ? -_reference_speed : 0;
        _speed_y = orientation == Orientation::DOWN ? _reference_speed : _speed_y;
        _pos_x = old_pos_x;
        _pos_y = old_pos_y;
        _orientation = orientation;
        return true;
    }

    bool Ghost::createPath(std::vector<Wall> walls, AEntity target, AEntity starting, int steps_taken)
    {
        for (auto &visited : _visited)
        {
            if (visited.collide_with(starting))
                return false;
        }
        for (auto &cell : _path)
        {
            if (cell.collide_with(starting))
                return false;
        }
        for (auto &wall : walls)
        {
            if (wall.getIsTemporary())
                if (wall.getIsOpen())
                    continue;
            if (wall.collide_with(starting))
                return false;
        }
        if (steps_taken > 250)
            return false;
        _visited.push_back(starting);
        _path.push_back(AEntity((int)starting.getPosX(), (int)starting.getPosY(), '?', starting.getOrientation()));
        if ((int)starting.getPosX() == (int)target.getPosX() && (int)starting.getPosY() == (int)target.getPosY())
            return true;
        if (createPath(walls, target, AEntity((int)starting.getPosX(), (int)starting.getPosY() - 1, '?', Orientation::UP), steps_taken + 1))
            return true;
        if (createPath(walls, target, AEntity((int)starting.getPosX() + 1, (int)starting.getPosY(), '?', Orientation::RIGHT), steps_taken + 1))
            return true;
        if (createPath(walls, target, AEntity((int)starting.getPosX(), (int)starting.getPosY() + 1, '?', Orientation::DOWN), steps_taken + 1))
            return true;
        if (createPath(walls, target, AEntity((int)starting.getPosX() - 1, (int)starting.getPosY(), '?', Orientation::LEFT), steps_taken + 1))
            return true;
        _path.pop_back();
        return false;
    }

    void Ghost::createPathWrapper(std::vector<Wall> walls, AEntity target, AEntity starting)
    {
        _path.clear();
        _visited.clear();
        _pos_x = (int)(_pos_x + 0.5);
        _pos_y = (int)(_pos_y + 0.5);
        AEntity new_target = AEntity((int)target.getPosX(), (int)target.getPosY(), '?', target.getOrientation());
        AEntity new_starting = AEntity((int)starting.getPosX(), (int)starting.getPosY(), '?', starting.getOrientation());
        for (auto &wall : walls)
        {
            if (wall.getIsTemporary())
                if (wall.getIsOpen())
                    continue;
            if (wall.collide_with(new_target))
                return;
            if (wall.collide_with(new_starting))
                return;
        }
        createPath(walls, new_target, new_starting, 0);
        std::vector<AEntity> new_path;
        AEntity first = _path[0];
        _path.erase(_path.begin());
        for (auto &cell : _path)
        {
            new_path.push_back(AEntity(first.getPosX(), first.getPosY(), '?', cell.getOrientation()));
            first = cell;
        }
        _path = new_path;
    }

    void Ghost::update(float delta_time, std::vector<Wall> walls, Player player)
    {
        if (_is_asleep)
        {
            _asleep_time -= delta_time;
            if (_asleep_time <= 0)
                _is_asleep = false;
            return;
        }
        if (_is_scared)
        {
            _time_scared -= delta_time;
            if (_time_scared <= 0)
                goBackToNormal(walls, player);
        }
        if (_path.size() == 0)
        {
            if (!_is_alive)
                goBackToNormal(walls, player);
            createPathWrapper(walls, player, *this);
        }
        if (_path.size() > 0)
        {
            for (auto &cell : _path)
            {
                if (collide_with(cell))
                {
                    if (changeDirection(cell.getOrientation(), walls))
                    {
                        _path.erase(_path.begin());
                    }
                }
            }
        }
    }

    void Ghost::respawn()
    {
        _pos_x = _initial_pos_x;
        _pos_y = _initial_pos_y;
        goBackToNormal({}, AEntity(_initial_pos_x, _initial_pos_y, '?', Orientation::RIGHT));
    }

    void Ghost::reset()
    {
        _pos_x = _initial_pos_x;
        _pos_y = _initial_pos_y;
        _orientation = Orientation::UP;
        _texture = 'g';
        _is_alive = true;
        _is_scared = false;
        _is_asleep = true;
        _asleep_time = asleep_time_reference;
        _time_scared = 0;
        normal_speed = normal_speed * 1.1;
        scared_speed = scared_speed * 1.1;
        dead_speed = dead_speed * 1.1;
        _reference_speed = normal_speed;
        _speed_x = _orientation == Orientation::LEFT ? -_reference_speed : 0;
        _speed_x = _orientation == Orientation::RIGHT ? _reference_speed : _speed_x;
        _speed_y = _orientation == Orientation::UP ? -_reference_speed : 0;
        _speed_y = _orientation == Orientation::DOWN ? _reference_speed : _speed_y;
        _path.clear();
    }

    std::vector<AEntity> Ghost::getPath() const
    {
        return _path;
    }

    bool Ghost::getIsAlive() const
    {
        return _is_alive;
    }
}
