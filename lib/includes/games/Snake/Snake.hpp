/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "AEntity.hpp"

namespace arcade
{
    class Snake
    {
    public:
        Snake(){};
        ~Snake() = default;

        void init(std::vector<AEntity> _grass);
        std::vector<AEntity> getEntities() const;
        void grow_body();
        void move(float delta_time, std::vector<AEntity> _walls);
        void change_orientation(Orientation orientation);
        AEntity getHead() const;
        bool is_alive() const;
    private:
        AEntity _head = AEntity(0, 0, 'O', Orientation::UP);
        std::vector<AEntity> _body;
        float remaining_delta_time = 0;
        float speed_per_second = 10;
        bool _is_alive = true;
    };
};

#endif /* !SNAKE_HPP_ */
