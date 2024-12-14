#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Global character attributes
char ozan_adi[50], calgi[50];
int can = 100, tokluk = 100, uyku = 100, hijyen = 100, altin = 10;
int guc = 3, ceviklik = 3, dayaniklilik = 3, karizma = 3, toplayicilik = 3;
int seviye = 1, tecrube = 0;

void menu();
void kamp_alani();
void sifahane();
void han();
void macera();
void seviye_atla();
void durumu_goster();
void kontrol_nitelikler();
void savas_sistemi(int zorluk);

void temizle() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Nitelik kontrol fonksiyonu
void kontrol_nitelikler() {
    // Kritik seviyelerde uyari ve can kaybi
    if (tokluk <= 20) {
        printf("UYARI: Tokluk seviyeniz kritik durumdadir!\n");
        can -= 20;
    }
    if (uyku <= 20) {
        printf("UYARI: Uyku seviyeniz kritik durumdadir!\n");
        can -= 10;
    }

    // Sinir kontrolleri
    if (can > 100) can = 100;
    if (tokluk > 100) tokluk = 100;
    if (uyku > 100) uyku = 100;
    if (hijyen > 100) hijyen = 100;

    if (can <= 0) {
        printf("\n===== Caninin kiymetini bilmeliydin... Canin: %d ===== \n", can);
        printf("\n===== Her yolun bir sonu vardir... Seninki de buraya kadardi ===== \n");
        exit(0);
    }
}

// Gelismis savas sistemi
void savas_sistemi(int zorluk) {
    int dusman_guc, dusman_ceviklik, dusman_dayaniklilik;
    int savas_devam = 1;

    // Dusman ozelliklerini zorluğa gore ayarla
    switch(zorluk) {
        case 1: // Kolay
            dusman_guc = rand() % 3 + 1;
            dusman_ceviklik = rand() % 3 + 1;
            dusman_dayaniklilik = rand() % 3 + 1;
            break;
        case 2: // Orta
            dusman_guc = rand() % 6 + 4;
            dusman_ceviklik = rand() % 6 + 4;
            dusman_dayaniklilik = rand() % 6 + 4;
            break;
        case 3: // Zor
            dusman_guc = rand() % 10 + 7;
            dusman_ceviklik = rand() % 10 + 7;
            dusman_dayaniklilik = rand() % 10 + 7;
            break;
    }

    printf("\n=== SAVAS BASLADI ===\n");
    printf("Dusman Ozellikleri - Guc: %d, Ceviklik: %d, Dayaniklilik: %d\n",
           dusman_guc, dusman_ceviklik, dusman_dayaniklilik);

    // Kacma sansi kontrolu
    int kacis_sansi = (4 * ceviklik) / 100;
    int kacan_taraf = (ceviklik > dusman_ceviklik) ? 0 : 1;

    printf("Kacmak isterseniz (Kacma sansiniz: %d%%): \n", kacis_sansi * 100);
    printf("1. Kac\n2. Savas\n");

    int secim;
    scanf("%d", &secim);

    if (secim == 1) {
        int kacis = rand() % 100 < (kacis_sansi * 100);
        if (kacis) {
            printf("Basariyla kactiniz!\n");
            return;
        } else {
            printf("Kacamadiniz! Savas basliyor!\n");
        }
    }

    // Savas dongusu
    while (savas_devam && can > 0 && dusman_dayaniklilik > 0) {
        // Kim saldiracak kontrolu
        int saldiran = (ceviklik > dusman_ceviklik) ? 0 :
                       (ceviklik < dusman_ceviklik) ? 1 :
                       rand() % 2;

        if (saldiran == 0) {  // Ozan saldiriyor
            int verilen_hasar = 4 * guc;
            int alinan_hasar = verilen_hasar - (verilen_hasar * (4 * dusman_dayaniklilik / 100 - 1));
            dusman_dayaniklilik -= alinan_hasar;
            printf("Ozanin saldirisi! Dusmana %d hasar verildi.\n", alinan_hasar);
        } else {  // Dusman saldiriyor
            int verilen_hasar = 4 * dusman_guc;
            int alinan_hasar = verilen_hasar - (verilen_hasar * (4 * dayaniklilik / 100 - 1));
            can -= alinan_hasar;
            printf("Dusmanin saldirisi! Ozana %d hasar verildi.\n", alinan_hasar);
        }

        // Savas durumu kontrolu
        if (can <= 0 || dusman_dayaniklilik <= 0) {
            savas_devam = 0;
        }
    }

    // Savas sonucu
    if (can > 0 && dusman_dayaniklilik <= 0) {
        printf("Dusmani yendiniz!\n");
        // Altin kazanimi zorluk seviyesine bağli
        switch(zorluk) {
            case 1: altin += rand() % 11 + 15; break;
            case 2: altin += rand() % 21 + 30; break;
            case 3: altin += rand() % 21 + 55; break;
        }
    } else {
        printf("Savasi kaybettiniz!\n");
    }

    kontrol_nitelikler();
}

int main() {
    srand(time(NULL));

    printf("Ozanin adini giriniz: ");
    scanf("%49s", ozan_adi);
    printf("Ozanin kullandigi calgiyi giriniz: ");
    scanf("%49s", calgi);

    while (1) {
        menu();
        kontrol_nitelikler();
    }

    return 0;
}

