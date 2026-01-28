#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
    int kap;
    int aracSayisi = 0;
    int secim;
    int toplamKazanc = 0;

    char plaka[10];
    char otopark[100][10];    // Hafıza oluşturduk aynı plakalı aracı iki sefer alamamak için
    int girisSaatleri[100];
    int girisDakikalari[100];

    printf("\n\nOtopark sistemine hosgeldiniz\n\n");
    printf("Otoparkin kapasitesini belirleyiniz:\n");
    scanf("%d", &kap);

    do {
        printf("\n\n1-Araba Girisi\n");
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
            printf("\n\nAraba Girisi Secildi\n");
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
                // Saat ve Dakika bilgilerini al ve diziye kaydet
                printf("Giris saati (0-23): ");
                scanf("%d", &girisSaatleri[aracSayisi]);
                printf("Giris dakikasi (0-59): ");
                scanf("%d", &girisDakikalari[aracSayisi]);

                printf("Kayit Basarili! %s aracı %02d:%02d saatinde giris yapti.\n",
                    otopark[aracSayisi], girisSaatleri[aracSayisi], girisDakikalari[aracSayisi]);

                aracSayisi++; // Her şey tamamsa araç sayısını artır
            }
            break;
        }

        case 2:{
            printf("\n\nAraba cikisi Secildi\n");
            printf("Cikarmak istediginiz plakayi girin (bosluk kullanmayin): ");
            scanf("%9s", plaka);


			int bulundu = -1;
            for (int i = 0; i < aracSayisi; i++) {
                if (strcmp(otopark[i], plaka) == 0) {
                    bulundu = i; break;
                }
            }
            if (bulundu == -1) {
                printf("Arac bulunamadi!\n");
            }
                  
            else {
				int cikissaat = 0;
				int cikisdakika = 0;
				int ucret = 0;
				printf("Arac cikis saati (0-23) giriniz: ");
				scanf("%d", &cikissaat);
				printf("Arac cikis dakikasi (0-59) giriniz: ");
				scanf("%d", &cikisdakika);

                // Toplam kalinan saati hesapla (Basit mantik)
                int farkDakika = (cikissaat * 60 + cikisdakika) - (girisSaatleri[bulundu] * 60 + girisDakikalari[bulundu]);
                if (farkDakika < 0) farkDakika += 24 * 60; // Gece yarisini gectiyse

                int toplamSaat = farkDakika / 60;
                if (farkDakika % 60 > 0) toplamSaat++; // 1 dakika bile gecse tam saat sayilir

                // Tarifeyi belirle (Giris saatine gore)
                int gSaat = girisSaatleri[bulundu];
                if (gSaat >= 6 && gSaat < 22) { // GUNDUZ TARIFESI
                    if (toplamSaat <= 4) ucret = 50 + (toplamSaat - 1) * 20;
                    else ucret = 110 + (toplamSaat - 4) * 40;
                    printf("Gunduz tarifesi uygulandi.\n");
                }
                else { // GECE TARIFESI
                    if (toplamSaat <= 4) ucret = toplamSaat * 100;
                    else ucret = 400 + (toplamSaat - 4) * 150;
                    printf("Gece tarifesi uygulandi.\n");
                }

                printf("Sure: %d saat | Borcunuz: %d TL\n", toplamSaat, ucret);
                toplamKazanc += ucret; // Kazancı ekle

                // Aracı diziden silme (Kaydirma islemi)
                for (int j = bulundu; j < aracSayisi - 1; j++) {
                    strcpy(otopark[j], otopark[j + 1]);
                    girisSaatleri[j] = girisSaatleri[j + 1];
                    girisDakikalari[j] = girisDakikalari[j + 1];
                }
                aracSayisi--;
                }
                break;
        }

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