#include "hexboard.h"

// init
HexBoard::HexBoard(size_t row_num_set, size_t col_num_set, double cell_size_set) : Board("Game of life - Hexagon version", row_num_set, col_num_set, cell_size_set) {
    SetPosition();
}
HexBoard::HexBoard(size_t row_num_set, size_t col_num_set, double cell_size_set, int thread_num_set) : Board("Game of life - Hexagon version", row_num_set, col_num_set, cell_size_set, thread_num_set) {
	SetPosition();
}
HexBoard::HexBoard(const std::string& file_name) : Board("Game of life - Hexagon version", file_name) {}

// geter

// seter
void HexBoard::ChangeState(double x_position, double y_position) {
    double temp = (x_position - (cell_size_ / 2.0)) / (cell_size_ / 2.0);
    // devided to six parts
    //  part:   x 0 1 2 3 4 5
    //                 _____
    //           _____/     \
    //          /     \_____/
    //          \_____/
    // 0 && 1 means odd rows
    // 3 && 4 means even rows
    size_t region = static_cast<size_t>(temp) % 6;
    size_t col = static_cast<size_t>(temp) / 6;
    if (region == 0 || region == 1) {
        // start from 0 + (√3 / 2) * cell_side_length 
        size_t row = static_cast<size_t>((y_position - ((sqrt(3) * cell_size_) / 2.0)) * 2.0 / (sqrt(3) * cell_size_));
        // make sure row number is odd
        if (row % 2 == 0) {
            row += 1;
        }
        // change state
        if (is_first_board_) {
            board_1_[row][col].ReverseState();
        }
        else {
            board_2_[row][col].ReverseState();
        }
    }
    if (region == 3 || region == 4) {
        // start from 0
        size_t row = static_cast<size_t>(y_position / (sqrt(3) * cell_size_) * 2.0);
        // make sure row number is even
        if (row % 2 != 0) {
            row -= 1;
        }
        // change state
        if (is_first_board_) {
            board_1_[row][col].ReverseState();
        }
        else {
            board_2_[row][col].ReverseState();
        }
    }
}

// functions
void HexBoard::TerminalDisplay() const {
    std::string space_4 = "    ";
    std::string space_6 = "      ";
    for (size_t row = 0; row < row_num_; ++row) {
         if (row % 2 == 0) {
            std::cout << space_4;
         }
         for (size_t col = 0; col < col_num_; ++col) {
             if (is_first_board_) {
                 if (board_1_.at(row).at(col).GetState()) {
                     std::cout << "X";
                 }
                 else {
                     std::cout << " ";
                 }
                 std::cout << space_6;
             }
             else {
                 if (board_2_.at(row).at(col).GetState()) {
                     std::cout << "X";
                 }
                 else {
                     std::cout << " ";
                 }
                 std::cout << space_6;
             }
         }
         std::cout << std::endl;
    }
}

