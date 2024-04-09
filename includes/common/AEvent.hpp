/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** AEvent
*/

#ifndef AEVENT_HPP_
#define AEVENT_HPP_

#include <vector>

namespace arcade
{
    /**
     * @brief Enumeration representing types of events.
     */
    enum class Type_e
    {
        KEY_A,                              /**< Key A event. */
        KEY_B,                              /**< Key B event. */
        KEY_C,                              /**< Key C event. */                  
        KEY_D,                              /**< Key D event. */
        KEY_E,                              /**< Key E event. */
        KEY_F,                              /**< Key F event. */
        KEY_G,                              /**< Key G event. */
        KEY_H,                              /**< Key H event. */
        KEY_I,                              /**< Key I event. */
        KEY_J,                              /**< Key J event. */
        KEY_K,                              /**< Key K event. */
        KEY_L,                              /**< Key L event. */
        KEY_M,                              /**< Key M event. */
        KEY_N,                              /**< Key N event. */
        KEY_O,                              /**< Key O event. */
        KEY_P,                              /**< Key P event. */
        KEY_Q,                              /**< Key Q event. */
        KEY_R,                              /**< Key R event. */
        KEY_S,                              /**< Key S event. */
        KEY_T,                              /**< Key T event. */
        KEY_U,                              /**< Key U event. */
        KEY_V,                              /**< Key V event. */
        KEY_W,                              /**< Key W event. */
        KEY_X,                              /**< Key X event. */
        KEY_Y,                              /**< Key Y event. */
        KEY_Z,                              /**< Key Z event. */
        NUM0,                               /**< Key Numpad 0 event. */
        NUM1,                               /**< Key Numpad 1 event. */
        NUM2,                               /**< Key Numpad 2 event. */
        NUM3,                               /**< Key Numpad 3 event. */
        NUM4,                               /**< Key Numpad 4 event. */
        NUM5,                               /**< Key Numpad 5 event. */
        NUM6,                               /**< Key Numpad 6 event. */
        NUM7,                               /**< Key Numpad 7 event. */
        NUM8,                               /**< Key Numpad 8 event. */
        NUM9,                               /**< Key Numpad 9 event. */
        SPACE,                              /**< Key SPACE event. */
        ENTER,                              /**< Key ENTER event. */
        BACKSPACE,                          /**< Key BACKSPACE event. */
        ESCAPE,                             /**< Key ESCAPE event. */
        UP,                                 /**< Key ARROW UP event. */
        DOWN,                               /**< Key ARROW DOWN event. */
        LEFT,                               /**< Key ARROW LEFT event. */
        RIGHT,                              /**< Key ARROW RIGHT event. */
        MOUSE_LEFT,                         /**< Mouse left button event. */
        MOUSE_RIGHT,                        /**< Mouse right button event. */
        GET_NEXT_GRAPHIC_LIBRARY,           /**< Get next graphic library event. */
        GET_PREVIOUS_GRAPHIC_LIBRARY,       /**< Get previous graphic library event. */
        GET_NEXT_GAME_LIBRARY,              /**< Get next game library event. */
        GET_PREVIOUS_GAME_LIBRARY,          /**< Get previous game library event. */
        GET_HIGHSCORE,                      /**< Get highscore event. */
        TYPE_COUNT                          /**< Number of event types. */
    };

    /**
     * @brief Class representing an event.
     */
    class AEvent
    {
    public:
        /**
         * @brief Constructor for AEvent.
         * @param type The type of the event(keyboard input).
         * @param value_x The value of x associated with the event.
         * @param value_y The value of y associated with the event.
         */
        AEvent(Type_e type, float value_x, float value_y);

        /**
         * @brief Destructor for AEvent.
         */
        ~AEvent() = default;

        /**
         * @brief Getter for the type of the event(keyboard input).
         * @return The type of the event.
         */
        Type_e getType() const;

        /**
         * @brief Getter for the value of x associated with the event.
         * @return The value of x associated with the event.
         */
        float getValueX() const;

        /**
         * @brief Getter for the value of y associated with the event.
         * @return The value of y associated with the event.
         */
        float getValueY() const;

    private:
        Type_e _type;           /**< The type of the event. */
        float _value_x;         /**< The value of x associated with the event. */
        float _value_y;         /**< The value of y associated with the event. */
    };

    /**
     * @brief Struct representing display data.
     */
    struct DisplayData
    {
        std::vector<AEvent> events;    /**< Vector containing events. */
        float delta;                    /**< Delta value for display. */
    };
}

#endif /* !AEVENT_HPP_ */
