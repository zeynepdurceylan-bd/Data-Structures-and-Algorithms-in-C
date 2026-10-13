#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hasta düğüm (node) yapısı tanımı
struct Hasta {
    int id;
    char isim[50];
    char durum[20]; // "bekliyor", "muayenede", "tamamlandi"
    struct Hasta* next;
};

// Kuyruk (Queue) için başlangıç ve bitiş göstericileri
struct Hasta *kuyrukBas = NULL;
struct Hasta *kuyrukSon = NULL;

// Yığın (Stack) için tepe (top) göstericisi
struct Hasta *yiginTepe = NULL;

// Geçmiş Kayıtlar (Linked List) için başlangıç ve bitiş göstericileri
struct Hasta *gecmisBas = NULL;
struct Hasta *gecmisSon = NULL;

// 1. Kuyruğa Eleman Ekleme (Enqueue - FIFO mantığı)
void enqueue(int id, const char *isim) {
    struct Hasta *yeni = (struct Hasta*)malloc(sizeof(struct Hasta));
    yeni->id = id;
    strcpy(yeni->isim, isim);
    strcpy(yeni->durum, "bekliyor");
    yeni->next = NULL;

    if (kuyrukSon == NULL) {
        kuyrukBas = yeni;
        kuyrukSon = yeni;
    } else {
        kuyrukSon->next = yeni;
        kuyrukSon = yeni;
    }
}

// 2. Kuyruktan Eleman Çıkarma (Dequeue)
struct Hasta* dequeue() {
    if (kuyrukBas == NULL) {
        return NULL;
    }
    struct Hasta *silinecek = kuyrukBas;
    kuyrukBas = kuyrukBas->next;
    if (kuyrukBas == NULL) {
        kuyrukSon = NULL;
    }
    silinecek->next = NULL;
    return silinecek;
}

// 3. Yığına Eleman Ekleme (Push)
void push(struct Hasta *h) {
    strcpy(h->durum, "muayenede");
    h->next = yiginTepe;
    yiginTepe = h;
}

// 4. Yığından Eleman Çıkarma (Pop - LIFO mantığı)
struct Hasta* pop() {
    if (yiginTepe == NULL) {
        return NULL;
    }
    struct Hasta *alinan = yiginTepe;
    yiginTepe = yiginTepe->next;
    alinan->next = NULL;
    strcpy(alinan->durum, "tamamlandi");
    return alinan;
}

// 5. Geçmiş Listesine Ekleme (Linked List)
void gecmiseEkle(struct Hasta *h) {
    h->next = NULL;
    if (gecmisBas == NULL) {
        gecmisBas = h;
        gecmisSon = h;
    } else {
        gecmisSon->next = h;
        gecmisSon = h;
    }
}

// Listeleme Fonksiyonları
void listeleBekleyenler() {
    printf("\n--- Bekleyen Hastalar ---\n");
    struct Hasta *temp = kuyrukBas;
    if (temp == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->isim, temp->durum);
        temp = temp->next;
    }
}

void listeleMuayene() {
    printf("\n--- Muayene Odasindaki Hastalar ---\n");
    struct Hasta *temp = yiginTepe;
    if (temp == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->isim, temp->durum);
        temp = temp->next;
    }
}

void listeleTamamlananlar() {
    printf("\n--- Tamamlanan Hastalar ---\n");
    struct Hasta *temp = gecmisBas;
    if (temp == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->isim, temp->durum);
        temp = temp->next;
    }
}

int main() {
    // 4. Hastaları belirtilen sırayla sisteme kaydediniz.
    enqueue(1, "Ahmet");
    enqueue(2, "Mehmet");
    enqueue(3, "Ayse");

    // 5. Ahmet'i muayeneye alıp muayenesini tamamlayınız.
    struct Hasta *h1 = dequeue();
    if (h1 != NULL) {
        push(h1);
        struct Hasta *bitti1 = pop();
        gecmiseEkle(bitti1);
    }

    // 6. Mehmet'i muayeneye alıp muayenesini tamamlayınız.
    struct Hasta *h2 = dequeue();
    if (h2 != NULL) {
        push(h2);
        struct Hasta *bitti2 = pop();
        gecmiseEkle(bitti2);
    }

    // 7. Ayşe'yi bekleme kuyruğunda bırakınız (Zaten kuyrukta bekliyor).

    // 8. Tüm işlemler sonrasındaki durumu ekrana yazdırınız.
    printf("=== Tum Islemler Sonrasi ===");
    listeleBekleyenler();
    listeleMuayene();
    listeleTamamlananlar();

    return 0;
}
