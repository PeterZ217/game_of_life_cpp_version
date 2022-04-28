#include "cell.h"

// init
Cell::Cell(Position& position) : position_(position) {}
Cell::Cell(Position& position, std::vector<Cell*>& neighbors) : position_(position), neighbors_(neighbors) { }

// geter
bool Cell::GetState() const {
    return state_;
}

// seter
void Cell::ReverseState() {
    state_ = !state_;
}
void Cell::NextState(std::function<bool(int neighbor_num)> rule) {
    int count_neighbor = 0;
    for (Cell*& neighbor : neighbors_) {
        if (neighbor->GetState()) {
            count_neighbor++;
        }
    }
    state_ = rule(count_neighbor);
}
void Cell::AddNeighbor(Cell* neighbor) {
    neighbors_.push_back(neighbor);
}