/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** AException
*/

#ifndef AEXCEPTION_HPP_
#define AEXCEPTION_HPP_

#include <exception>
#include <string>
#include <iostream>

#define FILE_DATA "In " + std::string(__FILE__) + " at line n°" + std::to_string(__LINE__) + " in function " + std::string(__func__) + "()"

namespace arcade
{
    /**
     * @brief Base class for exceptions in the arcade namespace.
     */
    class AException : public std::exception
    {
    public:
        /**
         * @brief Constructor for AException.
         * @param message The main message associated with the exception.
         * @param additionnal_message Additional message associated with the exception.
         * @param file_data Information about the file, line number, and function where the exception occurred.
         */
        AException(const std::string &message, const std::string &additionnal_message, const std::string &file_data);

        /**
         * @brief Virtual destructor for AException.
         */
        virtual ~AException() = default;

        /**
         * @brief Returns a C-style character string describing the exception.
         * @return A C-style character string describing the exception.
         */
        virtual const char *what() const noexcept override;

        /**
         * @brief Getter for the return value associated with the exception.
         * @return The return value associated with the exception.
         */
        int getReturnValue() const noexcept;

    protected:
        std::string _message;   /**< The main message associated with the exception. */

    private:
        const int return_value = 84;    /**< The return value associated with the exception. */
    };

    /**
     * @brief Exception class specifically for main function related errors.
     */
    class MainException : public AException
    {
    public:
        /**
         * @brief Constructor for MainException.
         * @param additionnal_message Additional message associated with the exception.
         * @param file_data Information about the file, line number, and function where the exception occurred.
         */
        MainException(const std::string &additionnal_message, const std::string &file_data);

        /**
         * @brief Virtual destructor for MainException.
         */
        virtual ~MainException() = default;
    };
}

#endif /* !AEXCEPTION_HPP_ */
