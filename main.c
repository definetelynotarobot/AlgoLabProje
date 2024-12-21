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
void toplayicilik_yap();
void egitim_al();
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
    int dusman_guc, dusman_ceviklik, dusman_baslangic_dayaniklilik, dusman_dayaniklilik;
    int ozan_baslangic_can, savas_devam = 1;
    int kazanilan_tecrube = 0;
    int kazanilan_altin = 0;
    int tur = 1;
    char *dusman_ismi;

    // Düşman özelliklerini zorluga gore ayarla
    switch(zorluk) {
        case 1: // Kolay
            dusman_guc = rand() % 3 + 1;
            dusman_ceviklik = rand() % 3 + 1;
            dusman_baslangic_dayaniklilik = rand() % 30 + 20;
            dusman_ismi = "Cirak Tarikat Uyesi";
            break;
        case 2: // Orta
            dusman_guc = rand() % 6 + 4;
            dusman_ceviklik = rand() % 6 + 4;
            dusman_baslangic_dayaniklilik = rand() % 50 + 40;
            dusman_ismi = "Tarikat Savascisi";
            break;
        case 3: // Zor
            dusman_guc = rand() % 10 + 7;
            dusman_ceviklik = rand() % 10 + 7;
            dusman_baslangic_dayaniklilik = rand() % 70 + 60;
            dusman_ismi = "Tarikat Komutani";
            break;
        case 4: // Final Savaşı
            printf("\n=== SUSKUNLUK TARIKATI LIDERI ILE KARSI KARSIYASINIZ! ===\n");
            printf("Lider: 'Demek sen, muzigin son koruyucususun... Ustani kurtarmaya mi geldin?\n");
            printf("Cok yazik, artik cok gec. Dunya sonsuza dek sessizlige gomulecek!'\n\n");
            
            dusman_guc = 15;
            dusman_ceviklik = 15;
            dusman_baslangic_dayaniklilik = 150;
            dusman_ismi = "Suskunluk Tarikati Lideri";
            
            // Final savaşı için özel güçlendirme
            can = 100; // Canı yenile
            printf("Ustanizin ruhu size guc veriyor! Caniniz yenilendi!\n");
            break;
    }

    // Baslangic degerlerini kopyala
    dusman_dayaniklilik = dusman_baslangic_dayaniklilik;
    ozan_baslangic_can = can;

    printf("\n=== SAVAS BASLIYOR ===\n");
    printf("Dusman: %s\n", dusman_ismi);
    printf("Dusman Ozellikleri - Guc: %d, Ceviklik: %d, Dayaniklilik: %d\n",
           dusman_guc, dusman_ceviklik, dusman_dayaniklilik);

    // Savas dongusu
    while (savas_devam && can > 0 && dusman_dayaniklilik > 0) {
        printf("\n--- %d. TUR ---\n", tur);
        printf("%s'nin Cani: %d | %s'nin Dayanikliligi: %d\n", 
               ozan_adi, can, dusman_ismi, dusman_dayaniklilik);

        // Final savaşı için özel mekanikler
        if (zorluk == 4 && tur % 3 == 0) {
            printf("\nLider ozel saldiri kullaniyor: 'SESSIZLIGIN CIGLIGI!'\n");
            int ozel_hasar = rand() % 20 + 15;
            can -= ozel_hasar;
            printf("Ozel saldiri %d hasar verdi!\n", ozel_hasar);
            if (can < 0) can = 0;
        }

        // Kacma secenegi (final savaşta kaçış yok)
        printf("Secenekler:\n");
        printf("1. Saldir\n");
        if (zorluk != 4) {
            printf("2. Kacmayi Dene (Kacis Sansi: %d%%)\n", (4 * ceviklik));
        }

        int secim;
        scanf("%d", &secim);

        if (secim == 2 && zorluk != 4) {
            int kacis_sansi = (4 * ceviklik);
            if (rand() % 100 < kacis_sansi) {
                printf("Savastan basariyla kactin!\n");
                hijyen -= 10;
                return;
            } else {
                printf("Kacis basarisiz oldu! Dusman saldiriyor!\n");
            }
        }

        // Ozan saldiriyor
        int ozan_hasar = rand() % (4 * guc) + 1;
        if (zorluk == 4) {  // Final savaşta müzik güçlendirmesi
            ozan_hasar = ozan_hasar * (1 + (karizma / 10));
            printf("\n%s %s ile guclu bir ezgi caliyor!\n", ozan_adi, calgi);
        }
        
        int ozan_vurusunun_etkinligi = 100 - (4 * dusman_ceviklik);
        if (ozan_vurusunun_etkinligi < 20) ozan_vurusunun_etkinligi = 20;

        int alinan_dusman_hasari = (ozan_hasar * ozan_vurusunun_etkinligi) / 100;
        dusman_dayaniklilik -= alinan_dusman_hasari;

        if (dusman_dayaniklilik < 0) dusman_dayaniklilik = 0;

        printf("%s'nin saldirisi! %s'ye %d hasar verildi (Vurusun etkinligi: %d%%)\n",
               ozan_adi, dusman_ismi, alinan_dusman_hasari, ozan_vurusunun_etkinligi);

        // Dusman saldiriyor
        if (dusman_dayaniklilik > 0) {
            int dusman_hasar = rand() % (4 * dusman_guc) + 1;
            int dusman_vurusunun_etkinligi = 100 - (4 * dayaniklilik);
            if (dusman_vurusunun_etkinligi < 20) dusman_vurusunun_etkinligi = 20;

            int alinan_ozan_hasari = (dusman_hasar * dusman_vurusunun_etkinligi) / 100;
            can -= alinan_ozan_hasari;
            hijyen -= 5;

            if (can < 0) can = 0;

            printf("%s'nin saldirisi! %s'na %d hasar verildi (Vurusun etkinligi: %d%%)\n",
                   dusman_ismi, ozan_adi, alinan_ozan_hasari, dusman_vurusunun_etkinligi);
        }

        printf("%s - Can: %d | %s - Dayaniklilik: %d\n",
               ozan_adi, can, dusman_ismi, dusman_dayaniklilik);

        if (can == 0 || dusman_dayaniklilik == 0) {
            savas_devam = 0;
        }

        tur++;
    }

    // Savas sonucu
    if (can > 0 && dusman_dayaniklilik == 0) {
        printf("\n=== ZAFER! ===\n");

        if (zorluk == 4) {
            printf("\nSuskunluk Tarikati Lideri yenilgiyle yere yigiliyor...\n");
            printf("'Imkansiz... Muzik... Bu kadar guclu olamaz...'\n\n");
            printf("Ustanizi zindandan kurtariyorsunuz. Dunya yeniden muzikle dolacak!\n");
            printf("\n=== TEBRIKLER! OYUNU TAMAMLADINIZ! ===\n");
            // Final savaşı ödülleri
            kazanilan_altin = 200;
            kazanilan_tecrube = 500;
        } else {
            switch(zorluk) {
                case 1:
                    kazanilan_altin = rand() % 11 + 15;
                    kazanilan_tecrube = 30;
                    break;
                case 2:
                    kazanilan_altin = rand() % 21 + 30;
                    kazanilan_tecrube = 60;
                    break;
                case 3:
                    kazanilan_altin = rand() % 21 + 55;
                    kazanilan_tecrube = 90;
                    break;
            }
        }

        printf("Kazanilan Altin: %d\n", kazanilan_altin);
        printf("Kazanilan Tecrube: %d\n", kazanilan_tecrube);

        altin += kazanilan_altin;
        tecrube += kazanilan_tecrube;
    } else {
        printf("\n=== YENILGI! ===\n");
        if (zorluk == 4) {
            printf("\nSuskunluk Tarikati Lideri zafer cigligi atiyor:\n");
            printf("'Sonunda! Muzigin son koruyucusu da dustu! Artik kimse bizi durduramaz!'\n");
        }
        printf("\nSavasi kaybettiniz...\n");
    }

    kontrol_nitelikler();
}

