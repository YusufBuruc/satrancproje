#include <stdio.h>
#include "fkutuphane.h"

int main() {

    s1.sira = 0;         //Sıranın kimde olduğunu belirten değişken. Küçükler:1  Büyükler:0
    BASLA:
    if (s1.sira == 0) {
        tahtayiGoster(); //tahtayı ekrana vericek fonksiyon
        printf("Sira Buyuk Taslarda\n");
        printf("oynamak istediginiz tasin satir ve sutununu girin:\n");
        scanf("%d %d", &s1.satir, &s1.sutun);
        if (tahta[s1.satir][s1.sutun] == 'P' || tahta[s1.satir][s1.sutun] == 'K' || tahta[s1.satir][s1.sutun] == 'A' ||   //Büyük taş seçildi mi seçilmedi mi kontrol eder
            tahta[s1.satir][s1.sutun] == 'S' || tahta[s1.satir][s1.sutun] == 'V' || tahta[s1.satir][s1.sutun] == 'F') {

            gecerliHamleler(s1.satir, s1.sutun);  //mevcut hamleler gösterilir

            printf("Bu tasi oynamak istiyor musunuz?\n"
                   "1-Evet\n"
                   "2-Hayir\n");
            scanf("%d", &s1.tercih);
            if (s1.tercih == 1) {
                printf("tasi oynamak istediginiz konumu yazin:\n");
                scanf("%d %d", &s2.satir, &s2.sutun);

                if (tahta[s2.satir][s2.sutun] == '*' || tahta2[s2.satir][s2.sutun] == '/') {
                    if(tahta[s2.satir][s2.sutun] == 's'){
                        printf("Oyun Bitti.Zafer Buyuklerin\n");
                        return 0;
                    }
                    tasiOyna(s1.satir, s1.sutun, s2.satir, s2.sutun);
                    s1.sira = 1;
                    goto BASLA;
                }
                else {
                    printf("Yanlis hamle!\n");
                    tahtayiDuzelt();
                    goto BASLA;
                }
            }
            else {
                tahtayiDuzelt();
                goto BASLA;
            }
        } else {                                //Büyük Taş Seçilmezse Uyarır
            printf("Lutfen Buyuk Tas Secin!\n");
            goto BASLA;
        }
    }
    else{                            // Eger s1.sira == 0 değilse yani sıra küçüklerdeyse burası çalışır
        tahtayiGoster();            //tahtayı ekrana vericek fonksiyon
        printf("Sira Kucuk Taslarda\n");
        printf("oynamak istediginiz tasin satir ve sutununu girin:\n");
        scanf("%d %d", &s1.satir, &s1.sutun);
        if (tahta[s1.satir][s1.sutun] == 'p' || tahta[s1.satir][s1.sutun] == 'k' || tahta[s1.satir][s1.sutun] == 'a' ||   //Küçük taş seçildi mi diye kontrol
            tahta[s1.satir][s1.sutun] == 's' || tahta[s1.satir][s1.sutun] == 'v' || tahta[s1.satir][s1.sutun] == 'f') {
            gecerliHamleler(s1.satir, s1.sutun);  //mevcut hamleler gösterilir
            printf("Bu tasi oynamak istiyor musunuz?\n"
                   "1-Evet\n"
                   "2-Hayir\n");
            scanf("%d", &s1.tercih);
            if (s1.tercih == 1) {      //Kullanıcı taşı oynamak isterse aşağıdaki kod çalışacak
                printf("tasi oynamak istediginiz konumu yazin:\n");
                scanf("%d %d", &s2.satir, &s2.sutun);
                if (tahta[s2.satir][s2.sutun] == '*' || tahta2[s2.satir][s2.sutun] == '/') {//Hamle geçerli mi kontrol edilir
                    tasiOyna(s1.satir, s1.sutun, s2.satir, s2.sutun);                          //Geçerliyse oynar
                    s1.sira = 0;
                    if(tahta[s2.satir][s2.sutun] == 'S'){
                        printf("Oyun Bitti.Zafer Kucuklerin\n");
                        return 0;}
                                                                            //Sırayı büyüklere devreder
                    goto BASLA;                                                      //Başa döner
                }
                else {                                           //Hamle geçersizse en başa döner.Sıra yine küçüklerde
                    printf("Yanlis hamle!\n");
                    tahtayiDuzelt();
                    goto BASLA;
                }

            } else {    //Kullanıcı taşı oynamak istemezse burası çalışır.
                tahtayiDuzelt();        //tahta eski haline döner (Oynanabilecek hamleleri göstermek için '*' lar yerleştirilmişti)
                goto BASLA;             //Başa döner. Sıra hala küçüklerde
            }
        }
        else {        //Küçük taş seçilmezse burası çalışır.
            printf("Lutfen Kucuk Tas Secin!\n");    //Sira hala küçüklerde!
            goto BASLA;
        }
    }
}