#ifndef POSITION_H
#define POSITION_H

#include <array>
#include <string>

class Position {
private:
    uint64_t white_pawns, white_knights, white_bishops, white_rooks, white_queens, white_king;
    uint64_t black_pawns, black_knights, black_bishops, black_rooks, black_queens, black_king;

    bool white_to_move;
    uint8_t castling_rights; // 4 bits: 0000 (KQkq)
    int en_passant_square;   // -1 if none
    int halfmove_clock;      // for 50-move rule
    int fullmove_number;
public:
    Position();
    Position(const std::string& fen);
    uint64_t white_pieces() const;
    uint64_t black_pieces() const;
    uint64_t all_pieces() const;
    void set_from_fen(const std::string& fen);
    void clear();
    void print_position();
};

int evaluate(const Position& pos);
#endif