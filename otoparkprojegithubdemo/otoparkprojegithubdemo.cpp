#define _CRT_SECURE_NO_WARNINGS 
// DİKKAT VİSUAL STUDİO HARİCİ KULLANIYORSANIZ KODU SİLİN #define _CRT_SECURE_NO_WARNINGS 


#include <stdio.h>
#include <iostream>

int main()
{
	printf("\n\n");
	printf("Otopark sistemine hosgeldiniz\n");
	printf("\n\n");


	printf("otoparkin kapasitesini belirleyiniz:\n");
	int kap;
	scanf("%d", &kap);






	printf("1-Araba Girisi\n");
	printf("2-Araba cikisi\n");
	printf("3-Otopark Durumu\n");
	printf("4-Arac Sorgulama\n");
	printf("5-Gunluk Kazanc Hesaplama\n");
	printf("6-Kurallara Gore Raporlama\n");
	printf("7-Programdan cikis\n");

	int secim;
	scanf("%d", &secim);

	
		switch (secim)
	{
	case 1:
		printf("Araba Girisi Seçildi\n");
		printf("\n\n");
		printf("plaka girin bosluk kullanmayin:\n");
		char plaka[10];
		scanf("%s", &plaka);
		printf("Girilen plaka: %s\n", plaka);





		break;
	case 2:
		printf("Araba cikisi Seçildi\n");
		printf("\n\n");
		printf("cikarmak istediginiz plakayi secin\n");
		printf("%s\n", plaka);






		break;
	case 3:
		printf("Otopark Durumu Seçildi\n");
		break;
	case 4:
		printf("Araç Sorgulama Seçildi\n");
		break;
	case 5:
		printf("Günlük Kazanç Hesaplama Seçildi\n");
		break;
	case 6:
		printf("Kurallara Göre Raporlama Seçildi\n");
		break;
	case 7:
		printf("Programdan Çıkış Seçildi\n");
		break;
	}















}