#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct PrintJob {
    char fileName[50];       
    struct PrintJob* next;   
} PrintJob;


typedef struct Queue {
    PrintJob* front;       
    PrintJob* rear;       
} Queue;


void enqueuePrintJob(Queue* q, char* fileName);
void processNextJob(Queue* q);
void showQueue(Queue q);


int main() {
  
    Queue q;
    q.front = NULL;
    q.rear = NULL;

    int secim;
    char dosyaAdi[50];

    do {
        printf("\n================ YAZICI KUYRUGU ================\n");
        printf("1) Yeni Dosya Ekle (enqueuePrintJob)\n");
        printf("2) Yazdir / Islemi Gerceklestir (processNextJob)\n");
        printf("3) Kuyrugu Goster (showQueue)\n");
        printf("0) Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);
        getchar(); // Buffer'da kalan yeni satır (\n) karakterini temizler

        switch (secim) {
            case 1:
                printf("Eklenecek Dosya Adini Giriniz: ");
                fgets(dosyaAdi, sizeof(dosyaAdi), stdin);
                dosyaAdi[strcspn(dosyaAdi, "\n")] = 0; // Sondaki \n karakterini siler
                enqueuePrintJob(&q, dosyaAdi);
                break;

            case 2:
                processNextJob(&q);
                break;

            case 3:
                showQueue(q);
                break;

            case 0:
                printf("Yazici simulasyonundan cikiliyor...\n");
                break;

            default:
                printf("Gecersiz secim! Tekrar deneyiniz.\n");
        }
    } while (secim != 0);

    // Bellekte kalan elemanları temizleme
    while (q.front != NULL) {
        processNextJob(&q);
    }

    return 0;
}

// FONKSİYON TANIMLARI 

// Kuyruğa Yeni Dosya Ekleme (Enqueue / Sona Ekleme)
void enqueuePrintJob(Queue* q, char* fileName) {
    // 1. Yeni düğüm için bellekten yer ayırma
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    if (newJob == NULL) {
        printf("Bellek yetersiz!\n");
        return;
    }

    // 2. Veriyi kopyalama ve next göstericisini NULL yapma
    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;

    // Durum 1: Kuyruk boşsa
    if (q->front == NULL) {
        q->front = newJob;
        q->rear = newJob;
    } 
    // Durum 2: Kuyrukta eleman varsa (Sona ekleme)
    else {
        q->rear->next = newJob; // Eski sonuncunun arkasına bağla
        q->rear = newJob;       // Kuyruğun yenilenen sonuncusu yap
    }

    printf("'%s' dosyasi yazici kuyruguna eklendi.\n", fileName);
}

// Sıradaki İşi Yazdırma ve Çıkarma (Dequeue / Baştan Çıkarma)
void processNextJob(Queue* q) {
    // İpucu Kontrolü: Kuyruk boşken yazdırma işlemi yapılmamalı!
    if (q->front == NULL) {
        printf("Kuyruk bos! Yazdirilacak dosya yok.\n");
        return;
    }

    // Çıkarılacak elemanı geçici değişkene alma (front / en öndeki eleman)
    PrintJob* temp = q->front;

    printf("Yazdiriliyor: >>> %s <<<\n", temp->fileName);

    // Front göstericisini bir sonraki düğüme kaydırma
    q->front = q->front->next;

    // Eğer son eleman da çıkarıldıysa rear da NULL olmalıdır
    if (q->front == NULL) {
        q->rear = NULL;
    }

    // Belleği temizleme
    free(temp);
}

// Kuyruğu Baştan Sona Doğru Listeleme (Show)
void showQueue(Queue q) {
    if (q.front == NULL) {
        printf("Kuyruk bos!\n");
        return;
    }

    printf("\n--- YAZICI BEKLEME KUYRUGU (Önden Arkaya) ---\n");
    PrintJob* temp = q.front;
    int sira = 1;

    while (temp != NULL) {
        printf("%d. %s", sira++, temp->fileName);
        if (temp == q.front) {
            printf("  <-- [Siradaki Yazdirilacak]");
        }
        printf("\n");
        temp = temp->next;
    }
    printf("---------------------------------------------\n");
}
