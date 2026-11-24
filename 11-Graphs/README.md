Soru : Kenar listesine (2, 4) bağlantısı eklendiğinde programın çıktısının nasıl değiştiğini gözlemleyiniz ve nedenini açıklayınız.
Cevap: (2, 4) kenarı eklendiğinde 2 ve 4 düğümlerinin dereceleri 1'er artar ve grafın genel derecesi 4 olur; ayrıca graf Bipartite (EVET) durumundan Bipartite değil (HAYIR) durumuna geçer. Bunun nedeni, başlangıçta {1, 3, 5} (0 rengi) ve {2, 4, 6} (1 rengi) olarak iki ayrı kümeye ayrılan grafın aynı kümesindeki (1 rengindeki) 2 ve 4 düğümlerinin doğrudan bağlanmasıyla, komşu düğümlerin farklı renkte/paritede olması kuralının bozulmasıdır.

Soru : Kök düğüm A seçildiğinde, A düğümünden B ve D düğümlerine giden en düşük maliyetli yolları ve toplam maliyetlerini tersten okuma yöntemiyle (Örn: A -> F -> E -> C -> B) ekrana yazdırınız.
Cevap: A düğümünden B'ye giden en düşük maliyetli yol A -> F -> E -> C -> B olup toplam maliyeti 5'tir (1 + 2 + 1 + 1 = 5). A düğümünden D'ye giden en düşük maliyetli yol ise A -> F -> E -> C -> B -> D (veya aynı maliyetteki A -> F -> E -> C -> D) olup toplam maliyeti 6'dır (1 + 2 + 1 + 1 + 1 = 6).

Soru : Algoritmayı graftaki tüm düğümleri (A'dan F'ye) sırayla kök düğüm kabul edecek şekilde bir döngü içinde çalıştırınız. Her düğüm için oluşan en kısa yol ağacının toplam maliyetini hesaplayarak en düşük toplam maliyete sahip olan en merkezi düğümü bulunuz.
Cevap: Tüm düğümler kök alındığında en düşük toplam maliyete sahip en merkezi düğüm C düğümüdür (C kök alındığında diğer düğümlere en kısa mesafeler toplamı 12'dir; diğer düğümlerin toplamları sırasıyla A: 18, B: 13, C: 12, D: 15, E: 13, F: 15'tir).