int main() {
    srand(time(NULL));

    printf("Ozanin adini giriniz: ");
    scanf("%49s", ozan_adi);
    printf("Ozanin kullandigi calgiyi giriniz: ");
    scanf("%49s", calgi);
    printf("\n=== EZGI KORUYUCULARI'NIN HIKAYESI ===\n");
    printf("Efsaneye gore, cok eski zamanlarda 'Ulu Ozan' olarak bilinen bir bilge yasarmis.\n");
    printf("Bu ozan, muzigin sadece kulaga hos gelen melodilerden ibaret olmadigini,\n");
    printf("ayni zamanda doganin ve evrenin gizemli guclerini kontrol edebilen kadim bir sanat oldugunu kesfetmis.\n");
    printf("\nBir gece, ustadinizin cadiri gizemli karanlik yaratiklar tarafindan basildi ve ustadiniz kacirildi.\n");
    printf("Şimdi onu kurtarmak icin yola cikmalisiniz...\n");
    printf("\nEzgi Koruyuculari'nin kadim dusmani olan 'Suskunluk Tarikati',\n");
    printf("dunyadan tum muzigi ve sesi silmeye ant icmis karanlik bir orguttur.\n");
    printf("ustadinizi kurtarmak ve tarikati durdurmak sizin goreviniz!\n");
    printf("\n ENTER ile devam edin...\n");
    getchar();
    getchar();

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
    printf("5. Toplayicilik yap \n");
    printf("6. Egitim al \n");
    printf("7. Seviye atla\n");
    printf("8. Durumu goster\n");
    printf("9. Oyundan cik\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1: kamp_alani(); break;
        case 2: sifahane(); break;
        case 3: han(); break;
        case 4: macera(); break;
        case 5: toplayicilik_yap(); break;
        case 6: egitim_al(); break;
        case 7: seviye_atla(); break;
        case 8: durumu_goster(); break;
        case 9:
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
            karizma += 1;
            uyku -= 5;
            printf("Kamp atesinde calgi caldin!\n");
            printf("Tokluk 5 azaldi, Uyku 5 azaldi, Karizma 1 yukseldi\n");
            break;
        case 2:
            hijyen += 10;
            uyku -= 5;
            tokluk -= 5;
            printf("Nehirde yikandin!\n");
            printf("Hijyen 10 artti, Tokluk 5 azaldi,\n");
            break;
        case 3:
            uyku += 30;
            tokluk -= 10;
            printf("Cadirda uyudun!\n");
            printf("Uyku 30 artti, Tokluk 10 azaldi\n");
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
    printf("1. Sifacidan yaralarini sarmasini iste (Can +20 Altin -5)\n");
    printf("2. Sifacidan merhem yapmasini iste (Hijyen +15 Altin -3)\n");
    printf("3. Koy meydanina don\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            can += 20;
            altin -= 5;
            tokluk -= 5;
            printf("Yaralarin sarildi!\n");
            printf("Can 20 artti, Tokluk 5 azaldi, Altin 5 azaldi\n");
            break;
        case 2:
            can += 5;
            hijyen += 15;
            altin -= 3;
            tokluk -= 5;
            printf("Merhem yapildi!\n");
            printf("Can 5 artti, Hijyen 15 artti, Tokluk 5 azaldi, Altin 3 azaldi\n");
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
            uyku -= 5;
            printf("Yemek yenildi!\n");
            printf("Tokluk 20 artti, Uyku 5 azaldi, Altin 5 azaldi\n");
            break;
        case 2:
            tokluk += 10;
            hijyen -= 5;
            altin -= 3;
            uyku -= 5;
            printf("Icecek alindi!\n");
            printf("Tokluk 10 artti, Hijyen 5 azaldi, Uyku 5 azaldi, Altin 3 azaldi\n");
            break;
        case 3:
            if (hijyen > 20) {
                int kazanilan_altin = 10 + (karizma * hijyen / 100);
                altin += kazanilan_altin;
                tecrube += 20;
                hijyen -= 10;
                tokluk -= 5;
                uyku -= 10;
                printf("Sarkini soyledin!\n");
                printf("%d Altin ve  20 tecrube kazandin\n", kazanilan_altin);
                printf("Hijyen 10 azaldi, Tokluk 5 azaldi, Uyku 10 azaldi\n");
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
    printf("4. Son macera\n");
    printf("5. Koy meydanina don\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            savas_sistemi(1);
            tecrube += 30;
            uyku -= 10;
            tokluk -= 10;
            break;
        case 2:
            savas_sistemi(2);
            tecrube += 60;
            uyku -= 15;
            tokluk -= 15;
            break;
        case 3:
            savas_sistemi(3);
            tecrube += 90;
            uyku -= 20;
            tokluk -= 20;
            break;
        case 4:
            if (guc >= 10 && ceviklik >= 10 && dayaniklilik >= 10 && karizma >= 10) {
                printf("\n=== SUSKUNLUK TARİKATI'NIN SAKLANDIĞI KARTAL YUVASI'NA VARDINIZ ===\n");
                printf("Ustadinizi kurtarmak icin son savasa hazir olun!\n");
                savas_sistemi(4);
                if (can > 0) {
                    printf("\n=== MUTLU SON ===\n");
                    printf("Ustadinizi kurtardiniz! Suskunluk Tarikati'ni yendiniz!\n");
                    printf("Artik gercek bir Ezgi Koruyucususunuz...\n");
                    printf("Oyunu tamamladiginiz icin tesekkurler!\n");
                    exit(0);
                }
            } else {
                printf("Bu goreve hazir degilsiniz!\n");
                printf("Gereksinimler: Guc >= 10, Çeviklik >= 10, Dayaniklilik >= 10, Karizma >= 10\n");
            }
            break;
        case 5:
            printf("Koy meydanina donuluyor \n");
            break;
        default:
            printf("Gecersiz secim!\n");
    }
}
void toplayicilik_yap() {
    srand(time(NULL));
    int bulma_sansi = (toplayicilik * 4) / 100;
    int rastgele_sayi = rand() % 100 + 1;
    int secim;

    printf("\n=== Toplayicilik Yap ===\n");
    printf("1. Sifali bitki ara\n");
    printf("2. Meyve topla\n");
    printf("3. Koy meydanina don\n");
    printf("Seciminizi yapin: ");
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            printf("\nDogada sifali bitki ariyorsun...\n");
            if (rastgele_sayi <= bulma_sansi) {
                printf("Tebrikler! Sifali bir bitki buldun. Can artti!\n");
                printf("Can 10 artti, Tokluk 5 azaldi, Hijyen 5 azaldi, Uyku 5 azaldi\n");
                can += 10;
                tokluk -= 5;
                hijyen -= 5;
                uyku -= 5;
            } else {
                printf("Maalesef, bir sey bulamadin.\n");
                printf("Tokluk 5 azaldi, Hijyen 5 azaldi, Uyku 5 azaldi\n");
                tokluk -= 5;
                hijyen -= 5;
                uyku -= 5;
            }
            break;

        case 2:
            printf("\nDogada meyve topluyorsun...\n");
            if (rastgele_sayi <= bulma_sansi) {
                printf("Tebrikler! Taze meyve buldun. Tokluk artti!\n");
                tokluk += 10; // Meyve bulunca tokluk artar
                hijyen -= 5;
                uyku -= 5;
            } else {
                printf("Maalesef, bir sey bulamadin.\n");
                printf("Tokluk 5 azaldi, Hijyen 5 azaldi, Uyku 5 azaldi\n");
                tokluk -= 5;
                hijyen -= 5;
                uyku -= 5;
            }
            break;

        case 3:
            printf("Koy meydanina donuluyor \n");
            break;

        default:
            printf("Gecersiz secim! Toplayicilik iptal edildi.\n");
            break;
    }
}

void egitim_al() {
    int secim, maliyet;
    
    printf("\n=== EGITIM MERKEZI ===\n");
    printf("Mevcut Altininiz: %d\n", altin);
    printf("Egitim Secenekleri:\n");
    printf("1. Savas Egitimi (Maliyet: 35 Altin, Kazanim: +2 Guc)\n");
    printf("2. Hareket Egitimi (Maliyet: 30 Altin, Kazanim: +2 Ceviklik)\n");
    printf("3. Dayaniklilik Egitimi (Maliyet: 40 Altin, Kazanim: +2 Dayaniklilik)\n");
    printf("4. Karizma Egitimi (Maliyet: 35 Altin, Kazanim: +2 Karizma)\n");
    printf("5. Dogada Yasam Egitimi (Maliyet: 40 Altin, Kazanim: +2 Toplayicilik)\n");
    printf("6. Ana Menuye Don\n");
    printf("Seciminizi yapin: ");
    
    scanf("%d", &secim);
    
    switch(secim) {
        case 1:
            maliyet = 35;
            if (altin >= maliyet) {
                altin -= maliyet;
                guc += 2;
                tokluk -= 15;
                uyku -= 10;
                hijyen -= 10;
                
                printf("\nSavaş Egitimi Basariyla Tamamlandi!\n");
                printf("2 Guc puani kazandiniz.\n");
                printf("Fiziksel yorgunluk nedeniyle tokluk, uyku ve hijyen degerleriniz azaldi.\n");
            } else {
                printf("\nYeterli altininiz yok!\n");
            }
            break;
        
        case 2:
            maliyet = 30;
            if (altin >= maliyet) {
                altin -= maliyet;
                ceviklik += 2;
                tokluk -= 15;
                uyku -= 10;
                hijyen -= 10;
                
                printf("\nHareket Egitimi Basariyla Tamamlandi!\n");
                printf("2 Ceviklik puani kazandiniz.\n");
                printf("Fiziksel yorgunluk nedeniyle tokluk, uyku ve hijyen degerleriniz azaldi.\n");
            } else {
                printf("\nYeterli altininiz yok!\n");
            }
            break;
        
        case 3:
            maliyet = 40;
            if (altin >= maliyet) {
                altin -= maliyet;
                dayaniklilik += 2;
                tokluk -= 15;
                uyku -= 10;
                hijyen -= 10;
                
                printf("\nDayaniklilik Egitimi Basariyla Tamamlandi!\n");
                printf("2 Dayaniklilik puani kazandiniz.\n");
                printf("Fiziksel yorgunluk nedeniyle tokluk, uyku ve hijyen degerleriniz azaldi.\n");
            } else {
                printf("\nYeterli altininiz yok!\n");
            }
            break;
        
        case 4:
            maliyet = 35;
            if (altin >= maliyet) {
                altin -= maliyet;
                karizma += 2;
                tokluk -= 15;
                uyku -= 10;
                hijyen -= 10;
                
                printf("\nKarizma Egitimi Basariyla Tamamlandi!\n");
                printf("2 Karizma puani kazandiniz.\n");
                printf("Sosyal yorgunluk nedeniyle tokluk, uyku ve hijyen degerleriniz azaldi.\n");
            } else {
                printf("\nYeterli altininiz yok!\n");
            }
            break;
        
        case 5:
            maliyet = 40;
            if (altin >= maliyet) {
                altin -= maliyet;
                toplayicilik += 2;
                tokluk -= 15;
                uyku -= 10;
                hijyen -= 10;
                
                printf("\nDogada Yasam Egitimi Basariyla Tamamlandi!\n");
                printf("2 Toplayicilik puani kazandiniz.\n");
                printf("Fiziksel yorgunluk nedeniyle tokluk, uyku ve hijyen degerleriniz azaldi.\n");
            } else {
                printf("\nYeterli altininiz yok!\n");
            }
            break;
        
        case 6:
            return;
        
        default:
            printf("Gecersiz secim!\n");
    }
}

void seviye_atla() {
    if (tecrube >= 100) {
        seviye++;
        tecrube -= 100;
        printf("\n Seviye atladiniz! Yeni seviyeniz: %d\n", seviye);
        printf("Gelistirebileceginiz ozellikler:\n");
        printf("1. Guc\n2. Ceviklik\n3. Dayaniklilik\n4. Karizma\n5. Toplayicilik\n");

        int puan = 5;
        while (puan > 0) {
            int secim, eklenecek_puan;
            printf("Kalan gelistirme puaniniz: %d\n", puan);
            printf("Hangi ozelligi gelistirmek istersiniz? (0 cikis): ");
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
    printf("Dayaniklilik: %d\n", dayaniklilik);
    printf("Karizma: %d\n", karizma);
    printf("Toplayicilik: %d\n", toplayicilik);
    printf("Tecrube: %d\n", tecrube);

}