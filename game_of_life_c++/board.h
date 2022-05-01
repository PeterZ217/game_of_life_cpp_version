#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <cmath>
#include <vector>
#include <thread>

#include "cell.h"

class Board {
public:
    // init
    Board() = default;
    Board(const std::string& name_set, size_t row_num_set, size_t col_num_set, double cell_size_set);
    Board(const std::string& name_set, size_t row_num_set, size_t col_num_set, double cell_size_set, int thread_num_set);
    Board(const std::string& name_set, const std::string& file_name);

    // geter
    size_t GetRowNum() const;
    size_t GetColNum() const;
    double GetCellSize() const;
    double GetHeight() const;
    double GetWidth() const;
    Cell& At(size_t row_num, size_t col_num);

    // seter
    void ReverseState(size_t row_num, size_t col_num);
    void SetState(size_t row_num, size_t col_num, bool next);
    virtual void ChangeState(double x_position, double y_position) = 0;

    // functions
    void NextGeneration();
    void Save(const std::string& file_name);


protected:
    size_t row_num_;
    size_t col_num_;

    double cell_size_;

    bool is_first_board_ = true;
    std::vector<std::vector<Cell>> board_1_;
    std::vector<std::vector<Cell>> board_2_;

    // helper functions
    virtual void SetPosition() = 0;
    virtual int CountNeighborNumber1(size_t row_num, size_t col_num) = 0;
    virtual int CountNeighborNumber2(size_t row_num, size_t col_num) = 0;
    virtual bool Rule(int neighbor_num, bool state) = 0;

private:
    std::string name_;

    double height_;
    double width_;

    int thread_num;

    // helper function
    bool Check1(size_t row_num, size_t col_num);
    bool Check2(size_t row_num, size_t col_num);
};

#endif