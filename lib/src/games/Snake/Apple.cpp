/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Apple
*/

#include "Apple.hpp"

namespace arcade {
    void Apple::eaten(std::vector<AEntity> _grass, std::vector<AEntity> _snake)
    {
        bool occupied = false;
        std::vector<AEntity> available_pos;
        for (auto &entity : _grass) {
            occupied = false;
            for (auto &snake_entity : _snake) {
                if (entity.collide_with(snake_entity))
                    occupied = true;
            }
            if (!occupied)
                available_pos.push_back(entity);
        }

        if (available_pos.empty())
            return;
        int random = rand() % available_pos.size();
        _pos_x = available_pos[random].getPosX();
        _pos_y = available_pos[random].getPosY();
    }
}