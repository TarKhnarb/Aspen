#pragma once
#define GAME_RUNNING_LINUX

#include <iostream>
#include <string>
#include <algorithm>

namespace Utils{ // Allow to store the full "address" of the directory the executable resides in

    #ifdef GAME_RUNNING_WINDOWS // With Windows
        #define WIN32_LEAN_AND_MEAN
        #include <windows.h>
        #include <Shlwapi.h>

        inline std::string getWorkingDirectory(){

            HMODULE hModule = getModuleHandle(nullptr);

            if(hModule){

                char path[256];
                getModuleFileName(hModule,path,sizeof(path));
                pathRemoveFileSpec(path);
                strcat_s(path,"\\"); // new
                return std::string(path); // new
            }
            return "";
        }
    #elif defined RUNNING_LINUX // With Linux
        #include <unistd.h>

        inline std::string getWorkingDirectory(){

            char cwd[1024];
            if(getcwd(cwd, sizeof(cwd)) != nullptr)
                return std::string(cwd) + std::string("/");

            return "";
        }
    #endif
}