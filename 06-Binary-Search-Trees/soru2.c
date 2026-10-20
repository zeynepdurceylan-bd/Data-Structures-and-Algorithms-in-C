#include <stdio.h>
#include <stdlib.h>

// Düğüm (Node) Yapısı
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Yeni Düğüm Oluşturan Fonksiyon
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Ağaca Eleman Ekleyen Fonksiyon (insert)
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Arama Fonksiyonu (Bulunduysa 1, bulunamadıysa 0 döndürür)
int search(struct Node* root, int key) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == key) {
        return 1;
    }
    if (key < root->data) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// Ağaktaki en küçük değeri döndüren fonksiyon
int findMin(struct Node* root) {
    struct Node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

int main() {
    struct Node* root = NULL;
    int numbers[] = {40, 20, 60, 10, 30, 50, 70};

    // Ağacı oluşturma
    for (int i = 0; i < 7; i++) {
        root = insert(root, numbers[i]);
    }

    // 30 değerini aratma
    if (search(root, 30))
        printf("30 agacta bulundu.\n");
    else
        printf("30 agacta bulunamadi.\n");

    // 90 değerini aratma
    if (search(root, 90))
        printf("90 agacta bulundu.\n");
    else
        printf("90 agacta bulunamadi.\n");

    // En küçük elemanı bulup yazdırma
    if (root != NULL)
        printf("En kucuk eleman: %d\n", findMin(root));

    return 0;
}

/* 
 SORULARININ YANITLARI


Cevap 1 : 25 değeri eklenirse 30 değerine sahip düğümün 
           sol çocuğu olarak yerleşir.

Cevap 2 : Preorder dolaşma elde edilir.

Cevap 3 : findMin() içinde left yerine right takip edilirse ağacın en büyük elemanı (Maximum) bulunur.
*/
