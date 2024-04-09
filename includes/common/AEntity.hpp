/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** AEntity
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include <vector>
#include <map>
#include <string>

namespace arcade
{
    /**
     * @brief Enumeration representing the orientation of an entity.
     */
    enum class Orientation
    {
        UP = 0,     /**< Up orientation. */
        RIGHT = 90, /**< Right orientation. */
        DOWN = 180, /**< Down orientation. */
        LEFT = 270  /**< Left orientation. */
    };

    /**
     * @brief Base class representing a generic entity.
     */
    class AEntity
    {
    public:
        /**
         * @brief Constructor for AEntity.
         * @param pos_x The x-coordinate position of the entity.
         * @param pos_y The y-coordinate position of the entity.
         * @param texture The texture character representing the entity.
         * @param orientation The orientation of the entity.
         */
        AEntity(float pos_x, float pos_y, char texture, Orientation orientation);

        /**
         * @brief Destructor for AEntity.
         */
        ~AEntity() = default;

        /**
         * @brief Getter for the x-coordinate position of the entity.
         * @return The x-coordinate position of the entity.
         */
        float getPosX() const;

        /**
         * @brief Getter for the y-coordinate position of the entity.
         * @return The y-coordinate position of the entity.
         */
        float getPosY() const;

        /**
         * @brief Getter for the texture character representing the entity.
         * @return The texture character representing the entity.
         */
        char getTexture() const;

        /**
         * @brief Setter for the texture character representing the entity.
         * @param texture The texture character to set.
         */
        void setTexture(char texture);

        /**
         * @brief Getter for the orientation of the entity.
         * @return The orientation of the entity.
         */
        Orientation getOrientation() const;

        /**
         * @brief Setter for the orientation of the entity.
         * @param orientation The orientation to set.
         */
        void setOrientation(Orientation orientation);

        /**
         * @brief Setter for the x-coordinate position of the entity.
         * @param pos_x The x-coordinate position to set.
         */
        void setPosX(float pos_x);

        /**
         * @brief Setter for the y-coordinate position of the entity.
         * @param pos_y The y-coordinate position to set.
         */
        void setPosY(float pos_y);

        /**
         * @brief Function to check if the entity collides with another entity.
         * @param entity The entity to check collision with.
         * @return True if the entities collide, false otherwise.
         */
        bool collide_with(AEntity entity);

    protected:
        float _pos_x;           /**< The x-coordinate position of the entity. */
        float _pos_y;           /**< The y-coordinate position of the entity. */
        char _texture;          /**< The texture character representing the entity. */
        Orientation _orientation;   /**< The orientation of the entity. */
    };

    /**
     * @brief Struct representing game data.
     */
    struct GameData
    {
        std::vector<AEntity> entities;     /**< Vector containing game entities. */
        std::map<char, std::string> textures; /**< Map containing textures. */
        std::size_t screen_size_x;          /**< Width of the screen. */
        std::size_t screen_size_y;          /**< Height of the screen. */
    };
}
#endif /* AENTITY_HPP_ */
