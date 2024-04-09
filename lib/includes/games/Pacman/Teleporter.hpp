/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Teleporter
*/

#ifndef TELEPORTER_HPP_
#define TELEPORTER_HPP_

#include "AEntity.hpp"

namespace arcade
{
    class Teleporter : public AEntity
    {
    public:
        Teleporter(float pos_x, float pos_y, char texture, Orientation orientation);
        ~Teleporter() = default;

        void setDest(float dest_x, float dest_y);

        float getDestX() const;
        float getDestY() const;

        void reset();

    private:
        float _dest_x;
        float _dest_y;
    };
}

#endif /* !TELEPORTER_HPP_ */
