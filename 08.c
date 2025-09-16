#include <stdio.h>
enum shape { ROCK, PAPER, SCISSORS };
enum result { LOSS, DRAW, WIN };
void print_shape(enum shape s) {
    switch (s) {
        case ROCK: printf("Rock"); break;
        case PAPER: printf("Paper"); break;
        case SCISSORS: printf("Scissors"); break;
    }
}
void print_result(enum result r) {
    switch (r) {
        case LOSS: printf("Loss"); break;
        case DRAW: printf("Draw"); break;
        case WIN: printf("Win"); break;
    }
}
enum result get_result(enum shape a, enum shape b) {
    if (a == b) return DRAW;
    if ((a == ROCK && b == SCISSORS) ||
        (a == PAPER && b == ROCK) ||
        (a == SCISSORS && b == PAPER)) {
        return WIN;
        }
    return LOSS;
}
enum shape get_strength(enum shape s) {
    switch (s) {
        case ROCK: return SCISSORS;
        case PAPER: return ROCK;
        case SCISSORS: return PAPER;
    }
}
int main() {
    return 0;
}