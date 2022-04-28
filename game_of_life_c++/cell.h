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
    Cell(Position& position, std::vector<Cell*>& neighbors);

    // geter
    bool GetState() const;

    // seter
    void ReverseState();
    void NextState(std::function<bool(int neighbor_num)> rule);
    void AddNeighbor(Cell* neighbor);

private:
    bool state_ = false;
    Position position_ = { 0.0, 0.0 };

    std::vector<Cell*> neighbors_;
};

#endif
