#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

FILE *vPtr,*iPtr,*binPtr; // foknsiyonlarda dosya islemleri yapýlacaðýndan global tanýmladým
struct veri
{
    int ogrNo;
    int *ogrNoAdres;
    int dersKodu;
    int puan;
};

void indeksDosyasiOlustur(void);
void kayitEkle(void);
void kayitBul(void);
void kayitSil(void);
void kayitGuncelle(void);
void veriDosyasiniGoster(void);
void indeksDosyasiniGoster(void);
void indeksDosyasiniSil(void);

int main()
{
    do
    {
        system("cls");// ekran temizleme yapar
        printf("\t\tMENU\n1-Indeks Dosyasi Olustur\n2-Kayit Ekle\n3-Kayit Bul\n4-Kayit Sil\n5-Kayit Guncelle\n6-Veri Dosyasini Goster\n7-Indeks Dosyasini Goster\n8-Indeks Dosyasini Sil\n9-Cikis\n\nLutfen islem seciniz:");//menü tablosu
        switch(getch())
        {
        case '1':
        {
            system("cls");  //text dosyasi olusturur
            indeksDosyasiOlustur();
            break;
        }
        case '2':
        {
            system("cls");//kayit ekler
            kayitEkle();
            break;
        }
        case '3':
        {
            system("cls"); // kayit bulur
            kayitBul();
            break;
        }
        case '4':
        {
            system("cls"); // kayit siler
            kayitSil();
            break;
        }
        case '5':
        {
            system("cls");  // kayit gunceller
            kayitGuncelle();
            break;
        }
        case '6':
        {
            system("cls"); // binary dosyasini gösterir
            veriDosyasiniGoster();
            break;
        }
        case '7':
        {
            system("cls");  // text dosyasini gösterir
            indeksDosyasiniGoster();
            break;
        }
        case '8':
        {
            system("cls");
            indeksDosyasiniSil();//indeks dosyasini siler
            break;
        }
        case '9':
        {
            return 0;
            break;//cikis
        }
        default:
        {
            printf("Hatali giris");
        }

        }

    }
    while(1);
    getch();
    return 0;
}
void indeksDosyasiOlustur(void)
{
    iPtr=fopen("indeks.txt","a"); // a ile dosya olusturuyoruz
    if(iPtr==NULL)
    {
        puts("Dosya acilamadi.");
        exit(1);

    }
    do
    {
        puts("Indeks dosyasi olusturuldu.Cikmak icin ESC tusuna basiniz.");

    }
    while(getch()!=27);
    fclose(vPtr);
    puts("\nDevam etmek icin bir tusa basin ...");
    getch();
}
void kayitEkle(void)
{
    struct veri *ogr=(struct kayit *)malloc(sizeof(struct veri));
    int i=0;
    vPtr=fopen("veri.bin","a+b"); // Binary dosyayý ekleme modunda açar, okuma da yapýlabilir.
    if(vPtr == NULL)
    {
        puts("Dosya acilamadi.");
        exit(1);
    }
    puts("\nOgrenci bilgilerini girin: ");
    do  // Önce bellege yazdýrýyoruz.
    {
        i++;
        fflush(stdin);//iþlevi, akýþýn çýktý arabelleðini temizlemek için kullanýlýr.
        printf("%d. Ogrencinin numarasi: ",i);
        scanf("%d",&ogr->ogrNo);
        ogr->ogrNoAdres=&ogr->ogrNo+i;
        printf("%d. Ogrencinin ders kodu: ",i);
        scanf("%d",&ogr->dersKodu);
        printf("%d. Ogrencinin puani:",i);
        scanf("%d",&ogr->puan);
        printf("\n");

        fwrite(ogr,sizeof(struct veri),1,vPtr);  // Sonra dosyaya yazdýrýyoruz.
        puts("Yeni bir kayit icin bir tusa, cikmak icin ESC tusuna basiniz.");
    }
    while(getch()!=27);
    fclose(vPtr);
    puts("\nBilgiler kaydedildi devam etmek icin bir tusa basin ...");
    getch();
}


