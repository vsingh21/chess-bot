// main.cpp - Entry point for the chess engine
#include <cstdio>
#include <cstdint>
#include "position.h"

int main() {
    printf("Welcome to the chess bot");
    Position p("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    p.print_position();
    return 0;
}
