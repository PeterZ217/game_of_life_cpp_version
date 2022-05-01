#pragma once
#ifndef CELL_HPP
#define CELL_HPP

#include <vector>
#include <functional>

struct Position {
    double x;
    double y;
};

class Cell {
public:
    Cell() = default;
    Cell(Position& position);

    // geter
    bool GetState() const;
    double GetX() const;
    double GetY() const;

    // seter
    void SetPosition(double x, double y);
    void ChangeState(bool next);
    void ReverseState();


private:
    bool state_ = false;
    Position position_ = { 0.0, 0.0 };
};

#endif
