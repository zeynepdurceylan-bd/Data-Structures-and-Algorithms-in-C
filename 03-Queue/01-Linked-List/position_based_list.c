#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Word {
    char text[50];        
    struct Word* next;    
} Word;

void pushWord(Word** top, char* text);
void popWord(Word** top);
void showWords(Word* top);


int main() {
    Word* top = NULL;
    char komut[10];
    char kelime[50];

    printf("=== UNDO (GERİ ALMA) SIMULASYONU ===\n");
    printf("Komutlar: add <kelime>, undo, show, exit\n\n");

    while (1) {
        printf("> ");
        scanf("%s", komut); 

        if (strcmp(komut, "add") == 0) {
            scanf("%s", kelime); // "add" komutundan sonra gelen kelimeyi oku
            pushWord(&top, kelime);
        } 
        else if (strcmp(komut, "undo") == 0) {
            popWord(&top);
        } 
        else if (strcmp(komut, "show") == 0) {
            showWords(top);
        } 
        else if (strcmp(komut, "exit") == 0) {
            printf("Programdan cikiliyor...\n");
            break;
        } 
        else {
            printf("Gecersiz komut!\n");
        }
    }

    // Bellekte kalan tüm düğümleri temizleme
    while (top != NULL) {
        popWord(&top);
    }

    return 0;
}

// FONKSİYON TANIMLARI 

// Stack'e Kelime Ekleme (Push / Ekle)
void pushWord(Word** top, char* text) {
    // 1. Dinamik bellek tahsisi
    Word* newWord = (Word*)malloc(sizeof(Word));
    if (newWord == NULL) {
        printf("Bellek yetersiz!\n");
        return;
    }

    // 2. Verileri düğüme yazma
    strcpy(newWord->text, text);

    // 3. Yeni elemanı Stack'in tepesine yerleştirme
    newWord->next = *top; // Yeni eleman eski tepeyi göstersin
    *top = newWord;       // Tepe noktası artık yeni eleman olsun
}

// Stack'ten Son Kelimeyi Çıkarma (Pop / Geri Al - Undo)
void popWord(Word** top) {
    // Kontrol: Stack boş mu?
    if (*top == NULL) {
        printf("Undo yapilacak kelime yok! (Stack bos)\n");
        return;
    }

    // Silinecek tepedeki düğümü geçici bir değişkene alma
    Word* temp = *top;

    // Tepe noktasını bir alttaki düğüme kaydırma
    *top = (*top)->next;

    
    free(temp);
}

// Stack'teki Kelimeleri Baştan Sona Doğru Yazdırma (Show)
void showWords(Word* top) {
    if (top == NULL) {
        printf("-> (Metin bos)\n");
        return;
    }

  

    Word* temp = top;
    char kelimeler[100][50];
    int sayac = 0;

    // Tepeden tabana kelimeleri toplama
    while (temp != NULL) {
        strcpy(kelimeler[sayac], temp->text);
        sayac++;
        temp = temp->next;
    }

    // İlk eklenenden son eklenene doğru tersten ekrana yazırma
    printf("-> ");
    for (int i = sayac - 1; i >= 0; i--) {
        printf("%s ", kelimeler[i]);
    }
    printf("\n");
}
