#include "position.h"
#include <sstream>
#include <iostream>

Position::Position() {
    clear();
}

Position::Position(const std::string& fen) {
    set_from_fen(fen);
}

uint64_t Position::white_pieces() const {
    return white_pawns | white_knights | white_bishops | white_rooks | white_queens | white_king;
}

uint64_t Position::black_pieces() const {
    return black_pawns | black_knights | black_bishops | black_rooks | black_queens | black_king;
}

uint64_t Position::all_pieces() const {
    return white_pieces() | black_pieces();
}



void Position::set_from_fen(const std::string& fen) {
    clear();
    std::istringstream iss(fen);
    std::string board, active_color, castling, en_passant, halfmove, fullmove;
    iss >> board >> active_color >> castling >> en_passant >> halfmove >> fullmove;

    // Parse board position
    int rank = 7, file = 0;
    for (char c : board) {
        if (c == '/') {
            rank--;
            file = 0;
        } else if (isdigit(c)) {
            file += c - '0';
        } else {
            uint64_t square_bit = 1ULL << (rank * 8 + file);
            switch (c) {
                case 'P': white_pawns |= square_bit; break;
                case 'N': white_knights |= square_bit; break;
                case 'B': white_bishops |= square_bit; break;
                case 'R': white_rooks |= square_bit; break;
                case 'Q': white_queens |= square_bit; break;
                case 'K': white_king |= square_bit; break;
                case 'p': black_pawns |= square_bit; break;
                case 'n': black_knights |= square_bit; break;
                case 'b': black_bishops |= square_bit; break;
                case 'r': black_rooks |= square_bit; break;
                case 'q': black_queens |= square_bit; break;
                case 'k': black_king |= square_bit; break;
            }
            file++;
        }
    }

    // Parse active color
    white_to_move = (active_color == "w");

    // Parse castling rights
    castling_rights = 0;
    for (char c : castling) {
        switch (c) {
            case 'K': castling_rights |= 1; break;
            case 'Q': castling_rights |= 2; break;
            case 'k': castling_rights |= 4; break;
            case 'q': castling_rights |= 8; break;
        }
    }

    // Parse en passant
    if (en_passant != "-") {
        int file_ep = en_passant[0] - 'a';
        int rank_ep = en_passant[1] - '1';
        en_passant_square = rank_ep * 8 + file_ep;
    } else {
        en_passant_square = -1;
    }

    // Parse move counters
    halfmove_clock = std::stoi(halfmove);
    fullmove_number = std::stoi(fullmove);
}

void Position::clear() {
    white_pawns = white_knights = white_bishops = white_rooks = white_queens = white_king = 0;
    black_pawns = black_knights = black_bishops = black_rooks = black_queens = black_king = 0;

    bool white_to_move = 0;
    uint8_t castling_rights = 0; // 4 bits: 0000 (KQkq)
    int en_passant_square = -1;   // -1 if none
    int halfmove_clock = 0;      // for 50-move rule
    int fullmove_number = 0;
}

void Position::print_position() {
    std::cout << "\n  a b c d e f g h\n";
    for (int rank = 7; rank >= 0; rank--) {
        std::cout << (rank + 1) << " ";
        for (int file = 0; file < 8; file++) {
            uint64_t square_bit = 1ULL << (rank * 8 + file);
            
            if (white_pawns & square_bit) std::cout << "♙ ";
            else if (white_knights & square_bit) std::cout << "♘ ";
            else if (white_bishops & square_bit) std::cout << "♗ ";
            else if (white_rooks & square_bit) std::cout << "♖ ";
            else if (white_queens & square_bit) std::cout << "♕ ";
            else if (white_king & square_bit) std::cout << "♔ ";
            else if (black_pawns & square_bit) std::cout << "♟ ";
            else if (black_knights & square_bit) std::cout << "♞ ";
            else if (black_bishops & square_bit) std::cout << "♝ ";
            else if (black_rooks & square_bit) std::cout << "♜ ";
            else if (black_queens & square_bit) std::cout << "♛ ";
            else if (black_king & square_bit) std::cout << "♚ ";
            else std::cout << ". ";
        }
        std::cout << (rank + 1) << "\n";
    }
    std::cout << "  a b c d e f g h\n";
    std::cout << "Turn: " << (white_to_move ? "White" : "Black") << "\n";
}

int evaluate(const Position& pos) {
    
}