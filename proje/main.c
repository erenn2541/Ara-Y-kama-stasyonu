#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ARAC 100
#define STR_LEN 50
#define DOSYA_ADI "arac_kayitlari.txt" 

char plakalar[MAX_ARAC][STR_LEN];
char modeller[MAX_ARAC][STR_LEN];
char isimler[MAX_ARAC][STR_LEN];
char telefonlar[MAX_ARAC][STR_LEN];

int toplam_arac = 0; 

void dosyaya_kaydet(char* plaka, char* model, char* isim, char* tel);
int plaka_kontrol(char* aranan_plaka);
void yeni_kayit_ekrani(char* gelen_plaka);
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    char girilen_plaka[STR_LEN];
    int secim;

    while(1) {
        printf("\n=== OTO YIKAMA ISTASYONU ===\n");
        printf("1. Arac Girisi Yap\n");
        printf("2. Guncel Bekleme Listesi\n");
        printf("3. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        if (secim == 1) {
            printf("\n--- Arac Kabul ---\n");
            printf("Plaka Giriniz (Bosluksuz): ");
            scanf("%s", girilen_plaka);

            int indeks = plaka_kontrol(girilen_plaka);

            if (indeks != -1) {
                printf("\n>>> HOS GELDINIZ Sayin %s\n", isimler[indeks]);
                printf(">>> Arac Modeli: %s\n", modeller[indeks]);
            } else {
                printf("\n[BILGI] Bu plaka bu oturumda kayitli degil.\n");
                yeni_kayit_ekrani(girilen_plaka);
            }

        } else if (secim == 2) {
            printf("\n--- Guncel Oturum Kayitlari ---\n");
            printf("%-15s %-15s %-15s\n", "PLAKA", "MODEL", "ISIM");
            printf("-----------------------------------------------\n");
            int i=0;
            for(i = 0; i < toplam_arac; i++) {
                printf("%-15s %-15s %-15s\n", plakalar[i], modeller[i], isimler[i]);
            }
            
        } else if (secim == 3) {
            printf("Cikis yapiliyor...\n");
            break;
        } else {
            printf("Hatali secim!\n");
        }
    }
}

void dosyaya_kaydet(char* plaka, char* model, char* isim, char* tel) {

    strcpy(plakalar[toplam_arac], plaka);
    strcpy(modeller[toplam_arac], model);
    strcpy(isimler[toplam_arac], isim);
    strcpy(telefonlar[toplam_arac], tel);
    toplam_arac++;

    FILE *fp = fopen(DOSYA_ADI, "a"); 
    if (fp != NULL) {
        fprintf(fp, "%s %s %s %s\n", plaka, model, isim, tel);
        fclose(fp); 
    }
}

int plaka_kontrol(char* aranan_plaka) {
	int i=0;
    for (i = 0; i < toplam_arac; i++) {
        if (strcmp(plakalar[i], aranan_plaka) == 0) {
            return i;
        }
    }
    return -1;
}

void yeni_kayit_ekrani(char* gelen_plaka) {
    char model[STR_LEN], isim[STR_LEN], tel[STR_LEN];
    int istek;

    printf("\n--- Yeni Kayit ---\n");
    printf("Plaka: %s\n", gelen_plaka);
    
    printf("Arac Modeli: ");
    scanf("%s", model);

    printf("Bilgileri kaydet? (1:Evet, 0:Hayir): ");
    scanf("%d", &istek);

    if (istek == 1) {
        printf("Isim: ");
        scanf("%s", isim);
        printf("Telefon: ");
        scanf("%s", tel);
    } else {
        strcpy(isim, "Misafir");
        strcpy(tel, "-");
    }
    dosyaya_kaydet(gelen_plaka, model, isim, tel);
    printf("\n[KAYIT] Bilgiler 'arac_kayitlari.txt' dosyasina yazildi.\n");
}
