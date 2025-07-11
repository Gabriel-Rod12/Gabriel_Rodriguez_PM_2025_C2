#include <stdio.h>
#include <math.h>

int main() {
    int T, P, R;

    for (T = 1; T <= 50; T++) {
        for (P = 1; P <= 50; P++) {
            for (R = 1; R <= 50; R++) {
                if (7 * pow(T, 4) - 6 * pow(P, 3) + 12 * pow(R, 5) < 5850) {
                    printf("T = %d, P = %d, R = %d\n", T, P, R);
                }
            }
        }
    }

    return 0;
}

