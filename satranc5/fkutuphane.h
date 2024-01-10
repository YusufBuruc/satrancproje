struct yapi{        // Taş hamleleri için oluşturulan yapi adlı bir struct.
    int satir, sutun;   // Oynanmak istenen taşın satır ve sütununu alabilmek için tanımlanan değişkenler.
    int sira ;          // Hamle sırasını belirlemek için oluşturulan değişken
    char tercih;        // Oynanmak istenilen taşın konumunu kullanıcıdan aldıktan sonra, o taşı oynamak isteyip istemediğini sorgulayan komut için kullanılan değişken.
};

struct yapi s1 ;      // Oynamak istenilen taşın bulunduğu satır ve sütun numaraları (konumu)
struct yapi s2 ;      // Seçilen taşın oynanmak istenildiği yerin bulunduğu satır ve sütun numaraları (konumu)
struct yapi kontrol ; // Taşın oynayabileceği hamleleri kontrol etmek için kullanıldı


char tahta[9][9] = {
        //Hamleler yapıldığında ekranda gözüken satranç tahtası.Geri çağırabilmek ve kullanabilmek için 9x9 lik bir diziyi fonksiyon şeklinde oluşturduk.
        {0,1,   2,    3,    4,   5,   6,  7,    8},
        {1,'k', 'a', 'f', 's', 'v', 'f', 'a', 'k'},
        {2,'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {3,'-', '-', '-', '-', '-', '-', '-', '-'},
        {4,'-', '-', '-', '-', '-', '-', '-', '-'},
        {5,'-', '-', '-', '-', '-', '-', '-', '-'},
        {6,'-', '-', '-', '-', '-', '-', '-', '-'},
        {7,'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {8,'K', 'A', 'F', 'S', 'V', 'F', 'A', 'K'}
};

/* Ekrana verilen tahtanın dışında, arka planda hamlelerin çalışması ve kontrol edilmesine yardımcı olan sanal satranç tahtası.
   Taşların nereye oynayabileceğini ve taş hareketleri için kullanılıyor. */
char tahta2[9][9] = {
        {0,1,   2,    3,    4,   5,   6,  7,    8},
        {1,'-', '-', '-', '-', '-', '-', '-', '-'},
        {2,'-', '-', '-', '-', '-', '-', '-', '-'},
        {3,'-', '-', '-', '-', '-', '-', '-', '-'},
        {4,'-', '-', '-', '-', '-', '-', '-', '-'},
        {5,'-', '-', '-', '-', '-', '-', '-', '-'},
        {6,'-', '-', '-', '-', '-', '-', '-', '-'},
        {7,'-', '-', '-', '-', '-', '-', '-', '-'},
        {8,'-', '-', '-', '-', '-', '-', '-', '-'}
};



FILE* Dosya;

/* Girilen satır sütundaki taşın geçerli hamle olarak oynayabileceği yerler * ile gösterilir.
tahtayiDuzelt fonksiyonu ekrandaki oynanabilen hamleler gösterildikten sonra tahta çıktısındaki "*" ları tekrar "-" karakterine dönüştüren bir fonksiyondur. */
void tahtayiDuzelt() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (tahta[i][j] == '*')
                tahta[i][j] = '-';
            tahta2[i][j] = '-' ;  // Sanal tahtadaki / işaretlerini - ye dönüştürür.
        }
    }
}
//tahtayiGoster fonksiyonu tahtayı ekrana verir ve son yapılan hamleyi belirtilen dosya içine işler.
void tahtayiGoster(){
    Dosya= fopen("C:\\Users\\Sinan\\Desktop\\satranç.txt","w");
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {       // for döngüsü kullanıp her bir satır için sütun sayısını artırarak tahtayı ekrana yazdırdık.
            if(i == 0) {                    // Örneğin 1. satırdaki 9 sütun sırasıyla yazıldıktan sonra bir alt satır olan 2. satıra geçer ve aynı işlemi yapar.
                // Böylelikle satır sayısı 9 olup 9. satırın da sütunları yazdırıldıktan sonra tahta ekrana yazdırılmış olur.
                fprintf(Dosya, "%d  ", tahta[i][j]);
                printf("%d  ", tahta[i][j]);
            }
            else if (j == 0) {
                fprintf(Dosya, "%d  ", tahta[i][j]);
                printf("%d  ", tahta[i][j]);
            }
            else {
                fprintf(Dosya, "%c  ", tahta[i][j]);
                printf("%c  ", tahta[i][j]);
            }
        }
        fprintf(Dosya,"\n");
        printf("\n");
    }
    fprintf(Dosya,"\n");
    printf("\n");
    if(s1.sira == 0)
        fprintf(Dosya,"Son Hamleyi Küçükler Yaptı.\n");
    else
        fprintf(Dosya,"Son Hamleyi Büyükler Yaptı.\n");

    fclose(Dosya);
}

