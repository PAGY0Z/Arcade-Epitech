/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
#define GHOST_HPP_

#include "AEntity.hpp"
#include "Wall.hpp"
#include "Player.hpp"
#include <vector>

namespace arcade
{
    class Ghost : public AEntity
    {
    public:
        Ghost(float pos_x, float pos_y, char texture, Orientation orientation, float asleep_time);
        ~Ghost() = default;

        bool getIsScared() const;
        void scare(std::vector<Wall> walls);
        void die(std::vector<Wall> walls);
        void respawn();
        void goBackToNormal(std::vector<Wall> walls, AEntity target);

        void move(float delta_time, std::vector<Wall> walls);

        void update(float delta_time, std::vector<Wall> walls, Player player);
        bool getIsAlive() const;

        bool changeDirection(Orientation orientation, std::vector<Wall> walls);

        std::vector<AEntity> getPath() const;

        void reset();

    private:
        bool createPath(std::vector<Wall> walls, AEntity target, AEntity starting, int steps_taken);
        void createPathWrapper(std::vector<Wall> walls, AEntity target, AEntity starting);
        float normal_speed = 5.0f;
        float scared_speed = 2.5f;
        float dead_speed = 10.0f;
        float asleep_time_reference;
        float _time_scared = 10;
        float _asleep_time;
        float _reference_speed;
        float _speed_x;
        float _speed_y;
        float _initial_pos_x;
        float _initial_pos_y;
        bool _is_alive;
        bool _is_scared;
        bool _is_asleep;
        std::vector<AEntity> _path;
        std::vector<AEntity> _visited;
    };
}

#endif /* !GHOST_HPP_ */
