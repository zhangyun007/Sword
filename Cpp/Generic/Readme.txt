C新泛型系统   该系统实现C各种宏替换以及泛型替换


#define A 12

Type T, U;
T add(T a, T b, U c) {
    return a + b + A;
}

int main() {
    add(12, 34)         //特化成为add_int
    add(12.3, 34.5)     //特化成为add_float
}