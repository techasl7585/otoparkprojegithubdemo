#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
    int kap;
    int aracSayisi = 0;
    int secim;
    int toplamKazanc = 0;
    int toplamGirisYapan = 0;
    int toplamCikisYapan = 0;


    char plaka[10];
    char otopark[100][10];    // Hafıza oluşturduk aynı plakalı aracı iki sefer alamamak için
    int girisSaatleri[100];
    int girisDakikalari[100];
	int cikissaatleri[100];
	int cikisdakikalari[100];


    // Geçmiş kayıtlar için (Arşiv)
    char gecmisOtopark[100][10];
    int gecmisGirisS[100], gecmisGirisD[100];
    int gecmisCikisS[100], gecmisCikisD[100];
    int gecmisUcret[100];
    int toplamCikanArac = 0; // Bu sayaç hiç azalmaz, her çıkışta artar










    printf("\n\nOtopark sistemine hosgeldiniz\n\n");
    printf("Otoparkin kapasitesini belirleyiniz:\n");
    scanf("%d", &kap);

    do {
        printf("\n\n1-Araba Girisi\n");
        printf("2-Araba cikisi\n");
        printf("3-Otopark Durumu\n");
        printf("4-Arac Sorgulama\n");
        printf("5-Gunluk Kazanc Hesaplama\n");
        printf("6-Raporlama\n");
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
                toplamGirisYapan++;
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


                // --- HAFIZAYA ALMA (ARŞİVLEME) BURADA BAŞLIYOR ---
                strcpy(gecmisOtopark[toplamCikanArac], otopark[bulundu]);
                gecmisGirisS[toplamCikanArac] = girisSaatleri[bulundu];
                gecmisGirisD[toplamCikanArac] = girisDakikalari[bulundu];
                gecmisCikisS[toplamCikanArac] = cikissaat;
                gecmisCikisD[toplamCikanArac] = cikisdakika;
                // ------------------------------------------------



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

                gecmisUcret[toplamCikanArac] = ucret; // Ücreti de hafızaya al
                toplamCikanArac++; // Arşiv sayacını artır
                toplamKazanc += ucret;

                printf("Sure: %d saat | Borc: %d TL. Cikis yapildi.\n", toplamSaat, ucret);



                // Aracı diziden silme (Kaydirma islemi)
                for (int j = bulundu; j < aracSayisi - 1; j++) {
                    strcpy(otopark[j], otopark[j + 1]);
                    girisSaatleri[j] = girisSaatleri[j + 1];
                    girisDakikalari[j] = girisDakikalari[j + 1];
                }
                aracSayisi--;
                toplamCikisYapan++;
                }
                break;
        }

        case 3:
            printf("\nOtopark Durumu: %d/%d dolu\n", aracSayisi, kap);
			printf("\nIcerideki araclar:\n");
            for (int i = 0; i < aracSayisi; i++) {
                printf("%d. Aracin Plakasi: %9s            --Giris saati: %3d:%3d ---   \n", i + 1, otopark[i], girisSaatleri[i], girisDakikalari[i]);
            }
            printf("\nCikan araclar:\n");
            for (int i = 0; i < toplamCikanArac; i++) {
                printf("%d. Aracin Plakasi: %9s            --Cikis saati: %3d:%3d ---   \n", i + 1, gecmisOtopark[i], gecmisCikisS[i], gecmisCikisD[i]);
            }

	
            break;

        case 4: {
            printf("\nSorgulamak istediginiz aracin plakasini giriniz: ");
            scanf("%9s", plaka);

            int bulunduIndeks = -1; // Değişken ismini karışmaması için değiştirdik

            // Sadece mevcut araçlar içinde ara
            for (int i = 0; i < aracSayisi; i++) {
                if (strcmp(otopark[i], plaka) == 0) {
                    bulunduIndeks = i;
                    break; // Aracı bulduğumuz an döngüden çıkıyoruz
                }
            }

            // SONUÇ GÖSTERME (Döngü bittikten sonra yapılır)
            if (bulunduIndeks != -1) {
                printf("\n>>> Arac Otoparkta!\n");
                printf("Plaka: %s\n", otopark[bulunduIndeks]);
                printf("Giris Zamani: %02d:%02d\n", girisSaatleri[bulunduIndeks], girisDakikalari[bulunduIndeks]);
            }
            else {
                printf("\n>>> HATA: %s plakali arac otoparkta bulunamadi.\n", plaka);
            }
            break;
        }
        case 5: {

            printf("\ngunluk kazanc: %d", toplamKazanc);

            break;
        }
        case  6:
        {
            printf("\n bugun su kadar arac giris yapmistir: %d", toplamGirisYapan);
            printf("\n bugun su kadar arac cikis yapmistir: %d", toplamCikisYapan);
			printf("\n bugunki toplam kazanc: %d", toplamKazanc);

            break;
        }
              
        case 0:
            printf("Programdan cikiliyor...\n");
            break;

        default:
            printf("Hatali secim!\n");
        }
    } while (secim != 0);

    return 0;
}