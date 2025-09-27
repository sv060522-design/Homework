#include <stdio.h>
#define MAX_GAMES 100
typedef struct {
    char title[50];
    double average;
} Game;
int main() {
    int n;
    scanf("%d\n", &n);
    Game games[MAX_GAMES];
    char temp;
    for (int i = 0; i < n; i++) {
        scanf(" %49[^:]", games[i].title);
        scanf("%c", &temp);
        int k;
        scanf("%d", &k);
        int sum = 0;
        for (int j = 0; j < k; j++) {
            int rating;
            scanf("%d", &rating);
            sum += rating;
        }
        games[i].average = (double)sum / k;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (games[j].average < games[j + 1].average) {
                Game temp_game = games[j];
                games[j] = games[j + 1];
                games[j + 1] = temp_game;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%s, %.3f\n", games[i].title, games[i].average);
    }
    return 0;
}