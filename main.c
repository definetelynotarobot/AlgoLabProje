#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global variables for character attributes
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
void yeni_macera();
void egitim_merkezi();
void ozellik_gelistir();
void temizle() {
    printf("\033[H\033[J"); // Clear screen (ANSI escape code)
}

int main() {
    char ozan_adi[50], calgi[50];

    // Oyun baslangici
    srand(time(NULL)); // Random seed
    printf("Ozanin adini giriniz: ");
    scanf("%49s", ozan_adi);
    printf("Ozanin kullandigi calgiyi giriniz: ");
    scanf("%49s", calgi);

    while (1 && can > 0) {
        menu();

    }
    if(can <= 0){
        printf("\n ===== Caninin kiymetini bilmeliydin... canin: %d ===== \n ", can);
        printf("\n ===== Her yolun bir sonu vardir... Seninki de buraya kadardi===== \n");
    }
    return 0;
}

void menu() {
    int secim;
    printf("\n===== ANA MENU =====\n");
    printf("1. Kamp alanina git \n");
    printf("2. Sifahane \n");
    printf("3. Han \n");
    printf("4. Maceraya atil (Altin ve Tecrube kazanabilirsiniz)\n");
    printf("5. Seviye atla\n");
    printf("6. Durumu goster\n");
    printf("7. Yeni macera\n");
    printf("8. Egitim merkezine git\n");
    printf("9. Oyundan cik\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);



    switch (secim) {
        case 1:
            kamp_alani();
            break;
        case 2:
            sifahane();
            break;
        case 3:
            han();
            break;
        case 4:
            macera();
            break;
        case 5:
            seviye_atla();
            break;
        case 6:
            durumu_goster();
            break;
        case 7:
            yeni_macera();
            break;
        case 8:
            egitim_merkezi();
            break;
        case 9:
            printf("Oyundan cikiliyor...\n");
            exit(0);
        default:
            printf("Gecersiz secim!\n");
    }
}

void kamp_alani() {
    int secim;
    printf("\n== Kamp Alani ==\n");
    printf("1. Kamp atesinde calgi cal (Tokluk -5, Hijyen +5)\n");
    printf("2. Nehirde yikan (Hijyen +10)\n");
    printf("3. Cadira gir ve uyu (Uyku +20, Tokluk -10)\n");
    printf("4. Koy meydanina don\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            printf("Calgi caliyorsunuz. Tokluk azalir, hijyen artar.\n");
            tokluk -= 5;
            hijyen += 5;
            break;
        case 2:
            printf("Nehirde yikaniyorsunuz. Hijyen artar.\n");
            hijyen += 10;
            break;
        case 3:
            printf("Uyuyorsunuz. Uyku artar, tokluk azalir.\n");
            uyku += 20;
            tokluk -= 10;
            break;
        case 4:
            printf("Koy meydanina donuyorsunuz.\n");
            break;
        default:
            printf("Gecersiz secim!\n");
    }
}

void sifahane() {
    int secim;
    printf("\n== Sifahane ==\n");
    printf("1. Yaralarinizi sarmak icin sifaciya gidin (Can +20)\n");
    printf("2. Merhem yapmasini isteyin (Hijyen +15)\n");
    printf("3. Koy meydanina don\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            printf("Sifaci yaralarinizi sardı. Can artiyor.\n");
            can += 20;
            break;
        case 2:
            printf("Merhem yapildi ve uygulandi. Hijyen artiyor.\n");
            hijyen += 15;
            break;
        case 3:
            printf("Koy meydanina donuyorsunuz.\n");
            break;
        default:
            printf("Gecersiz secim!\n");
    }
}

void han() {
    int secim;
    printf("\n== Han ==\n");
    printf("1. Yiyecek satin alin ve yiyin (Tokluk +20, Altin -5)\n");
    printf("2. Icecek satin alin ve icin (Tokluk +10, Hijyen -5, Altin -3)\n");
    printf("3. Enstruman calin ve sarki soyleyin (Altin +15, Tecrube +20, Hijyen > 20 gerek)\n");
    printf("4. Koy meydanina don\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            printf("Yiyecek yediniz. Tokluk artiyor.\n");
            tokluk += 20;
            altin -= 5;
            break;
        case 2:
            printf("Icecek ictiniz. Hijyen azalir ama tokluk artar.\n");
            tokluk += 10;
            hijyen -= 5;
            altin -= 3;
            break;
        case 3:
            if (hijyen > 20) {
                printf("Sarki soylediniz. Altin kazandiniz!\n");
                altin += 15;
                tecrube += 20;
            } else {
                printf("Hijyeniniz cok dusuk, performans yapamazsiniz.\n");
            }
            break;
        case 4:
            printf("Koy meydanina donuyorsunuz.\n");
            break;
        default:
            printf("Gecersiz secim!\n");
    }
}

void macera() {
    int secim;
    printf("\n== Macera ==\n");
    printf("1. Kolay kesif (Altin +15, Tecrube +30)\n");
    printf("2. Orta kesif (Altin +30, Tecrube +60)\n");
    printf("3. Zor kesif (Altin +50, Tecrube +90)\n");
    printf("4. Koy meydanina don\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            printf("Kolay kesif yaptiniz. Biraz altin kazandiniz.\n");
            altin += 15;
            tecrube += 30;
            hijyen -= 5;
            can -= 15;
            break;
        case 2:
            printf("Orta kesif yaptiniz. Daha fazla altin kazandiniz.\n");
            altin += 30;
            tecrube += 60;
            hijyen -= 20;
            can -= 30;
            break;
        case 3:
            printf("Zor kesif yaptiniz. Buyuk bir ganimet kazandiniz!\n");
            altin += 50;
            tecrube += 90;
            hijyen -= 30;
            can -= 50;
            break;
        case 4:
            printf("Koy meydanina donuyorsunuz.\n");
            break;
        default:
            printf("Gecersiz secim!\n");
    }
}

void yeni_macera() {
    printf("\n== Yeni Macera ==\n");
    printf("Bu bolum yeni maceralar eklemeniz icin yaratildi!\n");
    printf("Gelismeler yakinda...\n");
}

void egitim_merkezi() {
    printf("\n== Egitim Merkezi ==\n");
    printf("Burada becerilerinizi gelistirebilirsiniz.\n");
    printf("Seviye artisi icin calismalara baslayin!\n");
}

void seviye_atla() {
    if (tecrube >= 100) {
        printf("\nTebrikler! Seviye atladiniz. Yeni seviyeniz: %d\n", ++seviye);
        tecrube = 0;
        guc += 1;
        ceviklik += 1;
        dayaniklilik += 1;
        karizma += 1;
        toplayicilik += 1;
    } else {
        printf("Tecrube puaniniz yeterli degil. Daha fazla macera lazim!\n");
    }
}

void durumu_goster() {
    printf("\n=== Ozanin Durumu ===\n");
    printf("Can: %d\n", can);
    printf("Tokluk: %d\n", tokluk);
    printf("Uyku: %d\n", uyku);
    printf("Hijyen: %d\n", hijyen);
    printf("Altin: %d\n", altin);
    printf("Guc: %d\n", guc);
    printf("Ceviklik: %d\n", ceviklik);
    printf("Dayaniklilik: %d\n", dayaniklilik);
    printf("Karizma: %d\n", karizma);
    printf("Toplayicilik: %d\n", toplayicilik);
    printf("Seviye: %d\n", seviye);
    printf("Tecrube: %d\n", tecrube);
}

