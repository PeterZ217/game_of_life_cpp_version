#pragma once
#ifndef HEXBOARD_HPP
#define HEXBOARD_HPP

#include <string>
#include <vector>
#include <functional>
#include <iostream>

#include "board.h"

class HexBoard : public Board {
public:
    // init
    HexBoard() = default;
    HexBoard(size_t row_num_set, size_t col_num_set, double cell_size_set);
    HexBoard(size_t row_num_set, size_t col_num_set, double cell_size_set, int thread_num_set);
    HexBoard(const std::string & file_name);

    // geter

    // seter
    void ChangeState(double x_position, double y_position);

    // functions
    void TerminalDisplay() const;

protected:
    // helper functions
    void SetPosition();
    int CountNeighborNumber1(size_t row_num, size_t col_num);
    int CountNeighborNumber2(size_t row_num, size_t col_num);
    bool Rule(int neighbor_num, bool state);

private:
    //
};

#endif