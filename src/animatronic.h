#pragma once

class animatronic {
public:
    animatronic(std::string _name, int _difficulty) : name(_name), difficulty(_difficulty) { }

    std::string name;
    int difficulty;
};