#include <stdio.h>

int startGame() {
    int H = 25;
    int W = 80;

    char input;
    do {
        
        // printf("\n");
        // for (int i = 0; i < W; i++) {
        //     printf(".");
        // }

        // printf("\n");
        // for (int i = 0; i < H - 2; i++) {
        //     printf("|");
        //     for (int j = 0; j < W - 2; j++) {
        //         if (j == W / 2 - 3 || j == W / 2 - 2) {
        //             printf(".");
        //         } else {
        //             printf(" ");
        //         }
        //     }
        //     printf(".\n");
        // }
        // for (int i = 0; i < W; i++) {
        //     printf(".");
        // }
        // printf("\n");

        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                if (i == 0 || i == H - 1) {
                    printf(".");
                } else if (j == 0 || j == W - 1 || j == W / 2 - 2 || j == W / 2 - 3) {
                    printf(".");

                } else {

                    printf(" ");
                }

            }
            
            printf("\n");

        }
        
        scanf("%s", &input);
    } while (input !='e');
    return 0;
}

int main() {
    startGame();

    return 0;
}