void gecerliHamleler(int satir, int sutun) {
    switch (tahta[satir][sutun]) {           /* Switch komutu açıp her taşın durumuna göre case oluşturduk. Case'ler sayı olacağı için tek tırnak içinde
                                                ASCII tablosundaki karşılığına göre alınıyor. Aynı harflerde caseler olup fakat büyük küçük harf farkı
                                                olduğundan ASCII karşılıkları farklı çıkıyor ve bir karışıklık olmuyor.*/

        case 'P': {                          //Büyük piyonun oynayabileceği yerler için tutulan case.

            if (satir == 7) {                   /*Başlangıç konumu için piyonlar 1 ya da 2 hamle gidebilir. Bu özel durumda büyük piyonlar için başlangıç konumu
                                                 7. satır n. sütun olduğundan if komutu ile satır şartını kontrol ederek hamle yeteneğini koşulladık.*/
                for (int i = 1; i <3 ; ++i) {
                    if(tahta[satir - i][sutun] == '-')/* Büyük piyonun 7. satırdaki hamlelerini göstermek için kullanılan for döngüsü. Geçerli hamleleri
                                                         göstermek için oranın - olup olmadığını if koşuluyla kontrol eder.Tahtada geçerli hamle bölgelerine * koyar. */
                        tahta[satir - i][sutun] = '*' ;
                    else break;
                }
            } else if (tahta[satir - 1][sutun] == '-')  //Başlangıç konumunda(7. satır n. sütun) değilse yalnızca 1 ileri oynayabilir.
                tahta[satir - 1][sutun] = '*';

            if(tahta[satir - 1][sutun + 1] < 123 && tahta[satir - 1][sutun + 1] > 96) //eger sağ üst çaprazda küçük taş var ise tahta2 de oraya / işareti koy
                tahta2[satir - 1][sutun + 1] = '/' ;
            /* Büyük taşların küçük taşları yemesi, kendi taşlarını yememesi gerek. Bunun kontrolü için '' ifadesiyle taşların ASCII tablosundaki
               karşılığını koşul olarak aldık. Örneğin büyük piyonun taş yemesi için çapraz olarak -1 satır +1 sütun ya da -1 satır -1 sütun hamlesi
               yapması gerekir. Burda ASCII tablosunda 97 değerinde olan a ve 122 değerinde olan z için referans aldık ve buna bağlı bir koşul
               oluşturduk.*/
            if(tahta[satir - 1][sutun - 1] < 123 && tahta[satir - 1][sutun - 1] > 96) // İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.
                tahta2[satir - 1][sutun - 1] = '/' ;
            /* Bunu yapmamızın sebebi taşın hamle kabiliyetini satranç kurallarına göre kısıtlamaktır. Eğer oyuncular
            kendi taşını yemek isterse ikinci tahtada / işareti olmadığından kendi taşlarını yiyemez. Fakat diğer
            oyuncunun bir taşı varsa yemesi için / işareti koyulur. Bu sanal tahtada o taşı yiyebilirsin demektir.*/

            break;

        }

        case 'p':{      /*Küçük harf piyonun onayabileceği hamleler. Büyük piyona göre farkı küçük harfler tahtanın üst tarafında olduğu için satır sayısı
                          azalmak yerine artacaktır. */
            if (satir == 2) { //İlk hamle kontrolu yapılıyor.(Küçük piyonlar için ilk konum 2. satır n. sütun olduğu için 2. satır if koşulu ile kontrol edildi.
                for (int i = 1; i < 3; ++i) {
                    if(tahta[satir + i][sutun] == '-')
                        tahta[satir + i][sutun] = '*';
                    else break;
                }
            } else if (tahta[satir + 1][sutun] == '-')
                tahta[satir + 1][sutun] = '*';

            if(tahta[satir + 1][sutun + 1] < 91 && tahta[satir + 1][sutun + 1] > 64)
                /* Bu kez küçük taşları oynadığımız için
                 küçük taşların büyük taşları yemesi geçerli hamle olacağı için bu kez ASCII tablosuna göre büyük taşların referans noktası A(65)den Z(90)a
                 kadar alınır. */
                tahta2[satir + 1][sutun + 1] = '/' ; //İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.
            if(tahta[satir + 1][sutun - 1] < 91 && tahta[satir + 1][sutun - 1] > 64) /* Eğer piyon bir taşı yiyebilicek pozisyondaysa ve orada (sol alt çapraz)
                büyük taş var ise tahta2 de oraya / işareti koy */
                tahta2[satir + 1][sutun - 1] = '/' ; //İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.

            break;
        }

        case 'a':
        case 'A':{ // Atın hareketlerini göstermek için oluşturulan bir 8'e 2'lik bir dizi. At L şeklinde gidebileceği için hamleler ona göre tek tek yazıldı.
            int hareketler[8][2] = {
                    {-2, -1},
                    {-2,  1},
                    {-1, -2},
                    {-1,  2},
                    { 1, -2},
                    { 1,  2},
                    { 2, -1},
                    { 2,  1}
            };
            for (int i = 0; i < 8; ++i) {
                kontrol.satir = satir + hareketler[i][0];
                kontrol.sutun = sutun + hareketler[i][1];

                if(tahta[kontrol.satir][kontrol.sutun] == '-')
                    tahta[kontrol.satir][kontrol.sutun] = '*';
                else
                if(tahta[satir][sutun] == 'A' && tahta[kontrol.satir][kontrol.sutun] < 123 && tahta[kontrol.satir][kontrol.sutun] > 96)
                    tahta2[kontrol.satir][kontrol.sutun] = '/'; //Büyük atın taş yeme koşulu.(büyük taşın küçük taşı taş yeme prensibi ile aynı)
                if(tahta[satir][sutun] == 'a' && tahta[kontrol.satir][kontrol.sutun] < 91 && tahta[kontrol.satir][kontrol.sutun] > 64)
                    tahta2[kontrol.satir][kontrol.sutun] = '/'; //Küçük atın taş yeme koşulu.(küçük taşın büyük taşı taş yeme prensibi ile aynı)
            }
            break;
        }
        case 'v':                    //Vezir hem çapraz hem de düz gidebilen bir taş olduğu için fil ve kalenin hamlelerini kesişim olarak alır.
        case 'V':                    //Yani fil ve kalenin hamlelerini yazıp vezir case'in içine eklersek vezirin hamlelerini belirlemiş oluruz.

        case 'f':                    //Filin oynayabileceği hamleleri gösteren case
        case 'F':{

            for (int i = 1; i < 8; ++i) {     //Üst satırlardan sağ alt çapraza yapılan hamleler için.
                kontrol.satir = satir + i ;
                kontrol.sutun = sutun + i ;
                if(tahta[kontrol.satir][kontrol.sutun] == '-') // Geçerli hamleleri göstermek için tahtada - olan yerleri taşın hamle kabiliyetine göre *'e çevirir.
                    tahta[kontrol.satir][kontrol.sutun] = '*' ;
                else if(tahta[satir][sutun] < 91 && tahta[satir][sutun] > 64  //Eğer taşımız büyük ise ve küçük taşla karşılaşırsak:
                        && tahta[kontrol.satir][kontrol.sutun] < 123 && tahta[kontrol.satir][kontrol.sutun] > 96){
                    tahta2[kontrol.satir][kontrol.sutun] = '/' ;
                    break;}
                else if(tahta[satir][sutun] < 123 && tahta[satir][sutun] > 96     //Eğer taşımız küçük ise ve büyük taşla karşılaşırsak:
                        && tahta[kontrol.satir][kontrol.sutun] < 91 && tahta[kontrol.satir][kontrol.sutun] > 64){
                    tahta2[kontrol.satir][kontrol.sutun] = '/' ;
                    break;}
                else break;

            }

            for (int i = 1; i < 8; ++i) {     //Fillerin sağ üst çapraz hareketi için kullanılan for döngüsü
                kontrol.satir = satir - i ;
                kontrol.sutun = sutun + i ;
                if(tahta[kontrol.satir][kontrol.sutun] == '-')
                    tahta[kontrol.satir][kontrol.sutun] = '*' ;
                else if(tahta[satir][sutun] < 91 && tahta[satir][sutun] > 64    //Eğer taşımız büyük ise ve küçük taşla karşılaşırsak
                        && tahta[kontrol.satir][kontrol.sutun] < 123 && tahta[kontrol.satir][kontrol.sutun] > 96){
                    tahta2[kontrol.satir][kontrol.sutun] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else if(tahta[satir][sutun] < 123 && tahta[satir][sutun] > 96       //Eğer taşımız küçük ise ve büyük taşla karşılaşırsak
                        && tahta[kontrol.satir][kontrol.sutun] < 91 && tahta[kontrol.satir][kontrol.sutun] > 64){
                    tahta2[kontrol.satir][kontrol.sutun] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else break;
            }

            for (int i = 1; i < 8; ++i) {     //Fillerin sol alt çapraz hareketi için kullanılan for döngüsü
                kontrol.satir = satir + i ;
                kontrol.sutun = sutun - i ;
                if(tahta[kontrol.satir][kontrol.sutun] == '-' )
                    tahta[kontrol.satir][kontrol.sutun] = '*' ;
                else if(tahta[satir][sutun] < 91 && tahta[satir][sutun] > 64             //Eğer taşımız büyük ise ve küçük taşla karşılaşırsak
                        && tahta[kontrol.satir][kontrol.sutun] < 123 && tahta[kontrol.satir][kontrol.sutun] > 96){
                    tahta2[kontrol.satir][kontrol.sutun] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else if(tahta[satir][sutun] < 123 && tahta[satir][sutun] > 96             //Eğer taşımız küçük ise ve büyük taşla karşılaşırsak
                        && tahta[kontrol.satir][kontrol.sutun] < 91 && tahta[kontrol.satir][kontrol.sutun] > 64){
                    tahta2[kontrol.satir][kontrol.sutun] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else break;
            }

            for (int i = 1; i < 8; ++i) {     //Fillerin sol üst çapraz hareketi için kullanılan for döngüsü
                kontrol.satir = satir - i ;
                kontrol.sutun = sutun - i ;
                if(tahta[(kontrol.satir)][(kontrol.sutun)] == '-')
                    tahta[(kontrol.satir)][(kontrol.sutun)] = '*' ;
                else if(tahta[satir][sutun] < 91 && tahta[satir][sutun] > 64        //Eğer taşımız büyük ise ve küçük taşla karşılaşırsak
                        && tahta[kontrol.satir][kontrol.sutun] < 123 && tahta[kontrol.satir][kontrol.sutun] > 96){
                    tahta2[kontrol.satir][kontrol.sutun] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else if(tahta[satir][sutun] < 123 && tahta[satir][sutun] > 96        //Eğer taşımız küçük ise ve büyük taşla karşılaşırsak
                        && tahta[kontrol.satir][kontrol.sutun] < 91 && tahta[kontrol.satir][kontrol.sutun] > 64){
                    tahta2[kontrol.satir][kontrol.sutun] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else break;

            }
            if(tahta[satir][sutun] == 'F' || tahta[satir][sutun] == 'f') // Seçilen taş fil ise case den çıkış yap.
                break;
        }

        case 'k':  //Kalenin oynayabileceği hamleleri gösteren case
        case 'K':{
            for (int i = 1; i < 8; ++i) {
                if(tahta[satir][sutun + i] == '-')     //Kalenin sağa dogru olan bosluklarını algılar.
                    tahta[satir][sutun + i] = '*' ;
                else if(tahta[satir][sutun] < 91 && tahta[satir][sutun] > 64      //Eğer taşımız büyük ise ve küçük taşla karşılaşırsak
                        && tahta[satir][sutun + i] < 123 && tahta[satir][sutun + i] > 96){
                    tahta2[satir][sutun + i] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else if(tahta[satir][sutun] < 123 && tahta[satir][sutun] > 96       //Eğer taşımız küçük ise ve büyük taşla karşılaşırsak
                        && tahta[satir][sutun + i] < 91 && tahta[satir][sutun + i] > 64){
                    tahta2[satir][sutun + i] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else break;
            }
            for (int i = 1; i < 8; ++i) {
                if(tahta[satir][sutun - i] == '-')     //Kalenin sola dogru olan bosluklarını algılar.
                    tahta[satir][sutun - i] = '*' ;
                else if(tahta[satir][sutun] < 91 && tahta[satir][sutun] > 64    //Eğer taşımız büyük ise ve küçük taşla karşılaşırsak
                        && tahta[satir][sutun - i] < 123 && tahta[satir][sutun - i] > 96){
                    tahta2[satir][sutun - i] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else if(tahta[satir][sutun] < 123 && tahta[satir][sutun] > 96     //Eğer taşımız küçük ise ve büyük taşla karşılaşırsak
                        && tahta[satir][sutun - i] < 91 && tahta[satir][sutun - i] > 64){
                    tahta2[satir][sutun - i] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else break;
            }

            for (int i = 1; i < 8; ++i) {
                if(tahta[satir + i][sutun] == '-')     //Kalenin aşağı dogru olan bosluklarını algılar.
                    tahta[satir + i][sutun] = '*' ;
                else if(tahta[satir][sutun] < 91 && tahta[satir][sutun] > 64     //Eğer taşımız büyük ise ve küçük taşla karşılaşırsak
                        && tahta[satir + i][sutun] < 123 && tahta[satir + i][sutun] > 96){
                    tahta2[satir + i][sutun] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else if(tahta[satir][sutun] < 123 && tahta[satir][sutun] > 96   //Eğer taşımız küçük ise ve büyük taşla karşılaşırsak
                        && tahta[satir+i][sutun] < 91 && tahta[satir+i][sutun] > 64){
                    tahta2[satir + i][sutun] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else break;
            }

            for (int i = 1; i < 8; ++i) {       //Kalenin yukarı dogru olan bosluklarını algılar.
                if (tahta[satir - i][sutun] == '-')
                    tahta[satir - i][sutun] = '*';
                else if(tahta[satir][sutun] < 91 && tahta[satir][sutun] > 64     //Eğer taşımız büyük ise ve küçük taşla karşılaşırsak
                        && tahta[satir - i][sutun] < 123 && tahta[satir - i][sutun] > 96){
                    tahta2[satir - i][sutun] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else if(tahta[satir][sutun] < 123 && tahta[satir][sutun] > 96    //Eğer taşımız küçük ise ve büyük taşla karşılaşırsak
                        && tahta[satir - i][sutun] < 91 && tahta[satir - i][sutun] > 64){
                    tahta2[satir - i][sutun] = '/' ; // Sanal(tahta2) tahtada yenilebilecek taş için / işareti atanır.
                    break;}
                else break;
            }
            break;   // Seçilen taş fil ise case den çıkış yap.

        }

        case 's': //Şahın oynayabileceği hamleleri gösteren case
        case 'S':
            if(tahta[satir + 1][sutun] == '-')   //Aşağıya yapılan hamle
                tahta[satir + 1][sutun] = '*';
            else if(tahta[satir][sutun] == 's'
                    && tahta[satir + 1][sutun] < 91 && tahta[satir + 1][sutun] > 64
                    || tahta[satir][sutun] == 'S' &&
                       tahta[satir + 1][sutun] < 123 && tahta[satir + 1][sutun] > 96   )

                tahta2[satir + 1][sutun] = '/' ; //İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.

            if(tahta[satir - 1][sutun] == '-')  //Yukarı yapılan hamle
                tahta[satir - 1][sutun] = '*';
            else if(tahta[satir][sutun] == 's'
                    && tahta[satir - 1][sutun] < 91 && tahta[satir - 1][sutun] > 64
                    || tahta[satir][sutun] == 'S' &&
                       tahta[satir - 1][sutun] < 123 && tahta[satir - 1][sutun] > 96   )

                tahta2[satir - 1][sutun] = '/' ; //İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.

            if(tahta[satir][sutun + 1] == '-')  //Sağa yapılan hamle
                tahta[satir][sutun + 1] = '*';
            else if(tahta[satir][sutun] == 's'
                    && tahta[satir][sutun + 1] < 91 && tahta[satir][sutun + 1] > 64
                    || tahta[satir][sutun] == 'S' &&
                       tahta[satir][sutun + 1] < 123 && tahta[satir][sutun + 1] > 96   )

                tahta2[satir][sutun + 1] = '/' ; //İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.

            if(tahta[satir][sutun - 1] == '-')   //Sola yapılan hamle
                tahta[satir][sutun - 1] = '*';
            else if(tahta[satir][sutun] < 123 && tahta[satir][sutun] > 96
                    && tahta[satir][sutun - 1] < 91 && tahta[satir][sutun - 1] > 64
                    || tahta[satir][sutun] < 91 && tahta[satir][sutun] > 64 &&
                       tahta[satir][sutun - 1] < 123 && tahta[satir][sutun - 1] > 96   )

                tahta2[satir][sutun - 1] = '/' ; //İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.

            if(tahta[satir - 1][sutun - 1] == '-')    //Sol üste yapılan hamle
                tahta[satir - 1][sutun - 1] = '*';
            else if(tahta[satir][sutun] == 's'
                    && tahta[satir - 1][sutun - 1] < 91 && tahta[satir - 1][sutun - 1] > 64
                    || tahta[satir][sutun] == 'S' &&
                       tahta[satir - 1][sutun - 1] < 123 && tahta[satir - 1][sutun - 1] > 96   )

                tahta2[satir - 1][sutun - 1] = '/' ; //İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.

            if(tahta[satir - 1][sutun + 1] == '-')    //Sağ üste yapılan hamle
                tahta[satir - 1][sutun + 1] = '*';
            else if(tahta[satir][sutun] == 's'
                    && tahta[satir - 1][sutun + 1] < 91 && tahta[satir - 1][sutun + 1] > 64
                    || tahta[satir][sutun] == 'S' &&
                       tahta[satir - 1][sutun + 1] < 123 && tahta[satir - 1][sutun + 1] > 96   )

                tahta2[satir - 1][sutun + 1] = '/' ; //İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.

            if(tahta[satir + 1][sutun - 1] == '-')    //Sol alta yapılan hamle
                tahta[satir + 1][sutun - 1] = '*';
            else if(tahta[satir][sutun] == 's'
                    && tahta[satir + 1][sutun - 1] < 91 && tahta[satir + 1][sutun - 1] > 64
                    || tahta[satir][sutun] == 'S' &&
                       tahta[satir + 1][sutun - 1] < 123 && tahta[satir + 1][sutun - 1] > 96   )

                tahta2[satir + 1][sutun - 1] = '/' ; //İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.

            if(tahta[satir + 1][sutun + 1] == '-')   //Sağ alta yapılan hamle
                tahta[satir + 1][sutun + 1] = '*';
            else if(tahta[satir][sutun] == 's'
                    && tahta[satir + 1][sutun + 1] < 91 && tahta[satir + 1][sutun + 1] > 64
                    || tahta[satir][sutun] == 'S' &&
                       tahta[satir + 1][sutun + 1] < 123 && tahta[satir + 1][sutun + 1] > 96   )

                tahta2[satir + 1][sutun + 1] = '/' ; //İkinci(sanal) tahtada da taşı yiyebileceği için ikinci tahtada - olan yeri / değeri ile değiştirdik.

    }
    tahtayiGoster();
}
void tasiOyna(int satir,int sutun,int Osatir,int Osutun){       //Parametreler:
    tahta[Osatir][Osutun]= tahta[satir][sutun];                 //Taşı oynayacağı konuma götürür.
    tahta[satir][sutun]='-' ;                                   //Taşın geldiği konumu boşluk yapar.
    tahtayiDuzelt();               //Tahtadaki *'ları tekrar - yapar.
    tahtayiGoster();               //Tahtayı ekrana verir.
}
