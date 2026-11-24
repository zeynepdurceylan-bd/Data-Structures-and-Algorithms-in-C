#include <stdio.h>
#include <stdlib.h>

#define N 6

void grafiAnalizEt(int matris[N][N], int kenarSayisi, int kenarlar[][2]) {
    int i, j;

    /* 1. Veri Yapisi Olusturma: n x n Komsuluk Matrisi */
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matris[i][j] = 0;
        }
    }

    for (i = 0; i < kenarSayisi; i++) {
        int u = kenarlar[i][0] - 1;
        int v = kenarlar[i][1] - 1;
        matris[u][v] = 1;
        matris[v][u] = 1;
    }

    printf("--- 1. Komsuluk Matrisi ---\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", matris[i][j]);
        }
        printf("\n");
    }

    /* 2. Derece Hesaplama */
    int dereceler[N];
    int grafDerecesi = 0;

    printf("\n--- 2. Dugum Dereceleri ve Graf Derecesi ---\n");
    for (i = 0; i < N; i++) {
        int deg = 0;
        for (j = 0; j < N; j++) {
            deg += matris[i][j];
        }
        dereceler[i] = deg;
        printf("Dugum %d derecesi: %d\n", i + 1, deg);
        if (deg > grafDerecesi) {
            grafDerecesi = deg;
        }
    }
    printf("Grafin genel derecesi: %d\n", grafDerecesi);

    /* 3. Bipartite Kontrolu (BFS ile 0/1 Renklendirme / Tek-Cift Yontemi) */
    int renk[N];
    int kuyruk[N];
    int bas = 0, son = 0;
    int bipartiteMi = 1;

    for (i = 0; i < N; i++) {
        renk[i] = -1;
    }

    int start;
    for (start = 0; start < N && bipartiteMi; start++) {
        if (renk[start] == -1) {
            renk[start] = 0;
            kuyruk[son++] = start;

            while (bas < son && bipartiteMi) {
                int mevcut = kuyruk[bas++];
                for (j = 0; j < N; j++) {
                    if (matris[mevcut][j] == 1) {
                        if (renk[j] == -1) {
                            renk[j] = 1 - renk[mevcut];
                            kuyruk[son++] = j;
                        } else if (renk[j] == renk[mevcut]) {
                            bipartiteMi = 0;
                            break;
                        }
                    }
                }
            }
        }
    }

    printf("\n--- 3. Bipartite Kontrolu ---\n");
    for (i = 0; i < N; i++) {
        printf("Dugum %d -> Renk/Parite: %d\n", i + 1, renk[i]);
    }
    if (bipartiteMi) {
        printf("Graf Iki Parcali (Bipartite) midir?: EVET\n");
    } else {
        printf("Graf Iki Parcali (Bipartite) midir?: HAYIR\n");
    }
    printf("----------------------------------------\n");
}

int main() {
    int matris[N][N];

    /* Baslangic grafindaki kenarlar: E = {(1,2), (1,4), (2,3), (3,4), (3,6), (4,5), (5,6)} */
    int baslangicKenarlar[7][2] = {
        {1, 2}, {1, 4}, {2, 3}, {3, 4}, {3, 6}, {4, 5}, {5, 6}
    };

    printf("=== BASLANGIC GRAFI ===\n");
    grafiAnalizEt(matris, 7, baslangicKenarlar);

    /* 4. Dinamik Test: (2, 4) baglantisinin eklenmesi */
    int guncelKenarlar[8][2] = {
        {1, 2}, {1, 4}, {2, 3}, {3, 4}, {3, 6}, {4, 5}, {5, 6}, {2, 4}
    };

    printf("\n=== DINAMIK TEST: (2, 4) EKLENDIKTEN SONRA ===\n");
    grafiAnalizEt(matris, 8, guncelKenarlar);

    system("pause");
    return 0;
}
