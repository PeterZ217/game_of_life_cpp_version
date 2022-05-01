#include "board.h"

// init
Board::Board(const std::string& name_set, size_t row_num_set, size_t col_num_set, double cell_size_set) {
	name_ = name_set;
	height_ = (sqrt(3) / 2.0) * row_num_set * cell_size_set + cell_size_set;
	width_ = col_num_ * cell_size_set * 3.0 + 0.5 * cell_size_set;
	row_num_ = row_num_set;
	col_num_ = col_num_set;
	cell_size_ = cell_size_set;

	board_1_ = std::vector<std::vector<Cell>>(row_num_, std::vector<Cell>(col_num_, Cell()));
	board_2_ = std::vector<std::vector<Cell>>(row_num_, std::vector<Cell>(col_num_, Cell()));

	thread_num = 1;
}
Board::Board(const std::string& name_set, size_t row_num_set, size_t col_num_set, double cell_size_set, int thread_num_set) {
	name_ = name_set;
	height_ = (sqrt(3) / 2.0) * row_num_set * cell_size_set + cell_size_set;
	width_ = col_num_ * cell_size_set * 3.0 + 0.5 * cell_size_set;
	row_num_ = row_num_set;
	col_num_ = col_num_set;
	cell_size_ = cell_size_set;

	board_1_ = std::vector<std::vector<Cell>>(row_num_, std::vector<Cell>(col_num_, Cell()));
	board_2_ = std::vector<std::vector<Cell>>(row_num_, std::vector<Cell>(col_num_, Cell()));

	thread_num = thread_num_set;
}
Board::Board(const std::string& name_set, const std::string& file_name) {
	name_ = name_set;
	// todo!()
}

// geter
size_t Board::GetRowNum() const {
	return row_num_;
}
size_t Board::GetColNum() const {
	return col_num_;
}
double Board::GetCellSize() const {
	return cell_size_;
}
double Board::GetHeight() const {
	return height_;
}
double Board::GetWidth() const {
	return width_;
}
Cell& Board::At(size_t row_num, size_t col_num) {
	if (is_first_board_) {
		return board_1_.at(row_num).at(col_num);
	}
	return board_2_.at(row_num).at(col_num);
}

// seter
void Board::ReverseState(size_t row_num, size_t col_num) {
	if (is_first_board_) {
		board_1_.at(row_num).at(col_num).ReverseState();
	}
	else {
		board_2_.at(row_num).at(col_num).ReverseState();
	}
}
void Board::SetState(size_t row_num, size_t col_num, bool next) {
	if (is_first_board_) {
		board_1_.at(row_num).at(col_num).ChangeState(next);
	}
	else {
		board_2_.at(row_num).at(col_num).ChangeState(next);
	}
}

// functions
void Board::NextGeneration() {
	if (is_first_board_) {
		for (size_t row = 0; row < row_num_; ++row) {
			for (size_t col = 0; col < col_num_; ++col) {
				board_2_.at(row).at(col).ChangeState(Check1(row, col));
			}
		}
		is_first_board_ = false;
	}
	else {
		for (size_t row = 0; row < row_num_; ++row) {
			for (size_t col = 0; col < col_num_; ++col) {
				board_1_.at(row).at(col).ChangeState(Check2(row, col));
			}
		}
		is_first_board_ = true;
	}
}
void Board::Save(const std::string& file_name) {
	// todo!()
}

// helper functions
bool Board::Check1(size_t row_num, size_t col_num) {
	int neighbor_num = CountNeighborNumber1(row_num, col_num);
	return Rule(neighbor_num, board_1_.at(row_num).at(col_num).GetState());
}
bool Board::Check2(size_t row_num, size_t col_num) {
	int neighbor_num = CountNeighborNumber2(row_num, col_num);
	return Rule(neighbor_num, board_2_.at(row_num).at(col_num).GetState());
}