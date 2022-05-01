#include "cell.h"

// init
Cell::Cell(Position& position) : position_(position) {}

// geter
bool Cell::GetState() const {
    return state_;
}
double Cell::GetX() const {
    return position_.x;
}
double Cell::GetY() const {
    return position_.y;
}

// seter
void Cell::SetPosition(double x, double y) {
    position_.x = x;
    position_.y = y;
}
void Cell::ChangeState(bool next) {
    state_ = next;
}
void Cell::ReverseState() {
    state_ = !state_;
}