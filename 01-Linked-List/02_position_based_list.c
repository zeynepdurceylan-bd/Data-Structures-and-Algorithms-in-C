#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Song {
    char name[50];         
    struct Song* next;     
    struct Song* prev;     
} Song;


void addSongToEnd(Song** head, char* name);
void removeSong(Song** head, char* name);
void playNext(Song** current);
void playPrevious(Song** current);
void displayPlaylist(Song* head);


int main() {
    Song* head = NULL;    
    Song* current = NULL; 
    int secim;
    char sarkiAdi[50];

    do {
        printf("\n================ MUZIK CALAR ================\n");
        if (current != NULL) {
            printf("Su An Calan Sarki: >>> %s <<<\n", current->name);
        } else {
            printf("Su An Calan Sarki: Yok\n");
        }
        printf("---------------------------------------------\n");
        printf("1. Sona Sarki Ekle (addSongToEnd)\n");
        printf("2. Sarki Sil (removeSong)\n");
        printf("3. Sonraki Sarkiya Gec (playNext)\n");
        printf("4. Önceki Sarkiya Gec (playPrevious)\n");
        printf("5. Çalma Listesini Göster (displayPlaylist)\n");
        printf("0. Çıkış\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);
        getchar(); // Buffer'da kalan yeni satır (\n) karakterini temizler

        switch (secim) {
            case 1:
                printf("Eklenecek Sarki Adi: ");
                fgets(sarkiAdi, sizeof(sarkiAdi), stdin);
                sarkiAdi[strcspn(sarkiAdi, "\n")] = 0; // Sondaki \n karakterini siler
                addSongToEnd(&head, sarkiAdi);
                // Liste ilk defa oluşuyorsa çalan şarkıyı başa ayarla
                if (current == NULL) {
                    current = head;
                }
                break;

            case 2:
                printf("Silinecek Sarki Adi: ");
                fgets(sarkiAdi, sizeof(sarkiAdi), stdin);
                sarkiAdi[strcspn(sarkiAdi, "\n")] = 0;
                
                // Silinecek şarkı o an çalan şarkıysa, çalan şarkıyı kaydır
                if (current != NULL && strcmp(current->name, sarkiAdi) == 0) {
                    if (current->next != NULL) {
                        current = current->next;
                    } else {
                        current = current->prev;
                    }
                }
                removeSong(&head, sarkiAdi);
                break;

            case 3:
                playNext(&current);
                break;

            case 4:
                playPrevious(&current);
                break;

            case 5:
                displayPlaylist(head);
                break;

            case 0:
                printf("Müzik çalar kapatılıyor...\n");
                break;

            default:
                printf("Gecersiz secim! Tekrar deneyiniz.\n");
        }
    } while (secim != 0);

    return 0;
}

//FONKSİYON TANIMLARI

// Listenin Sonuna Şarkı Ekleme
void addSongToEnd(Song** head, char* name) {
    // Yeni düğüm için bellekten yer ayırma
    Song* newSong = (Song*)malloc(sizeof(Song));
    if (newSong == NULL) {
        printf("Bellek yetersiz!\n");
        return;
    }

    // Verileri atama
    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    // Durum 1: Liste boşsa
    if (*head == NULL) {
        *head = newSong;
        printf("'%s' listeye eklendi (İlk şarkı).\n", name);
        return;
    }

    // Durum 2: Listenin sonuna kadar gitme
    Song* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Bağlantıları kurma
    temp->next = newSong;
    newSong->prev = temp;
    printf("'%s' listenin sonuna eklendi.\n", name);
}

// İsme Göre Şarkı Silme
void removeSong(Song** head, char* name) {
    // Kontrol: Liste boş mu?
    if (*head == NULL) {
        printf("Liste boş! Silinecek şarkı yok.\n");
        return;
    }

    Song* temp = *head;

    // Aranan şarkıyı bulana kadar ilerle
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    // Şarkı listede bulunamadıysa
    if (temp == NULL) {
        printf("'%s' adli sarki listede bulunamadi!\n", name);
        return;
    }

    // Durum 1: Silinecek eleman ilk eleman (head) ise
    if (temp == *head) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } 
    // Durum 2: Silinecek eleman arada veya sonda ise
    else {
        temp->prev->next = temp->next;
        if (temp->next != NULL) { // Sonda değilse
            temp->next->prev = temp->prev;
        }
    }

    free(temp); // Belleği serbest bırakma
    printf("'%s' adli sarki listeden silindi.\n", name);
}

// Bir Sonraki Şarkıya Geçme
void playNext(Song** current) {
    if (*current == NULL) {
        printf("Liste boş! Çalınacak şarkı yok.\n");
        return;
    }

    if ((*current)->next != NULL) {
        *current = (*current)->next;
        printf("Sonraki şarkıya geçildi: %s\n", (*current)->name);
    } else {
        printf("Listenin sonundasınız! Sonraki şarkı yok.\n");
    }
}

// Bir Önceki Şarkıya Geçme
void playPrevious(Song** current) {
    if (*current == NULL) {
        printf("Liste boş! Çalınacak şarkı yok.\n");
        return;
    }

    if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Önceki şarkıya geçildi: %s\n", (*current)->name);
    } else {
        printf("Listenin başındasınız! Önceki şarkı yok.\n");
    }
}

// Tum Çalma Listesini Yazdırma
void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("Liste boş!\n");
        return;
    }

    printf("\n--- CALMA LISTESI ---\n");
    Song* temp = head;
    int sira = 1;
    while (temp != NULL) {
        printf("%d. %s\n", sira++, temp->name);
        temp = temp->next;
    }
    printf("---------------------\n");
}