void kayitBul(void)
{
    struct veri *ogr=(struct veri *)malloc(sizeof(struct veri));
    int numara;
    int durum=0;// durum=0 ise kayit bulunmamaktadirç
    fflush(stdin);//iþlevi, akýþýn çýktý arabelleðini temizlemek için kullanýlýr.
    printf("\nOgrenci numarasini giriniz: ");
    scanf("%d",&numara);
    iPtr=fopen("indeks.txt","w+");// Text dosyayý yazma modunda açar, okuma da yapýlabilir.
    vPtr=fopen("veri.bin","r+b");//Binary dosyayý okuma modunda açar, yazma da yapýlabilir.
    if(vPtr == NULL)
    {
        puts("Dosya acilamadi.");
        exit(1);
    }
    if(iPtr == NULL)
    {
        puts("Dosya acilamadi.");
        exit(1);
    }

    int sayac;
    while(fread(ogr,sizeof(struct veri),1,vPtr)!=NULL)//dosyadaki satir sayisi bularak kisi sayisini bulmus oluruz
    {
        sayac++;
    }

    fseek(vPtr,0,SEEK_SET);//imleci dosyanin en basina alýyoruz
    int sirala[sayac][4];
    int i=0,j,k;
    int tmp[1]= {0};

    while(fread(ogr,sizeof(struct veri),1,vPtr)!=NULL)// veri dosyasindakileri matrise atarak sýralamayi kolaylaþtýracaðýz
    {


        sirala[i][0]=ogr->ogrNo;
        sirala[i][1]=ogr->dersKodu;
        sirala[i][2]=ogr->puan;
        sirala[i][3]=ogr->ogrNoAdres;


        i++;
    }

    fseek(vPtr,0,SEEK_SET);//imleci dosyanin en basina alýyoruz
    // Alt tarafta bouble sort fonsiyonu devreye giriyor
    while(fread(ogr,sizeof(struct veri),1,vPtr)!=NULL)
    {
        for ( k=0 ; k < sayac-1 ; k++ )
        {

            for (j=0 ; j < sayac-1; j++)
            {

                if (sirala[j][0]>sirala[j+1][0])
                {
                    tmp[0] = sirala[j][0];
                    sirala[j][0]= sirala[j+1][0];
                    sirala[j+1][0] = tmp[0];

                    tmp[0] = sirala[j][1];
                    sirala[j][1]= sirala[j+1][1];
                    sirala[j+1][1] = tmp[0];

                    tmp[0] = sirala[j][2];
                    sirala[j][2]= sirala[j+1][2];
                    sirala[j+1][2] = tmp[0];

                    tmp[0] = sirala[j][3];
                    sirala[j][3]= sirala[j+1][3];
                    sirala[j+1][3] = tmp[0];

                }
            }
        }

    }

    fclose(iPtr);
    iPtr=fopen("indeks.txt","w+");//Text dosyayý yazma modunda açar, okuma da yapýlabilir.
    i=0;
    while(!feof(iPtr))// dosyayi bellege yazdiriyoruz
    {
        fscanf(iPtr,"\n%d %d %d %x",sirala[i][0],sirala[i][1],sirala[i][2],sirala[i][3]);
        i++;
    }
    // Alt tarafta binary search fonsiyonu devreye giriyor
    int bas=0;
    int son=sayac-1;
    int orta=0;


    orta = (bas+son)/2;

    do
    {
        if (sirala[orta][0] < numara)
            bas = orta + 1;
        else if (sirala[orta][0] == numara)
        {
            printf("\n%-20s%-20s%-20s%-20s\n", "OGRENCI NUMARASI", "DERS KODU", "PUANI","OGRENCI NUMARASININ ADRESI");
            for(int i=0,j=1; j<5, i<5; j++, i++)
            {
                if(sirala[orta+i][0] == numara)
                {
                    printf("\n%-20d%-20d%-20d%-20x\n",sirala[orta+i][0],sirala[orta+i][1],sirala[orta+i][2],sirala[orta+i][3]);
                }
                if(sirala[orta-j][0] == numara)
                {
                    printf("\n%-20d%-20d%-20d%-20x\n",sirala[orta-j][0],sirala[orta-j][1],sirala[orta-j][2],sirala[orta-j][3]);
                }

            }
            break;

        }
        else
            son  = orta - 1;

        orta = (bas + son)/2;
    }
    while (bas <= son);

    if (bas > son)
        printf("%d numarali ogrenci bulunamadi \n", numara);

    fclose(iPtr);
    fclose(vPtr);
    puts("\nBilgiler lsitelendi devam etmek icin bir tusa basin ...");
    getch();

}


