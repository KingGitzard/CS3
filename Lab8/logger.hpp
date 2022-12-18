// Singleton Design header
// Hunter Harbison 
// 3/22/2022

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>

class Logger{
    public:
        static Logger * instance(){
            static Logger log;
            return &log;
        }
    ~Logger(){
        std::cout << "destructor" << std::endl;
        file.close();
    }
    void report(const std::string &line){
        file << line;
    }

    private:
        std::string fileName = "log.txt";
        std::ofstream file;

        Logger(){
            file.open(fileName, std::fstream::app);
            if(!file.is_open()){
                std::cout << "Could not open file.\n";
                exit(0);
            }
        }
    Logger(const Logger&) = delete;
    Logger& operator = (const Logger&) = delete;
};

#endif