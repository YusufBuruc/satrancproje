char board[9][9] = {
        {0,1,   2,    3,    4,   5,   6,  7,    8},
        {1,'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {2,'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {3,'-', '-', '-', '-', '-', '-', '-', '-'},
        {4,'-', '-', '-', '-', '-', '-', '-', '-'},
        {5,'-', '-', '-', '-', '-', '-', '-', '-'},
        {6,'-', '-', '-', '-', '-', '-', '-', '-'},
        {7,'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {8,'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
};
char board2[9][9] = {
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


















void tahtayiDuzelt() {                     //Geçerli hamleler gösterildikten sonra "*" ları tekrar "-" karakterine dönüştüren fonksiyon
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == '*')
                board[i][j] = '-';
            board2[i][j] = '-' ;           //2. Tahtayı eski haline getirir
        }
    }
}

void tahtayiGoster(){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(i == 0)
                printf("%d  ",board[i][j]);       //önce tahtanın üstündeki "rakamlar"
            else if (j == 0)
                printf("%d  ",board[i][j]);       //sonra tahtanın solundaki "rakamlar"
            else
                printf("%c  ",board[i][j]);       //en son her bir "taş ve boşluk" -char türünde- yazdırılır
        }
        printf("\n");
    }
    printf("\n");
}

