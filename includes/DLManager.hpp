/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** DLManager
*/

#ifndef DLMANAGER_HPP_
#define DLMANAGER_HPP_

#include "AException.hpp"
#include <string>
#include <memory>
#include <dlfcn.h>

namespace arcade
{
    class DLManagerException : public AException
    {
    public:
        DLManagerException(const std::string &additionnal_message, const std::string &file_data);
        virtual ~DLManagerException() = default;
    };

    template <typename LibraryType>
    class DLManager
    {
    public:
        DLManager(int type) : _type(type)
        {
            _handle = nullptr;
        }

        ~DLManager()
        {
            if (_handle)
                dlclose(_handle);
            _handle = nullptr;
        }

        LibraryType *loadLibrary(const std::string &libPath)
        {
            try
            {
                if (isLibraryUsingInterface(libPath) == false)
                    throw DLManagerException(libPath + " Library does not use the right interface", FILE_DATA);
                char *error = dlerror();
                error = nullptr;
                if (_handle)
                    dlclose(_handle);
                _handle = dlopen(libPath.c_str(), RTLD_LAZY);
                if ((error = dlerror()) != nullptr)
                    throw DLManagerException(libPath + " : " + error, FILE_DATA);
                LibraryType *(*entryPoint)() = (LibraryType * (*)()) dlsym(_handle, _entryPointName.c_str());
                if ((error = dlerror()) != nullptr)
                    throw DLManagerException(libPath + " : " + error, FILE_DATA);
                LibraryType *lib = entryPoint();
                if (lib == nullptr)
                    throw DLManagerException(libPath + " : Library entry point returned nullptr", FILE_DATA);
                return lib;
            }
            catch (const AException &except)
            {
                std::cerr << except.what() << std::endl;
                exit(except.getReturnValue());
            }
        }

        void unloadLibrary(LibraryType *lib)
        {
            try
            {
                char *error = dlerror();
                error = nullptr;
                lib->~LibraryType();
                if (_handle)
                    dlclose(_handle);
                if ((error = dlerror()) != nullptr)
                    throw DLManagerException(std::string("unloadLibrary Error : ") + error, FILE_DATA);
                _handle = nullptr;
            }
            catch (const AException &except)
            {
                std::cerr << except.what() << std::endl;
                exit(except.getReturnValue());
            }
        }

        bool isLibraryUsingInterface(const std::string &libPath)
        {
            try
            {
                char *error = dlerror();
                error = nullptr;
                void *tmp_handle = dlopen(libPath.c_str(), RTLD_LAZY);
                if ((error = dlerror()) != nullptr)
                    throw DLManagerException(libPath + " : " + error, FILE_DATA);
                int (*getType)() = (int (*)())dlsym(tmp_handle, _getType.c_str());
                if ((error = dlerror()) != nullptr)
                {
                    dlclose(tmp_handle);
                    throw DLManagerException(libPath + " : " + error, FILE_DATA);
                }
                if (getType() != _type)
                {
                    dlclose(tmp_handle);
                    throw DLManagerException("Library '" + libPath + "' does not use the right interface", FILE_DATA);
                }
                dlclose(tmp_handle);
                return true;
            }
            catch (const AException &except)
            {
                return false;
            }
        }

    private:
        const std::string _entryPointName = "entryPoint";
        const std::string _getType = "getType";
        void *_handle;
        int _type;
    };
}

#endif /* !DLMANAGER_HPP_ */