void kayitSil(void)
{

    struct veri ogr;
    int num,durum1=0;// durum 0 ise silinememiþtir
    printf("Silinecek ogrenci numarasi giriniz: ");
    scanf("%d",&num);

    vPtr = fopen("veri.bin","rb");//Binary dosyayý okuma modunda açar, yazma da yapýlabilir.
    binPtr= fopen("yedek.bin","wb");//Binary dosyayý yazma modunda açar, okuma da yapýlabilir.


    if(vPtr == NULL)
    {
        printf("Hata");
        exit(1);
    }
    while(fread(&ogr,sizeof(struct veri),1,vPtr)!=NULL)
    {

        if(num != ogr.ogrNo)
        {
            fwrite(&ogr,sizeof(struct veri),1,binPtr);// dosyayi yedege yazdiriyoruz
        }
        else
        {
            durum1=1;// eðer durum 1 se kayit silinir
        }

    }
    int i=0;

    fclose(vPtr);
    fclose(binPtr);


    if(durum1 == 1)
    {
        remove("veri.bin");//veri dosyasýný siliyoruz
        rename("yedek.bin","veri.bin");// yedek dosyanin adýný veri olarak degistiryoruz
        printf("Silme islemi tamamlandi.Devam etmek icin bir tusa basiniz...");
    }
    else
    {
        remove("yedek.bin");
        printf("%d numarali bir ogrenci bulunamadi",num);
    }


    fflush(stdin);//iþlevi, akýþýn çýktý arabelleðini temizlemek için kullanýlýr.

    getch();

}

void kayitGuncelle(void)
{
    struct veri ogr;
    int num,durum=0;
    printf("Bilgisi guncellenecek ogrenci numarasini giriniz: ");
    scanf("%d",&num);
    vPtr = fopen("veri.bin","rb");//Binary dosyayý okuma modunda açar, yazma da yapýlabilir.
    binPtr= fopen("yedek.bin","wb");//Binary dosyayý yazma modunda açar, okuma da yapýlabilir.

    if(vPtr == NULL)
    {
        printf("Hata");
        exit(1);
    }

    while(fread(&ogr,sizeof(struct veri),1,vPtr)!=NULL)
    {

        if(num != ogr.ogrNo)
        {
            fwrite(&ogr,sizeof(struct veri),1,binPtr);// dosyayi yedege atýyoruz
        }
        else// elseye girerse puanlarý degistirme kodlarýna giris yapýyoruz
        {
            printf("\n%-20s%-20s%-20s%-20s\n", "OGRENCI NUMARASI", "DERS KODU", "PUANI","OGRENCI NUMARASININ ADRESI");
            printf("\n%-20d%-20d%-20d%-20x\n",ogr.ogrNo,ogr.dersKodu,ogr.puan,ogr.ogrNoAdres);
            printf("Puani : ");
            scanf("%d",&ogr.puan);
            fwrite(&ogr,sizeof(struct veri),1,binPtr);
            durum = 1;
        }

    }


    fclose(vPtr);
    fclose(binPtr);

    if(durum == 1)// kayit guncellenmis demektir
    {
        remove("veri.bin");
        rename("yedek.bin","veri.bin");
        puts("Ogrenci bilgileri degistirildi...");
    }
    else // else ye girerse ogrenci bulunamamistir
    {
        remove("yedek.bin");
        puts("Ogrenci bulunamadi...");
    }
    fflush(stdin);//iþlevi, akýþýn çýktý arabelleðini temizlemek için kullanýlýr.
    getch();

}