void validMoves(int satir,int sutun) {
    int satir1 = 0, sutun1 = 0;
    int* satir1ptr ;
    int* sutun1ptr ;
    satir1ptr = &satir1 ;
    sutun1ptr = &sutun1 ;

    switch (board[satir][sutun]) {           //Taşın Türüne Göre Hamleler
        case 'P': {                          // Alt tarafın piyonunun oynayabileceği hamleler
            if (satir == 7) {                     //Başlangıç konumundaysa 2 ileri oynayabilir
                for (int i = 1; i <3 ; ++i) {
                    if(board[satir-i][sutun] == '-')
                        board[satir-i][sutun] = '*' ;
                    else break;
                }
            } else if (board[satir - 1][sutun] == '-')  //Başlangıç konumunda değilse yalnızca 1 ileri oynayabilir
                board[satir - 1][sutun] = '*';

            if( board[satir-1][sutun+1] < 123 && board[satir-1][sutun+1] > 96) //eger sağ üst çaprazda küçük taş var ise tahta2 de oraya / işareti koy
                board2[satir-1][sutun+1] = '/' ;
            if( board[satir-1][sutun-1] < 123 && board[satir-1][sutun-1] > 96) //eger sol üst çaprazda küçük taş var ise tahta2 de oraya / işareti koy
                board2[satir-1][sutun-1] = '/' ;

            break;

        }

        case 'p':{      //Üst Piyonun onayabileceği hamleler
            if (satir == 2) {
                for (int i = 1; i < 3; ++i) {
                    if(board[satir+i][sutun] == '-')
                        board[satir + i][sutun] = '*';
                    else break;
                }
            } else if (board[satir + 1][sutun] == '-')
                board[satir + 1][sutun] = '*';

            if( board[satir+1][sutun+1] < 91 && board[satir+1][sutun+1] > 64) //eger sağ alt çaprazda büyük taş var ise tahta2 de oraya / işareti koy
                board2[satir+1][sutun+1] = '/' ;
            if( board[satir+1][sutun-1] < 91 && board[satir+1][sutun-1] > 64) //eger sol alt çaprazda büyük taş var ise tahta2 de oraya / işareti koy
                board2[satir+1][sutun-1] = '/' ;

            break;
        }

        case 'N':
        case 'n':{
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
                *satir1ptr = satir + hareketler[i][0];
                *sutun1ptr = sutun + hareketler[i][1];

                if(board[*satir1ptr][*sutun1ptr] == '-')
                    board[*satir1ptr][*sutun1ptr] = '*';
                else
                if( board[satir][sutun] == 'N' && board[*satir1ptr][*sutun1ptr] < 123 && board[*satir1ptr][*sutun1ptr] > 96)
                    board2[*satir1ptr][*sutun1ptr] = '/';
                if(board[satir][sutun] == 'n' && board[*satir1ptr][*sutun1ptr] < 91 && board[*satir1ptr][*sutun1ptr] > 64)
                    board2[*satir1ptr][*sutun1ptr] = '/';
            }
            break;
        }
        case 'Q':                    //Vezir hem fil hem kale gibi davrandığından
        case 'q':                    //ikisini de sırayla çalıştırsak bir mahsuru olmaz
        case 'b':                   //Filin oynayabileceği hamleler
        case 'B':{

            for (int i = 1; i < 8; ++i) {     //sağ alt çapraz
                *satir1ptr = satir + i ;
                *sutun1ptr = sutun + i ;
                if(board[*satir1ptr][*sutun1ptr] == '-')
                    board[*satir1ptr][*sutun1ptr] = '*' ;
                else if(board[satir][sutun] < 91 && board[satir][sutun] > 64                            //Eğer taşımız büyük ise
                        && board[*satir1ptr][*sutun1ptr] < 123 && board[*satir1ptr][*sutun1ptr] > 96){   //ve küçük taşla karşılaşırsak
                    board2[*satir1ptr][*sutun1ptr] = '/' ;
                    break;}
                else if(board[satir][sutun] < 123 && board[satir][sutun] > 96                           //Eğer taşımız küçük ise
                        && board[*satir1ptr][*sutun1ptr] < 91 && board[*satir1ptr][*sutun1ptr] > 64){    // ve büyük taşla karşılaşırsak
                    board2[*satir1ptr][*sutun1ptr] = '/' ;

                    break;}
                else break;

            }

            for (int i = 1; i < 8; ++i) {     //sağ üst çapraz
                *satir1ptr = satir - i ;
                *sutun1ptr = sutun + i ;
                if(board[*(satir1ptr)][*(sutun1ptr)] == '-')
                    board[*(satir1ptr)][*(sutun1ptr)] = '*' ;
                else if(board[satir][sutun] < 91 && board[satir][sutun] > 64                            //Eğer taşımız büyük ise
                        && board[*satir1ptr][*sutun1ptr] < 123 && board[*satir1ptr][*sutun1ptr] > 96){   //ve küçük taşla karşılaşırsak
                    board2[*satir1ptr][*sutun1ptr] = '/' ;
                    break;}
                else if(board[satir][sutun] < 123 && board[satir][sutun] > 96                           //Eğer taşımız küçük ise
                        && board[*satir1ptr][*sutun1ptr] < 91 && board[*satir1ptr][*sutun1ptr] > 64){    // ve büyük taşla karşılaşırsak
                    board2[*satir1ptr][*sutun1ptr] = '/' ;
                    break;}
                else break;
            }

            for (int i = 1; i < 8; ++i) {     //sol alt çapraz
                *satir1ptr = satir + i ;
                *sutun1ptr = sutun - i ;
                if(board[*(satir1ptr)][*(sutun1ptr)] == '-' )
                    board[*(satir1ptr)][*(sutun1ptr)] = '*' ;
                else if(board[satir][sutun] < 91 && board[satir][sutun] > 64                            //Eğer taşımız büyük ise
                        && board[*satir1ptr][*sutun1ptr] < 123 && board[*satir1ptr][*sutun1ptr] > 96){   //ve küçük taşla karşılaşırsak
                    board2[*satir1ptr][*sutun1ptr] = '/' ;
                    break;}
                else if(board[satir][sutun] < 123 && board[satir][sutun] > 96                           //Eğer taşımız küçük ise
                        && board[*satir1ptr][*sutun1ptr] < 91 && board[*satir1ptr][*sutun1ptr] > 64){    // ve büyük taşla karşılaşırsak
                    board2[*satir1ptr][*sutun1ptr] = '/' ;
                    break;}
                else break;
            }

            for (int i = 1; i < 8; ++i) {     //sol üst çapraz
                *satir1ptr = satir - i ;
                *sutun1ptr = sutun - i ;
                if(board[*(satir1ptr)][*(sutun1ptr)] == '-')
                    board[*(satir1ptr)][*(sutun1ptr)] = '*' ;
                else if(board[satir][sutun] < 91 && board[satir][sutun] > 64                            //Eğer taşımız büyük ise
                        && board[*satir1ptr][*sutun1ptr] < 123 && board[*satir1ptr][*sutun1ptr] > 96){   //ve küçük taşla karşılaşırsak
                    board2[*satir1ptr][*sutun1ptr] = '/' ;
                    break;}
                else if(board[satir][sutun] < 123 && board[satir][sutun] > 96                           //Eğer taşımız küçük ise
                        && board[*satir1ptr][*sutun1ptr] < 91 && board[*satir1ptr][*sutun1ptr] > 64){    // ve büyük taşla karşılaşırsak
                    board2[*satir1ptr][*sutun1ptr] = '/' ;
                    break;}
                else break;

            }
            if(board[satir][sutun] == 'B' || board[satir][sutun] == 'b') // taşımız filse çıkış yap vezir ise devam et
                break;
        }
        case 'r':
        case 'R':{
            for (int i = 1; i < 8; ++i) {
                if(board[satir][sutun+i] == '-')     //saga dogru boslukları algılar
                    board[satir][sutun+i] = '*' ;
                else if(board[satir][sutun] < 91 && board[satir][sutun] > 64                            //Eğer taşımız büyük ise
                        && board[satir][sutun+i] < 123 && board[satir][sutun+i] > 96){                  //ve küçük taşla karşılaşırsak
                    board2[satir][sutun+i] = '/' ;
                    break;}
                else if(board[satir][sutun] < 123 && board[satir][sutun] > 96                           //Eğer taşımız küçük ise
                        && board[satir][sutun+i] < 91 && board[satir][sutun+i] > 64){    // ve büyük taşla karşılaşırsak
                    board2[satir][sutun+i] = '/' ;
                    break;}
                else break;
            }
            for (int i = 1; i < 8; ++i) {
                if(board[satir][sutun-i] == '-')     //sola dogru boşlukları algılar
                    board[satir][sutun-i] = '*' ;
                else if(board[satir][sutun] < 91 && board[satir][sutun] > 64                            //Eğer taşımız büyük ise
                        && board[satir][sutun-i] < 123 && board[satir][sutun-i] > 96){   //ve küçük taşla karşılaşırsak
                    board2[satir][sutun-i] = '/' ;
                    break;}
                else if(board[satir][sutun] < 123 && board[satir][sutun] > 96                           //Eğer taşımız küçük ise
                        && board[satir][sutun-i] < 91 && board[satir][sutun-i] > 64){    // ve büyük taşla karşılaşırsak
                    board2[satir][sutun-i] = '/' ;
                    break;}
                else break;}
            for (int i = 1; i < 8; ++i) {
                if(board[satir+i][sutun] == '-')     //aşağı doğru boşlukları algılar
                    board[satir+i][sutun] = '*' ;
                else if(board[satir][sutun] < 91 && board[satir][sutun] > 64                            //Eğer taşımız büyük ise
                        && board[satir+i][sutun] < 123 && board[satir+i][sutun] > 96){   //ve küçük taşla karşılaşırsak
                    board2[satir+i][sutun] = '/' ;
                    break;}
                else if(board[satir][sutun] < 123 && board[satir][sutun] > 96                           //Eğer taşımız küçük ise
                        && board[*satir1ptr][*sutun1ptr] < 91 && board[*satir1ptr][*sutun1ptr] > 64){    // ve büyük taşla karşılaşırsak
                    board2[*satir1ptr][*sutun1ptr] = '/' ;
                    break;}
                else break;
            }
            for (int i = 1; i < 8; ++i) {            //yukarı doğru boşlukları algılar
                if (board[satir-i][sutun] == '-')
                    board[satir-i][sutun] = '*';
                else if(board[satir][sutun] < 91 && board[satir][sutun] > 64                            //Eğer taşımız büyük ise
                        && board[satir-i][sutun] < 123 && board[satir-i][sutun] > 96){   //ve küçük taşla karşılaşırsak
                    board2[satir-i][sutun] = '/' ;
                    break;}
                else if(board[satir][sutun] < 123 && board[satir][sutun] > 96                           //Eğer taşımız küçük ise
                        && board[satir-i][sutun] < 91 && board[satir-i][sutun] > 64){    // ve büyük taşla karşılaşırsak
                    board2[satir-i][sutun] = '/' ;
                    break;}
                else break;
            }
            break;   //CASE 'R' den çıkar

        }
        case 'k':
        case 'K':
            if(board[satir+1][sutun] == '-')                                            //Aşağı
                board[satir+1][sutun] = '*';
            else if(   board[satir][sutun] < 123 && board[satir][sutun] > 96
                       && board[satir+1][sutun] < 91 && board[satir+1][sutun] > 64
                       || board[satir][sutun] < 91 && board[satir][sutun] > 64 &&
                          board[satir+1][sutun] < 123 && board[satir+1][sutun] > 96   )

                board2[satir+1][sutun] = '/' ;

            if(board[satir-1][sutun] == '-')                                            //Yukarı
                board[satir-1][sutun] = '*';
            else if(   board[satir][sutun] < 123 && board[satir][sutun] > 96
                       && board[satir-1][sutun] < 91 && board[satir-1][sutun] > 64
                       || board[satir][sutun] < 91 && board[satir][sutun] > 64 &&
                          board[satir-1][sutun] < 123 && board[satir-1][sutun] > 96   )

                board2[satir-1][sutun] = '/' ;

            if(board[satir][sutun+1] == '-')                                            //Sağa
                board[satir][sutun+1] = '*';
            else if(   board[satir][sutun] < 123 && board[satir][sutun] > 96
                       && board[satir][sutun+1] < 91 && board[satir][sutun+1] > 64
                       || board[satir][sutun] < 91 && board[satir][sutun] > 64 &&
                          board[satir][sutun+1] < 123 && board[satir][sutun+1] > 96   )

                board2[satir][sutun+1] = '/' ;

            if(board[satir][sutun-1] == '-')                                            //Sola
                board[satir][sutun-1] = '*';
            else if(   board[satir][sutun] < 123 && board[satir][sutun] > 96
                       && board[satir][sutun-1] < 91 && board[satir][sutun-1] > 64
                       || board[satir][sutun] < 91 && board[satir][sutun] > 64 &&
                          board[satir][sutun-1] < 123 && board[satir][sutun-1] > 96   )

                board2[satir][sutun-1] = '/' ;

            if(board[satir-1][sutun-1] == '-')                                            //Sol üst
                board[satir-1][sutun-1] = '*';
            else if(   board[satir][sutun] < 123 && board[satir][sutun] > 96
                       && board[satir-1][sutun-1] < 91 && board[satir-1][sutun-1] > 64
                       || board[satir][sutun] < 91 && board[satir][sutun] > 64 &&
                          board[satir-1][sutun-1] < 123 && board[satir-1][sutun-1] > 96   )

                board2[satir-1][sutun-1] = '/' ;

            if(board[satir-1][sutun+1] == '-')                                            //Sağ üst
                board[satir-1][sutun+1] = '*';
            else if(   board[satir][sutun] < 123 && board[satir][sutun] > 96
                       && board[satir-1][sutun+1] < 91 && board[satir-1][sutun+1] > 64
                       || board[satir][sutun] < 91 && board[satir][sutun] > 64 &&
                          board[satir-1][sutun+1] < 123 && board[satir-1][sutun+1] > 96   )

                board2[satir-1][sutun+1] = '/' ;

            if(board[satir+1][sutun-1] == '-')                                            //sol alt
                board[satir+1][sutun-1] = '*';
            else if(   board[satir][sutun] < 123 && board[satir][sutun] > 96
                       && board[satir+1][sutun-1] < 91 && board[satir+1][sutun-1] > 64
                       || board[satir][sutun] < 91 && board[satir][sutun] > 64 &&
                          board[satir+1][sutun-1] < 123 && board[satir+1][sutun-1] > 96   )

                board2[satir+1][sutun-1] = '/' ;

            if(board[satir+1][sutun+1] == '-')                                            //sağ alt
                board[satir+1][sutun+1] = '*';
            else if(   board[satir][sutun] < 123 && board[satir][sutun] > 96
                       && board[satir+1][sutun+1] < 91 && board[satir+1][sutun+1] > 64
                       || board[satir][sutun] < 91 && board[satir][sutun] > 64 &&
                          board[satir+1][sutun+1] < 123 && board[satir+1][sutun+1] > 96   )

                board2[satir+1][sutun+1] = '/' ;

    }
    tahtayiGoster();
}
void tasiOyna(int satir,int sutun,int Osatir,int Osutun){       //Parametreler:
    switch (board[satir][sutun] ) {                             //Oynanacak taşın satır ve sütunu , oynanacağı konumun satır ve sütunu
        case 'k':
        case 'K':
        case 'q':
        case 'Q':
        case 'r':
        case 'R':
        case 'n':
        case 'N':
        case 'b':
        case 'B':
        case 'p':
        case 'P': board[Osatir][Osutun] = board[satir][sutun] ; //Taşı oynanacağı konuma götürür
            board[satir][sutun] = '-' ;                         //Taşın baştaki konumunu boşluk yapar
            break;

    }
    tahtayiDuzelt();               //Yıldız varsa tekrar boşluk yapar
    tahtayiGoster();               //Tahtayı ekrana verir
}