// helper functions
void HexBoard::SetPosition() {
    // Calculate the position for each cell
        //                 _____       _____       _____       _____
        //           _____/ 0,0 \_____/ 0,1 \_____/ 0,2 \_____/ 0,3 \
        //          / 1,0 \_____/ 1,1 \_____/ 1,2 \_____/ 1,3 \_____/
        //          \_____/ 2,0 \_____/ 2,1 \_____/ 2,2 \_____/ 2,3 \
        //          / 3,0 \_____/ 3,1 \_____/ 3,2 \_____/ 3,3 \_____/
        //          \_____/ 4,0 \_____/ 4,1 \_____/ 4,2 \_____/ 4,3 \
        //          / 5,0 \_____/ 5,1 \_____/ 5,2 \_____/ 5,3 \_____/
        //          \_____/ 6,0 \_____/ 6,1 \_____/ 6,2 \_____/ 6,3 \
        //          / 7,0 \_____/ 7,1 \_____/ 7,2 \_____/ 7,3 \_____/
        //          \_____/     \_____/     \_____/     \_____/
    for (size_t row = 0; row < row_num_; ++row) {
        for (size_t col = 0; col < col_num_; ++col) {
            // sqrt(3)/2 approx = 0.8660254

            // Position of even and odd row is diifferent
            // even rows (start from 0)
            if (row % 2 == 0) {
                double x = (2.5 + 3.0 * col) * cell_size_;
                double y = (sqrt(3) / 2.0) * (1.0 + row) * cell_size_;
                board_1_[row][col].SetPosition(x, y);
                board_2_[row][col].SetPosition(x, y);
            }
            // even rows
            else {
                double x = (1.0 + (3.0 * col)) * cell_size_;
                double y = (row + 1.0) * (sqrt(3) / 2.0) * cell_size_;
                board_1_[row][col].SetPosition(x, y);
                board_2_[row][col].SetPosition(x, y);
            }
        }
    }
}
int HexBoard::CountNeighborNumber1(size_t row_num, size_t col_num) {
    int count = 0;
    // odd rows
    if (row_num % 2 == 0) {
        // Even row
        //         (-2, 0)
        // (-1, 0) /~~~~~\ (-1, 1)
        // (1, 0)  \_____/ (1, 1)
        //          (2, 0)
        if (row_num > 0) {
            if (board_1_[row_num - 2][col_num].GetState()) {
                count++;
            }
            if (board_1_[row_num - 1][col_num].GetState()) {
                count++;
            }
            if (col_num < (col_num_ - 1) && board_1_[row_num - 1][col_num + 1].GetState()) {
                count++;
            }
        }
        if (row_num < (row_num_ - 2) && board_1_[row_num + 2][col_num].GetState()) {
            count++;
        }
        if (board_1_[row_num + 1][col_num].GetState()) {
            count++;
        }
        if (col_num < (col_num_ - 1) && board_1_[row_num + 1][col_num + 1].GetState()) {
            count++;
        }
    }
    // even rows
    else {
        if (row_num > 1 && board_1_[row_num - 2][col_num].GetState()) {
            count++;
        }
        if (row_num < (row_num_ - 1)) {
            if (board_1_[row_num + 2][col_num].GetState()) {
                count++;
            }
            if (col_num > 0 && board_1_[row_num + 1][col_num - 1].GetState()) {
                count++;
            }
            if (board_1_[row_num + 1][col_num].GetState()) {
                count++;
            }
        }
        if (col_num > 0 && board_1_[row_num - 1][col_num - 1].GetState()) {
            count++;
        }
        if (board_1_[row_num - 1][col_num].GetState()) {
            count++;
        }
    }
    return count;
}
int HexBoard::CountNeighborNumber2(size_t row_num, size_t col_num) {
    int count = 0;
    // odd rows
    if (row_num % 2 == 0) {
        // Even row
        //         (-2, 0)
        // (-1, 0) /~~~~~\ (-1, 1)
        // (1, 0)  \_____/ (1, 1)
        //          (2, 0)
        if (row_num > 0) {
            if (board_2_[row_num - 2][col_num].GetState()) {
                count++;
            }
            if (board_2_[row_num - 1][col_num].GetState()) {
                count++;
            }
            if (col_num < (col_num_ - 1) && board_2_[row_num - 1][col_num + 1].GetState()) {
                count++;
            }
        }
        if (row_num < (row_num_ - 2) && board_2_[row_num + 2][col_num].GetState()) {
            count++;
        }
        if (board_2_[row_num + 1][col_num].GetState()) {
            count++;
        }
        if (col_num < (col_num_ - 1) && board_2_[row_num + 1][col_num + 1].GetState()) {
            count++;
        }
    }
    // even rows
    else {
        if (row_num > 1 && board_2_[row_num - 2][col_num].GetState()) {
            count++;
        }
        if (row_num < (row_num_ - 1)) {
            if (board_2_[row_num + 2][col_num].GetState()) {
                count++;
            }
            if (col_num > 0 && board_2_[row_num + 1][col_num - 1].GetState()) {
                count++;
            }
            if (board_2_[row_num + 1][col_num].GetState()) {
                count++;
            }
        }
        if (col_num > 0 && board_2_[row_num - 1][col_num - 1].GetState()) {
            count++;
        }
        if (board_2_[row_num - 1][col_num].GetState()) {
            count++;
        }
    }
    return count;
}
bool HexBoard::Rule(int neighbor_num, bool state) {
    if (state) {
        if (neighbor_num == 3 || neighbor_num == 5) {
            return true;
        }
    }
    else {
        //  reproduction
        if (neighbor_num == 2) {
            return true;
        }
    }
    return false;
}