#include "piece.h"

Piece::Piece(std::string file_name, int pos, Type type)
    : file_name{file_name}, pos{pos}, type{type} {}
