/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Apple
*/

#ifndef APPLE_HPP_
#define APPLE_HPP_

#include "AEntity.hpp"

namespace arcade {
    class Apple : public AEntity {
        public:
            Apple(float pos_x, float pos_y, char texture, Orientation orientation) : AEntity(pos_x, pos_y, texture, orientation) {};
            ~Apple() = default;

            void eaten(std::vector<AEntity> _grass, std::vector<AEntity> _snake);
    };
}

#endif /* !APPLE_HPP_ */
