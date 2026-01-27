#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
    int kap;
    int aracSayisi = 0;
    int secim;

    char plaka[10];
    char otopark[100][10];    // Hafıza oluşturduk aynı plakalı aracı iki sefer alamamak için


    printf("\n\nOtopark sistemine hosgeldiniz\n\n");
    printf("Otoparkin kapasitesini belirleyiniz:\n");
    scanf("%d", &kap);

    do {
        printf("1-Araba Girisi\n");
        printf("2-Araba cikisi\n");
        printf("3-Otopark Durumu\n");
        printf("4-Arac Sorgulama\n");
        printf("5-Gunluk Kazanc Hesaplama\n");
        printf("6-Kurallara Gore Raporlama\n");
        printf("0-Programdan cikis\n");

        scanf("%d", &secim);

        switch (secim) {
        case 1: {
            if (aracSayisi >= kap) {
                printf("Otopark dolu!\n");
                break;
            }
            printf("Araba Girisi Secildi\n");
            printf("Plaka girin (bosluk kullanmayin): ");
            scanf("%s", plaka);

            // --- AYNI PLAKA KONTROLÜ BAŞLIYOR ---
            int plakaVarMi = 0;

            // Mevcut araç sayısına kadar listeyi tarıyoruz
            for (int i = 0; i < aracSayisi; i++) {
                // strcmp 0 olursa iki plaka aynıdır
                if (strcmp(otopark[i], plaka) == 0) {
                    plakaVarMi = 1; // Bulduk!
                    break;  // Aramayı durdur
                }
            }
            // ------------------------------------

            if (plakaVarMi == 1) {
                printf("HATA: %s plakali arac zaten iceride!\n", plaka);
            }
            else {
                // Listede yoksa, listeye ekle ve sayıyı artır
                strcpy(otopark[aracSayisi], plaka);
                aracSayisi++;
                printf("Giris Basarili. Arac sayisi: %d\n", aracSayisi);
            }
            break;
        }

        case 2:
            printf("Araba cikisi Secildi\n");
            printf("Cikarmak istediginiz plakayi girin (bosluk kullanmayin): ");
            scanf("%s", plaka);
            printf("cikarilan plaka: %s\n", plaka);
            aracSayisi--;
            break;

        case 3:
            printf("Otopark Durumu: %d/%d dolu\n", aracSayisi, kap);
            break;

        case 0:
            printf("Programdan cikiliyor...\n");
            break;

        default:
            printf("Hatali secim!\n");
        }
    } while (secim != 0);

    return 0;
}