#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int kap;
    int aracSayisi = 0;
    int secim;
    char plaka[10];


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
        case 1:
            if (aracSayisi >= kap) {
                printf("Otopark dolu!\n");
                break;
            }
            printf("Araba Girisi Seçildi\n");
            printf("Plaka girin (bosluk kullanmayin): ");
            scanf("%s", plaka);
            printf("Girilen plaka: %s\n", plaka);
            aracSayisi++;
            break;

        case 2:
            printf("Araba cikisi Seçildi\n");
            printf("Cikarmak istediginiz plaka: %s\n", plaka);
            if (aracSayisi > 0) aracSayisi--;
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