void menu() {
    int secim;
    printf("\n===== ANA MENU =====\n");
    printf("1. Kamp alanina git\n");
    printf("2. Sifahane\n");
    printf("3. Han\n");
    printf("4. Maceraya atil\n");
    printf("5. Seviye atla\n");
    printf("6. Durumu goster\n");
    printf("7. Oyundan cik\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1: kamp_alani(); break;
        case 2: sifahane(); break;
        case 3: han(); break;
        case 4: macera(); break;
        case 5: seviye_atla(); break;
        case 6: durumu_goster(); break;
        case 7:
            printf("Oyundan cikmak istediginizden emin misiniz? (1: Evet, 0: Hayir): ");
            int cikis;
            scanf("%d", &cikis);
            if (cikis == 1) exit(0);
            break;
        default: printf("Gecersiz secim!\n");
    }
}

void kamp_alani() {
    int secim;
    printf("\n== Kamp Alani ==\n");
    printf("1. Kamp atesinde calgi cal\n");
    printf("2. Nehirde yikan\n");
    printf("3. Cadira gir ve uyu\n");
    printf("4. Koy meydanina don\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            tokluk -= 5;
            hijyen += 5;
            karizma += 1;
            break;
        case 2:
            hijyen += 10;
            break;
        case 3:
            uyku += 20;
            tokluk -= 10;
            break;
        case 4:
            printf("Koy meydanina donuluyor \n");
            break;
        default:
            printf("Gecersiz secim!\n");
    }
}

void sifahane() {
    int secim;
    printf("\n== Sifahane ==\n");
    printf("1. Sifacidan yaralari sar (Can +20)\n");
    printf("2. Sifacidan merhem yap (Hijyen +15)\n");
    printf("3. Koy meydanina don\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            can += 20;
            altin -= 5;
            tokluk -= 5;
            printf("Yaralarin sarildi. Can 20 artti, Tokluk 5 azaldi, Altin 5 azaldi")
            break;
        case 2:
            can += 5;
            hijyen += 15;
            altin -= 3;
            tokluk -= 5;
            printf("Merhem yapildi. Can 5 artti, Tokluk 5 azaldi, Hijyen 15 artti, Altin 3 azaldi")
            break;
        case 3:
            printf("Koy meydanina donuluyor \n");
            break;
        default:
            printf("Gecersiz secim!\n");
    }
}

void han() {
    int secim;
    printf("\n== Han ==\n");
    printf("1. Yemek ye\n");
    printf("2. Icecek al\n");
    printf("3. Sarki soyle\n");
    printf("4. Koy meydanina don\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            tokluk += 20;
            altin -= 5;
            break;
        case 2:
            tokluk += 10;
            hijyen -= 5;
            altin -= 3;
            break;
        case 3:
            if (hijyen > 20) {
                int kazanilan_altin = 10 + (karizma * hijyen / 100);
                altin += kazanilan_altin;
                tecrube += 20;
            } else {
                printf("Hijyeniz cok dusuk, performans yapamazsiniz.\n");
            }
            break;
        case 4:
            printf("Koy meydanina donuluyor \n");
            break;
        default:
            printf("Gecersiz secim!\n");
    }
}

void macera() {
    int secim;
    printf("\n== Macera ==\n");
    printf("1. Kolay kesif\n");
    printf("2. Orta kesif\n");
    printf("3. Zor kesif\n");
    printf("4. Koy meydanina don\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            savas_sistemi(1);
            tecrube += 30;
            break;
        case 2:
            savas_sistemi(2);
            tecrube += 60;
            break;
        case 3:
            savas_sistemi(3);
            tecrube += 90;
            break;
        case 4:
            printf("Koy meydanina donuluyor \n");
            break;
        default:
            printf("Gecersiz secim!\n");
    }
}

void seviye_atla() {
    if (tecrube >= 100) {
        seviye++;
        tecrube = 0;
        printf("\nSeviye atladiniz! Yeni seviyeniz: %d\n", seviye);
        printf("Gelistirebileceğiniz ozellikler:\n");
        printf("1. Guc\n2. Ceviklik\n3. Dayaniklilik\n4. Karizma\n5. Toplayicilik\n");

        int puan = 5;
        while (puan > 0) {
            int secim, eklenecek_puan;
            printf("Kalan gelistirme puaniniz: %d\n", puan);
            printf("Hangi ozelliği gelistirmek istersiniz? (0 cikis): ");
            scanf("%d", &secim);

            if (secim == 0) break;

            printf("Kac puan eklemek istersiniz? ");
            scanf("%d", &eklenecek_puan);

            if (eklenecek_puan > puan) {
                printf("Yeterli puan yok!\n");
                continue;
            }

            switch(secim) {
                case 1: guc += eklenecek_puan; break;
                case 2: ceviklik += eklenecek_puan; break;
                case 3: dayaniklilik += eklenecek_puan; break;
                case 4: karizma += eklenecek_puan; break;
                case 5: toplayicilik += eklenecek_puan; break;
                default: printf("Gecersiz secim!\n");
            }

            puan -= eklenecek_puan;
        }
    } else {
        printf("Seviye atlamak icin yeterli tecrube puaniniz yok!\n");
    }
}

void durumu_goster() {
    printf("\n=== Ozanin Durumu ===\n");
    printf("Adi: %s\n", ozan_adi);
    printf("Calgisi: %s\n", calgi);
    printf("Can: %d\n", can);
    printf("Tokluk: %d\n", tokluk);
    printf("Uyku: %d\n", uyku);
    printf("Hijyen: %d\n", hijyen);
    printf("Altin: %d\n", altin);
    printf("Guc: %d\n", guc);
    printf("Ceviklik: %d\n", ceviklik);
}
