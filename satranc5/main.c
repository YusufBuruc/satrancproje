#include <stdio.h>
#include "fkutuphane.h"

int oyunsonu = 0;







int main() {

    int satir, sutun;            //Oynanacak taşın konumunu almak için oluşturulan değişkenler
    int Osatir, Osutun;          //Oynanacak konumu kullanıcıdan almak için oluşturulan değişkenler
    int sira = 0;              // sırayı belirlemek için oluşturulan değişken
    char tercih;

    BASLA :
    if (sira == 0) {
        tahtayiGoster(); //tahtayı ekrana vericek fonksiyon
        printf("Sira Buyuk Taslarda\n");
        TEKRAR:
        printf("oynamak istediginiz tasin konumunu girin:\n");
        scanf("%d %d", &satir, &sutun);
        if (board[satir][sutun] == 'P' || board[satir][sutun] == 'R' || board[satir][sutun] == 'N' ||   //Büyük taş seçildi mi seçilmedi mi kontrol eder
            board[satir][sutun] == 'K' || board[satir][sutun] == 'Q' || board[satir][sutun] == 'B') {

            validMoves(satir, sutun);//mevcut hamleler gösterilir
            if(oyunsonu == 1)
                return 0;
            printf("Bu tasi oynamak istiyor musunuz?\n"
                   "1-Evet\n"
                   "2-Hayir\n");
            scanf("%d", &tercih);
            if (tercih == 1) {
                printf("tasi oynamak istediginiz konumu yazin:\n");
                scanf("%d %d", &Osatir, &Osutun);
                if (board[Osatir][Osutun] == '*' || board2[Osatir][Osutun] == '/') {
                    if(board[Osatir][Osutun] == 'k'){
                        printf("Oyun Bitti.Zafer Büyüklerin\n");
                        return 0;
                    }
                    tasiOyna(satir, sutun, Osatir, Osutun);
                    sira = 1;
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
                goto TEKRAR;
            }
        } else {                                //Büyük Taş Seçilmezse Uyarır
            printf("Lutfen Buyuk Tas Secin!\n");
            goto BASLA;
        }
    }
    else{                            // Eger sira == 0 değilse yani sıra küçüklerdeyse burası çalışır
        tahtayiGoster();            //tahtayı ekrana vericek fonksiyon
        printf("Sira Kucuk Taslarda\n");
        printf("oynamak istediginiz tasin konumunu girin:\n");
        scanf("%d %d", &satir, &sutun);
        if (board[satir][sutun] == 'p' || board[satir][sutun] == 'r' || board[satir][sutun] == 'n' ||   //Küçük taş seçildi mi diye kontrol
            board[satir][sutun] == 'k' || board[satir][sutun] == 'q' || board[satir][sutun] == 'b') {

            validMoves(satir, sutun);  //mevcut hamleler gösterilir
            printf("Bu tasi oynamak istiyor musunuz?\n"
                   "1-Evet\n"
                   "2-Hayir\n");
            scanf("%d", &tercih);
            if (tercih == 1) {      //Kullanıcı taşı oynamak isterse aşağıdaki kod çalışacak
                printf("tasi oynamak istediginiz konumu yazin:\n");
                scanf("%d %d", &Osatir, &Osutun);
                if (board[Osatir][Osutun] == '*' || board2[Osatir][Osutun] == '/') {//Hamle geçerli mi kontrol edilir
                    if(board[Osatir][Osutun] == 'K'){
                        printf("Oyun Bitti.Zafer Kücüklerin\n");
                        return 0;}
                    tasiOyna(satir, sutun, Osatir, Osutun);                          //Geçerliyse oynar
                    sira = 0;                                                        //Sırayı büyüklere devreder
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
        else {        //Büyük taş seçilmezse burası çalışır.
            printf("Lutfen Buyuk Tas Secin!\n");    //Sira hala küçüklerde!
            goto BASLA;
        }


    }
}
















