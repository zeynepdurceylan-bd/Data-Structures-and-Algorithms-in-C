#include <stdio.h>
#include <stdlib.h> // malloc ve free fonksiyonları için gerekli kütüphane

// İkili Arama Ağacı (BST) Düğüm Yapısı
struct Node {
    int data;           // Düğümün sakladığı sayı (hazine değeri)
    struct Node* left;  // Sol çocuk düğümün bellekteki adresini tutan işaretçi (pointer)
    struct Node* right; // Sağ çocuk düğümün bellekteki adresini tutan işaretçi (pointer)
};

// Yeni bir düğüm oluşturma fonksiyonu
struct Node* newNode(int data) {
    // Belleğin Heap (yığın) bölgesinde yeni bir düğüm için yer ayırıyoruz (malloc ile dinamik bellek tahsisi)
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    
    node->data = data;   // Düğümün veri alanına gelen sayıyı yazıyoruz
    node->left = NULL;   // Başlangıçta sol çocuk yok, NULL (hiçbir yeri göstermiyor)
    node->right = NULL;  // Başlangıçta sağ çocuk yok, NULL
    
    return node;         // Oluşturulan düğümün adresini döndürüyoruz
}

// Ağaca yeni eleman ekleme fonksiyonu (Rekürsif - Öz yinelemeli)
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return newNode(data); // Eğer kök boşsa, yeni düğüm oluşturup oraya yerleştiriyoruz
    }
    
    if (data < root->data) {
        // Eklenecek sayı mevcut düğümden küçükse sol dala git (&root->left adresini günceller)
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        // Eklenecek sayı mevcut düğümden büyükse sağ dala git
        root->right = insert(root->right, data);
    }
    
    return root; // Kök düğümün güncel adresini döndürür
}

// Ödev Görevi: Rekürsif olarak hazineyi arama ve ziyaret edilenleri yazdırma
int searchTreasure(struct Node* root, int target, int* stepCount) {
    if (root == NULL) {
        return 0; // Ağacın sonuna gelindi ve bulunamadı (0 = Yanlış/Bulunamadı)
    }
    
    // Bonus 1: Her adımda ziyaret edilen düğümü ekrana yazdır
    (*stepCount)++; // stepCount pointer'ı (işaretçisi) aracılığıyla adım sayısını 1 artırıyoruz
    printf("%d. Adim: Ziyaret edilen dugum -> %d\n", *stepCount, root->data);
    
    if (root->data == target) {
        return 1; // Hazine bulundu! (1 = Doğru/Bulundu)
    }
    
    if (target < root->data) {
        // Aranan sayı küçükse sol alt ağaca geç (rekürsif arama)
        return searchTreasure(root->left, target, stepCount);
    } else {
        // Aranan sayı büyükse sağ alt ağaca geç (rekürsif arama)
        return searchTreasure(root->right, target, stepCount);
    }
}

// Bonus 2: Ağacın yüksekliğini bularak en kötü durumda kaç adım gerekeceğini hesaplama
int getHeight(struct Node* root) {
    if (root == NULL) {
        return 0; // Boş ağacın yüksekliği 0'dır
    }
    
    int leftHeight = getHeight(root->left);   // Sol dalın yüksekliği
    int rightHeight = getHeight(root->right); // Sağ dalın yüksekliği
    
    // Hangisi daha derinse onu seçip kök için +1 ekliyoruz
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

int main() {
    struct Node* root = NULL; // Ağacın kök (root) işaretçisini (pointer) başlangıçta boş (NULL) tanımlıyoruz
    
    // Örnek bir İkili Arama Ağacı (BST) elemanlarını ekleyelim:
    //         50
    //       /    \
    //     30      70
    //    /  \    /  \
    //   20  40  60  80
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int i;
    for (i = 0; i < 7; i++) {
        root = insert(root, values[i]); // Elemanları ağaca yerleştiriyoruz
    }
    
    int guess;
    printf("--- Hazine Agaci Oyunu (Treasure Tree Game) ---\n");
    printf("Aramak icin bir sayi (hazine degeri) girin: ");
    scanf("%d", &guess); // Kullanıcıdan arayacağı sayıyı alıyoruz
    
    int steps = 0;
    printf("\nArama Sureci Basliyor:\n");
    
    // searchTreasure fonksiyonuna 'steps' değişkeninin bellekteki adresini (&) gönderiyoruz ki fonksiyon içinde güncellenebilsin (pointer mantığı)
    int found = searchTreasure(root, guess, &steps);
    
    printf("\n----------------------------------------\n");
    if (found) {
        printf("Sonuc: Hazine bulundu!\n");
    } else {
        printf("Sonuc: Bosuna kazdin!\n");
    }
    
    // Bonus 2 Bilgisi: Ağacın yüksekliği en kötü senaryoda gereken maksimum adım sayısını verir
    int treeHeight = getHeight(root);
    printf("\n[Bonus Bilgisi] Agac yuksekligi (En kotu durumda gereken maksimum adim): %d\n", treeHeight);
    
    return 0;
}
