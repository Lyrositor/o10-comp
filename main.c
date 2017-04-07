#include <stdint.h>

int64_t main() {
    int64_t a;
    a = 2;
    ++a;
    return a; // 2
}

/*

// minus op
int64_t main() {
    int64_t a;
    int64_t b;
    a = 1;
    b = 2;
    a = -a; // a = -1
    b = a + b; // b = 2-1 = 1
    return b; // 1
}

// bitwise complement
int64_t main() {
    int64_t a;
    int64_t b;
    a = 1; // a = 0b0..01
    a = ~a; // a = 0b11..10
    b = a + 1; // b = 0b11..11
    return ~b; // 0
}

// logical negation
int64_t main() {
    int64_t a;
    int64_t b;
    a = 5; // a = 5
    a = !a; // a = 0
    b = 0; // b = 0
    b = !b; // b = 1
    return b; // 1
}

// unary_plus
int64_t main() {
    int64_t a;
    a = 1;
    a = +a;
    return a; // 1
}

*/