void veriDosyasiniGoster(void)
{
    struct veri ogr;
    vPtr = fopen("veri.bin","r+b"); //Binary dosyayý okuma modunda açar, yazma da yapýlabilir. "a
    if(vPtr != NULL)
    {
        printf("\n%-20s%-20s%-20s%-20s\n", "OGRENCI NUMARASI", "DERS KODU", "PUANI","OGRENCI NUMARASININ ADRESI");
        while(fread(&ogr,sizeof(struct veri),1,vPtr)!=NULL)
        {

            printf("\n%-20d%-20d%-20d%-20x\n",ogr.ogrNo,ogr.dersKodu,ogr.puan,ogr.ogrNoAdres);
        }

        fclose(vPtr);
    }
    puts("\nBilgiler listelendi devam etmek icin bir tusa basin ...");
    getch();
}
void indeksDosyasiniGoster(void)
{
    struct veri *ogr=(struct veri *)malloc(sizeof(struct veri));
    vPtr= fopen("veri.bin","r+b");//Binary dosyayý okuma modunda açar, yazma da yapýlabilir. "a
    iPtr = fopen("indeks.txt","w+");//Text dosyayý yazma modunda açar, okuma da yapýlabilir.
    int sayac=0;
    if(vPtr == NULL)
    {
        puts("Dosya acilamadi");
        exit(1);
    }
    if(iPtr == NULL)
    {
        puts("Dosya acilamadi");
        exit(1);
    }


    while(fread(ogr,sizeof(struct veri),1,vPtr)!=NULL)// veri dosyasindakileri matrise atarak sýralamayi kolaylaþtýracaðýz
    {
        sayac++;
    }
    fseek(vPtr,0,SEEK_SET);
    int sirala[sayac][4];
    int i=0,j,k;
    int tmp[1]= {0};

    while(fread(ogr,sizeof(struct veri),1,vPtr)!=NULL)// diziyi iki boyutlu dizi ye atarak siralama islemini kolaylastiryoruz
    {


        sirala[i][0]=ogr->ogrNo;
        sirala[i][1]=ogr->dersKodu;
        sirala[i][2]=ogr->puan;
        sirala[i][3]=ogr->ogrNoAdres;


        i++;
    }

    fseek(vPtr,0,SEEK_SET);// imleci dosyanin basina götürüyoruz
    while(fread(ogr,sizeof(struct veri),1,vPtr)!=NULL)
    {
        // bubble sort algoritmasý
        for ( k=0 ; k < sayac-1 ; k++ )
        {

            for (j=0 ; j < sayac-1; j++)
            {

                if (sirala[j][0]>sirala[j+1][0])
                {



                    tmp[0] = sirala[j][0];
                    sirala[j][0]= sirala[j+1][0];
                    sirala[j+1][0] = tmp[0];

                    tmp[0] = sirala[j][1];
                    sirala[j][1]= sirala[j+1][1];
                    sirala[j+1][1] = tmp[0];

                    tmp[0] = sirala[j][2];
                    sirala[j][2]= sirala[j+1][2];
                    sirala[j+1][2] = tmp[0];

                    tmp[0] = sirala[j][3];
                    sirala[j][3]= sirala[j+1][3];
                    sirala[j+1][3] = tmp[0];

                }
            }
        }

    }

    printf("\n%-20s%-20s%-20s%-20s\n", "OGRENCI NUMARASI", "DERS KODU", "PUANI","OGRENCI NUMARASININ ADRESI");

    for(i=0; i<sayac; i++)
    {

        fprintf(iPtr,"\n%-20d%-20d%-20d%-20x\n",sirala[i][0],sirala[i][1],sirala[i][2],sirala[i][3]);// dosyaya yazdiriyoruz
        printf("\n%-20d%-20d%-20d%-20x\n",sirala[i][0],sirala[i][1],sirala[i][2],sirala[i][3]);

    }



    fclose(vPtr);
    fclose(iPtr);

    puts("\nBilgiler listelendi devam etmek icin bir tusa basin ...");
    getch();
}

void  indeksDosyasiniSil()
{
    for(int i = 0; i<100; i++)
    {

    }
    remove("indeks.txt");
    puts("Dosya basari ile silindi");
    getch();
}










