#include <stdio.h>
#include <stdlib.h>

#define N 6
#define INF 999999

char dugumAdi(int indeks) {
    return 'A' + indeks;
}

int harfToIndeks(char harf) {
    if (harf >= 'a' && harf <= 'z') {
        harf = harf - 'a' + 'A';
    }
    if (harf >= 'A' && harf < 'A' + N) {
        return harf - 'A';
    }
    return -1;
}

void yoluTerstenYazdir(int onceki[], int hedef) {
    int yol[N];
    int uzunluk = 0;
    int mevcut = hedef;

    while (mevcut != -1) {
        yol[uzunluk++] = mevcut;
        mevcut = onceki[mevcut];
    }

    int i;
    for (i = uzunluk - 1; i >= 0; i--) {
        printf("%c", dugumAdi(yol[i]));
        if (i > 0) {
            printf(" -> ");
        }
    }
}

int dijkstraHesapla(int graf[N][N], int kok, int mesafe[], int onceki[], int tabloYazdir) {
    int biliniyor[N];
    int i, adim, j;

    for (i = 0; i < N; i++) {
        biliniyor[i] = 0;
        mesafe[i] = INF;
        onceki[i] = -1;
    }

    mesafe[kok] = 0;

    if (tabloYazdir) {
        printf("\n--- 1. Dijkstra Adim Adim Tablo (Kok Dugum: %c) ---\n", dugumAdi(kok));
    }

    for (adim = 0; adim < N; adim++) {
        int enKucuk = INF;
        int secilen = -1;

        for (i = 0; i < N; i++) {
            if (!biliniyor[i] && mesafe[i] < enKucuk) {
                enKucuk = mesafe[i];
                secilen = i;
            }
        }

        if (secilen == -1) {
            break;
        }

        biliniyor[secilen] = 1;

        for (j = 0; j < N; j++) {
            if (!biliniyor[j] && graf[secilen][j] != INF) {
                if (mesafe[secilen] + graf[secilen][j] < mesafe[j]) {
                    mesafe[j] = mesafe[secilen] + graf[secilen][j];
                    onceki[j] = secilen;
                }
            }
        }

        if (tabloYazdir) {
            printf("\nAdim %d (Secilen Dugum: %c):\n", adim + 1, dugumAdi(secilen));
            printf("Dugum\tKnown\tDistance\tPath\n");
            for (i = 0; i < N; i++) {
                printf("%c\t%d\t", dugumAdi(i), biliniyor[i]);
                if (mesafe[i] == INF) {
                    printf("INF\t\t");
                } else {
                    printf("%d\t\t", mesafe[i]);
                }
                if (onceki[i] == -1) {
                    printf("-\n");
                } else {
                    printf("%c\n", dugumAdi(onceki[i]));
                }
            }
        }
    }

    int toplamMaliyet = 0;
    for (i = 0; i < N; i++) {
        if (mesafe[i] != INF) {
            toplamMaliyet += mesafe[i];
        }
    }
    return toplamMaliyet;
}

int main() {
    int graf[N][N];
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            graf[i][j] = (i == j) ? 0 : INF;
        }
    }

    /* Kenar listesi: (Baslangic, Bitis, Maliyet) */
    int kenarlar[10][3] = {
        {0, 1, 7}, /* A - B : 7 */
        {0, 2, 5}, /* A - C : 5 */
        {0, 5, 1}, /* A - F : 1 */
        {1, 2, 1}, /* B - C : 1 */
        {1, 3, 1}, /* B - D : 1 */
        {1, 4, 3}, /* B - E : 3 */
        {2, 3, 2}, /* C - D : 2 */
        {2, 4, 1}, /* C - E : 1 */
        {3, 5, 7}, /* D - F : 7 */
        {4, 5, 2}  /* E - F : 2 */
    };

    for (i = 0; i < 10; i++) {
        int u = kenarlar[i][0];
        int v = kenarlar[i][1];
        int w = kenarlar[i][2];
        graf[u][v] = w;
        graf[v][u] = w;
    }

    char secimHarf;
    printf("Kok dugumu giriniz (A-F): ");
    scanf(" %c", &secimHarf);

    int kok = harfToIndeks(secimHarf);
    if (kok == -1) {
        kok = 0; /* Gecersiz giriste varsayilan A */
    }

    int mesafe[N], onceki[N];
    dijkstraHesapla(graf, kok, mesafe, onceki, 1);

    /* 2. Gorev: Kok dugum A secildiginde B ve D rotalari */
    int mesafeA[N], oncekiA[N];
    dijkstraHesapla(graf, 0, mesafeA, oncekiA, 0);

    printf("\n--- 2. Kok Dugum A Icin En Kisa Rotalar ---\n");
    printf("A -> B Maliyet: %d | Rota: ", mesafeA[1]);
    yoluTerstenYazdir(oncekiA, 1);
    printf("\n");

    printf("A -> D Maliyet: %d | Rota: ", mesafeA[3]);
    yoluTerstenYazdir(oncekiA, 3);
    printf("\n");

    /* 3. Gorev: Tum dugumler icin merkezi dugum tespiti */
    printf("\n--- 3. Merkezi Dugum Analizi (Tum Dugumler) ---\n");
    int enMerkeziDugum = 0;
    int enDusukToplam = INF;

    for (i = 0; i < N; i++) {
        int geciciMesafe[N], geciciOnceki[N];
        int toplam = dijkstraHesapla(graf, i, geciciMesafe, geciciOnceki, 0);
        printf("Kok Dugum %c -> En Kisa Yol Agaci Toplam Maliyeti: %d\n", dugumAdi(i), toplam);

        if (toplam < enDusukToplam) {
            enDusukToplam = toplam;
            enMerkeziDugum = i;
        }
    }

    printf("\nEn Merkezi Dugum (Ana Aktarma Merkezi): %c (Toplam Maliyet: %d)\n",
           dugumAdi(enMerkeziDugum), enDusukToplam);

    system("pause");
    return 0;
}
