/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Wall
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include "AEntity.hpp"

namespace arcade
{
    class Wall : public AEntity
    {
    public:
        Wall(float pos_x, float pos_y, char texture, Orientation orientation, bool is_temporary);
        ~Wall() = default;

        bool getIsTemporary() const;
        bool getIsOpen() const;

        void open();
        void update(float deltaTime);

        void reset();

    private:
        bool _is_temporary;
        bool _is_open = false;
        float _time_to_open = 10;
    };
}

#endif /* !WALL_HPP_ */
