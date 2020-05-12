#ifndef GAME_RESOURCEMANAGER_H
#define GAME_RESOURCEMANAGER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>

template<typename Derived, typename T>
class ResourceManager{

public:

    ResourceManager(const std::string &pathsFile){

        loadPaths(pathsFile);
    }

    virtual ~ResourceManager(){

        purgeResources();
    }

    T* getResource(const std::string &name){

        auto res = findResource(name);
        return(res ? res->first : nullptr);
    }

    std::string getPath(const std::string &name){

        auto path = paths.find(name);
        return(path != paths.end() ? path->second : "");
    }

    bool requireResource(const std::string &name){

        auto res = findResource(name);
        if(res){

            ++res->second;
            return true;
        }

        auto found = paths.find(name);
        if (found == paths.end())
            return false;

        T* resource = load(found->second);
        if (!resource)
            return false;

        resources.emplace(name, std::make_pair(resource, 1));
        return true;
    }

    bool releaseResource(const std::string &name){

        auto res = findResource(name);
        if (!res)
            return false;

        --res->second;
        if (!res->second)
            unload(name);

        return true;
    }

    void purgeResources(){

        while(resources.begin() != resources.end()){

            delete resources.begin()->second.first;
            resources.erase(resources.begin());
        }
    }

    T* load(const std::string &path){

        return static_cast<Derived*>(this)->load(path);
    }

    std::pair<T*,unsigned int>* findResource(const std::string &name){

        auto itr = resources.find(name);
        return(itr != resources.end() ? &itr->second : nullptr);
    }

    bool unload(const std::string &name){
        auto itr = resources.find(name);
        if(itr == resources.end())
            return false;

        delete itr->second.first;
        resources.erase(itr);
        return true;
    }

    void loadPaths(const std::string &pathFile){

        std::ifstream tPaths;
        tPaths.open(pathFile);
        if(tPaths.is_open()){

            std::string line;
            while(std::getline(tPaths,line)){

                std::stringstream keystream(line);
                std::string pathName;
                std::string path;
                keystream >> pathName;
                keystream >> path;
                paths.emplace(pathName,path);
            }
            tPaths.close();
            return;
        }
        std::cerr << "! Failed loading the path file: " << pathFile << std::endl;
    }

private:

    std::unordered_map<std::string, std::pair<T*, unsigned int>> resources;
    std::unordered_map<std::string, std::string> paths;
};

#endif
