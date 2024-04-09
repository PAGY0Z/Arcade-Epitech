/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "AEntity.hpp"
#include "Wall.hpp"
#include "Teleporter.hpp"
#include <vector>

namespace arcade
{
    class Player : public AEntity
    {
    public:
        Player(float pos_x, float pos_y, char texture, Orientation orientation);
        ~Player() = default;

        void teleport(Teleporter &teleporter);

        void move(float delta_time, std::vector<Wall> entities);
        void setOrientation(Orientation orientation, std::vector<Wall> walls);

        void die();
        void respawn();

        int getLivesRemaining() const;

        void reset();

    private:
        float _initial_pos_x;
        float _initial_pos_y;
        float _speed_x;
        float _speed_y;
        float _reference_speed = 5.0f;
        int lives_remaining = 3;
    };
}

#endif /* !PLAYER_HPP_ */
