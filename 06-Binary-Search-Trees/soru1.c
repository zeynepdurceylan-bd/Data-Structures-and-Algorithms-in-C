#include <stdio.h>
#include <stdlib.h>

// 1. Düğüm (Node) Yapısının Tanımlanması
struct Node {
    int data;           // Düğümün içinde tutulan tam sayı veri
    struct Node *left;  // Sol çocuk düğümün adresini tutan pointer
    struct Node *right; // Sağ çocuk düğümün adresini tutan pointer
};

// 2. Yeni Düğüm Oluşturan Yardımcı Fonksiyon
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 3. Ağaca Eleman Ekleyen Fonksiyon (insert)
struct Node* insert(struct Node* root, int data) {
    // Ağaç boşsa veya eklenecek yere gelindiyse yeni düğüm oluştur ve döndür
    if (root == NULL) {
        return newNode(data);
    }

    // Eklenen değer kökten küçükse sol alt ağaca git
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    // Eklenen değer kökten büyükse sağ alt ağaca git
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // Eğer aynı değer tekrar verilirse ekleme yapma, aynen bırak
    return root;
}

// 4. Inorder Dolaşma Fonksiyonu (Sol -> Kök -> Sağ)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);        // Önce sol alt ağaca git
        printf("%d ", root->data);  // Sonra kök düğümü yazdır
        inorder(root->right);       // En son sağ alt ağaca git
    }
}

int main() {
    struct Node* root = NULL; // Başlangıçta ağaç boş

    // Program istenen değerleri sırasıyla ekliyor (Aynı değer tekrar eklenmez)
    root = insert(root, 40);
    root = insert(root, 20);
    root = insert(root, 60);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 50);
    root = insert(root, 70);

    // Beklenen çıktı: Inorder: 10 20 30 40 50 60 70
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    return 0;
}
