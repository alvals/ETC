// http://book.pythontips.com/en/latest/python_c_extension.html
//.dll instead of .so for Windows
//#For Linux
//$  gcc -shared -Wl,-soname,adder -o adder.so -fPIC add.c

//#For Mac
//$ gcc -shared -Wl,-install_name,adder.so -o adder.so -fPIC add.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_uchar_array(unsigned char *buf, int count);

void fill_with_random(unsigned char *buf, int count);

void parse_package_1(unsigned char *in, int tam_in, float *out, int tam_out);

// Now this method is useless. Justo a proof of concept
void parse_package_2(unsigned char *in, int tam_in, float *out, int tam_out);

void print_float_array(float *buf, int count);

int conver1 (int cad1,int cad2,  int salida);
long converbar(unsigned char x, unsigned char y, unsigned char z, long out);
short converhour(unsigned char x, short out );
short convermin(unsigned char x, unsigned char y, short out);
short converseg(unsigned char x, unsigned char y, short out);
short converdia(unsigned char x, short out);
short convermes(unsigned char x,unsigned char y, short out);
short converanio(unsigned char x, short out);
int converaltura(unsigned char x,unsigned char y, int out);
double converlatlon(int h,int hm,int lm,int l,double salida );

// int main() {
//     int tam_array_in = 30;
//     int tam_array_out = 16;
//     unsigned char array_in[30];
//     float array_out[16];
//
//     srand(time(NULL));
//
//     fill_with_random(array_in, tam_array_in);
//     print_uchar_array(array_in, tam_array_in);
//
//     printf("\n\n");
//
//     parse_package(array_in, tam_array_in, array_out, tam_array_out);
//     print_float_array(array_out, tam_array_out);
//
//     return 0;
// }

void print_uchar_array(unsigned char *buf, int count){
    for (size_t i = 0; i < count; i++) {
        printf("%d, ", buf[i]);
    }
}

void fill_with_random(unsigned char *buf, int count) {
    unsigned char num;

    for(size_t i = 0; i < count; ++i){
        num = rand();
        buf[i] = num;
    }
}

void parse_package_1(unsigned char *cadena, int tam_in, float *datos, int tam_out){
    //------------------programa editado---------------
                                                       //lat
    /*********************************************************
            PROGRAMA PRINCIPAL
    **********************************************************/

        //==============declaracion de funciones===

        //=============variables de los sensores================
        short nukaworld=0;   //variable intermedia para MAGX,MAGY,MAGZ,ACEL Y GIR
        short new_vegas1 = 0, new_vegas2 = 0, new_vegas3 = 0;
        short farharbor  = 0, farharbor1 = 0, farharbor2 = 0;
        int   farharbor3 = 0;
        short vault_tec  = 0, vault_tec1 = 0;  // variable intermedia para barometro (4 bits altos)
        int   vault_tec2 = 0;
        short wasteland  = 0,   wasteland0 = 0, wasteland1 = 0, wasteland2 = 0, wasteland3 = 0;
        short brokensteel0 = 0, brokensteel1 = 0,brokensteel2 = 0, brokensteel3 = 0;
        short anchorage0 = 0, anchorage1 = 0, anchorage2 = 0, anchorage3 = 0,anchoragea = 0;
        short point_lookout0 = 0, point_lookout1 = 0, point_lookout2 = 0,point_lookout3 = 0;
        short mothership0 = 0, mothership1 = 0,mothership2 = 0,mothership3 = 0,mothership4 = 0;
        int automatron=0;
        float var;
        const float magne = 0.0729927;      //configuracion de la ganancia del magnetometro
        const float dps=0.076335877;   //grados por segiundo?
        const float acce= 0.000061035;  //
        const float a = (9.81/2048.0);  //escalado a 16g
        const float gy = (250/32768.0);  //escalado a
        const float barometro = 0.008;  //conversion de hectopascales?
        const float valor = 0.080566;  // datos en binario * voltaje de referencia * escalamiento
        const float sensibilidad= 0.185;  //sensor de corriente
        const float relacion =  0.080566;  //datos en
        // const float rev=0.000244;   // voltaje de referencia del ADC = 1 v ; 1 binario = 0.000244 v
        const float pasos = 186.81818182 * 2;
        const float div = 0.001;
    /********************************************************
    ==================MAGNETOMETRO HMC5883L=======================
     ******************************************************/
    //-------------------------magx-------------------
        float MAGX;
        nukaworld = conver1(cadena[0], cadena[1], nukaworld);
        MAGX = nukaworld * magne;
        //printf("\n magnetometroX: %f\n", MAGX);

    //--------------------------------magy-----------------------
        float MAGY;
        nukaworld=conver1(cadena[2],cadena[3],nukaworld);
        MAGY=nukaworld*magne;
        //printf("\n magnetometroY: %f\n", MAGY);
    //--------------------------------magz-----------------------
        float MAGZ;
        nukaworld=conver1(cadena[4],cadena[5],nukaworld);
        MAGZ=nukaworld*magne;
        //printf("\n magnetometroZ: %f\n", MAGZ);
    /********************************************************
    ==================ACEL-GYR - MPU6050========================
    ******************************************************/
      //-------------------------acelerometro en x-------------------
        float ACELX;
        nukaworld=conver1(cadena[6],cadena[7],nukaworld);
        ACELX=nukaworld*a;
        //printf("\n acelerometroX: %f\n ", ACELX);
        //--------------------------------acelerometro en y-----------------------
        float ACELY;
        nukaworld=conver1(cadena[8],cadena[9],nukaworld);
        ACELY=nukaworld*a;
        //printf("\n acelerometroY: %f\n ", ACELY);
       //--------------------------------acelerometro en z-----------------------
        float ACELZ;
        nukaworld=conver1(cadena[10],cadena[11],nukaworld);
        ACELZ=nukaworld*a;
       // printf("\n acelerometroZ: %f\n ", ACELZ);
        //-------------------------giroscopio en x-------------------
        float GIRX;
        nukaworld=conver1(cadena[12],cadena[13],nukaworld);
        GIRX=nukaworld*gy;  //antes de gy era dps
       // printf("\n giroscopioX: %f\n ", GIRX);
        //--------------------------------------------------------
        //--------------------------------giroscopio en y-----------------------
        float GIRY;
        nukaworld=conver1(cadena[14],cadena[15],nukaworld);
        GIRY=nukaworld*gy;  //antes dps
       // printf("\n giroscopioY: %f\n ", GIRY);
        //-----------------------------------------------------
        //--------------------------------giroscopio en z-----------------------
        float GIRZ;
        nukaworld=conver1(cadena[16],cadena[17],nukaworld);
        GIRZ=nukaworld*gy;   //MAGNE?
        //printf("\n giroscopioZ: %f\n ", GIRZ);
    /********************************************************
    ==================BAROMETRO========================

     ******************************************************/
        automatron= (int)(cadena[20]);    //conversion de tipo a short
        float BAR;
        // LAST
        int y1 = 0;
        int y2 = 0;
        int y3 = 0;
        int y4 = cadena[18];
        //
        y3 = (cadena[20] >> 4) & 0x0000000f;
        y1 = (y4 << 12) & 0x000ff000;
        y2 = (cadena[19] << 4) & 0x00000ff0;
        farharbor2 = y1 | y2 | y3;
        BAR = farharbor2 * 0.01;

        // borrar
        // float BAR;
        // BAR = 0;

        //OLD
        // automatron & 0xf0;
        // automatron >>=4;
        //     //---------------
        // new_vegas1=(short)(cadena[19]);
        // new_vegas2=new_vegas1 & 0x0F;
        // new_vegas2 <<=4;
        //
        // farharbor = new_vegas2 | automatron;
        //
        // new_vegas3=new_vegas1& 0xf0;
        // new_vegas3 <<=4;
        // farharbor1= farharbor | new_vegas3;
        //     //------------------
        // vault_tec=(short)cadena[18];    //trama[18]
        // vault_tec1 = vault_tec & 0x0F;
        // vault_tec1 <<= 12;
        // farharbor2= vault_tec1 | farharbor1;   //se obtiene el byte alto
        // vault_tec2=vault_tec & 0xf0;
        // vault_tec2<<=12;
        // farharbor3= farharbor2 | vault_tec2;
        //
        // BAR=farharbor3/100;//*barometro;
        //printf("\n barometro %f\n",BAR);
    /*******************************************
    //------------------------temperatura 1-----------
    //--------------------------------------------------
    ********************************************/
        float TEM1;
        wasteland= (int)cadena[20];
        wasteland0=wasteland& 0x0f;
        wasteland0<<=8;
        wasteland1=(int)cadena[21];
        wasteland2=wasteland0 | wasteland1;
        TEM1 = wasteland2/100; // /0.01;
        //printf("\n T1 %f\n",TEM1);
    /*******************************************
    //------------------------temperatura 2----------
    //--------------------------------------------------
    ********************************************/
        float TEM2;
        brokensteel0 = (int)cadena[22];
        brokensteel0<<=8;
        brokensteel1= (int)cadena[23];

        brokensteel2 = brokensteel0 | brokensteel1;
        brokensteel3 = brokensteel2 & 0xfff0;
        brokensteel3>>=4;
        TEM2= (brokensteel3 * valor) / 10;
        //printf("\n T2: %f\n",TEM2);
    /*******************************************
    //------------------------temperatura 3-----------
    //--------------------------------------------------
    ********************************************/
        float TEM3;
        anchorage0 = (int)cadena[23];
        anchoragea=anchorage0<<8;
        anchorage1= (int)cadena[24];

        anchorage2 = anchoragea| anchorage1;

        anchorage3 = anchorage2 & 0x0FFF;

        TEM3= (anchorage3*valor) / 10;
        //printf("\n T3: %f\n",TEM3);
    /*******************************************
    //-------------------CORRIENTE ACS712----------
    //--------------------------------------------------
    ********************************************/
        float SC;
        point_lookout0 = (int)cadena[25];
        point_lookout0<<=8;
        point_lookout1= (int)cadena[26];
        point_lookout2 = point_lookout0 | point_lookout1;
        point_lookout3 = point_lookout2 & 0xFFF0;
        point_lookout3>>=4;
        SC= ((point_lookout3*relacion)-2.5)/sensibilidad;
        //printf("\n CORRIENTE: %f\n",SC);
    /*******************************************
    //---------------------SENSOR DE VOLTAJE-----------
    //--------------------------------------------------
    ********************************************/
        float SV;
        mothership0 = (int)cadena[26];
        mothership1 =mothership0<<8;
        mothership2 = (int)cadena[27];
        mothership3 = mothership1| mothership2;
        mothership4 = mothership3 & 0x0FFF;
        SV = (mothership4/100) ;

        //printf("\n VOLTAJE: %f\n",SV);
    /*******************************************
    //---------------------SESOR UV VML-----------
    //--------------------------------------------------
    ********************************************/

        float SUV;
        nukaworld=conver1(cadena[28],cadena[29],nukaworld);
        SUV=(nukaworld)/pasos;
        //printf("\n ultra: %f\n ", SUV);

    /************************************************
    ----------------------GPS--------------
    *************************************************/
        float GPSHOR;
        var = converhour(cadena[30], var);
        GPSHOR = var;
        //printf("\n hora: %f",GPSHOR);
        var = 0;
        float GPSMIN;
        var = convermin(cadena[30],cadena[31], var);
        GPSMIN = var;
        //printf(":min: %f",GPSMIN);
        var = 0;
        float GPSSEG;
        var = converseg(cadena[31],cadena[32], var);
        GPSSEG = var;
        //printf("seg: %f",GPSMIN);
        var = 0;
        float GPSDIA;
        var = converdia(cadena[32], var);
        GPSDIA = var;
        //printf("\n dia: %f ",GPSDIA);
        var = 0;
        float GPSMES;
        var = convermes(cadena[32],cadena[33], var);
        GPSMES = var;
        //printf(" mes: %f ",GPSMES);
        var = 0;
        float GPSANO;
        var = converanio(cadena[33], var);
        GPSANO = var + 2000;
        //printf(" a�o: %f \n",GPSANO);
        var = 0;
        float GPSALT;
        var = converaltura(cadena[34],cadena[35], var);
        GPSALT = var / 10;
        //printf("\n ALTURA: %f \n",GPSALT);
        var = 0;

        double GPSLAT;
        var = converlatlon(cadena[36],cadena[37],cadena[38],cadena[39], var);
        GPSLAT = var / 1000000;
        //printf("\n LATITUD: %f \n",GPSLAT);
        var = 0;

        float GPSLON;
        var = converlatlon(cadena[40],cadena[41],cadena[42],cadena[43], var);
        GPSLON = var / 1000000;
        //printf("\n LONGITUD: %f \n",GPSLON);
    /**************************************************************
          Almacenamiento y reenvio a programa principal de la ETC
    *************************************************/
              //float datos[25];
              datos[0]=MAGX;
              datos[1]=MAGY;
              datos[2]=MAGZ;
              datos[3]=ACELX;
              datos[4]=ACELY;
              datos[5]=ACELZ;
              datos[6]=GIRX;
              datos[7]=GIRY;
              datos[8]=GIRZ;
              datos[9]=BAR;
              datos[10]=TEM1;
              datos[11]=TEM2;
              datos[12]=TEM3;
              datos[13]=SC;
              datos[14]=SV;
              datos[15]=SUV;
              datos[16]=GPSHOR;
              datos[17]=GPSMIN;
              datos[18]=GPSSEG;
              datos[19]=GPSDIA;
              datos[20]=GPSMES;
              datos[21]=GPSANO;
              datos[22]=GPSALT;
              datos[23]=GPSLAT;
              datos[24]=GPSLON;
    //---FIN DEL PROGRAMA PRINCIPAL
}

void parse_package_2(unsigned char *cadena, int tam_in, float *datos, int tam_out){

    /*********************************************************
            PROGRAMA PRINCIPAL
    **********************************************************/

        //=============variables de los sensores================
        short nukaworld=0;   //variable intermedia para MAGX,MAGY,MAGZ,ACEL Y GIR
        short new_vegas1 = 0, new_vegas2 = 0, new_vegas3 = 0;
        short farharbor  = 0, farharbor1 = 0, farharbor2 = 0;
        int   farharbor3 = 0;
        short vault_tec  = 0, vault_tec1 = 0;  // variable intermedia para barometro (4 bits altos)
        int   vault_tec2 = 0;
        short wasteland  = 0,   wasteland0 = 0, wasteland1 = 0, wasteland2 = 0, wasteland3 = 0;
        short brokensteel0 = 0, brokensteel1 = 0,brokensteel2 = 0, brokensteel3 = 0;
        short anchorage0 = 0, anchorage1 = 0, anchorage2 = 0, anchorage3 = 0,anchoragea = 0;
        short point_lookout0 = 0;
        short point_lookout1 = 0;
        short point_lookout2 = 0;
        short point_lookout3 = 0;
        short mothership0 = 0;
        short mothership1 = 0;
        short mothership2 = 0;
        short mothership3 = 0;
        short mothership4 = 0;

        int automatron=0;

        const float magne = 0.0729927;      //configuracion de la ganancia del magnetometro
        const float dps=0.076335877;   //grados por segiundo?
        const float acce= 0.000061035;  //
        const float a = (9.81/2048.0);  //escalado a 16g
        const float gy = (250/32768.0);  //escalado a
        const float barometro = 0.008;  //conversirevon de hectopascales?
        const float valor = 0.080566;  // datos en binario * voltaje de referencia * escalamiento
        const float sensibilidad= 0.185;  //sensor de corriente
        const float relacion =  0.080566;  //datos en
        // const float rev=0.000244;   // voltaje de referencia del ADC = 1 v ; 1 binario = 0.000244 v
        const float pasos = 186.81818182 * 2;
    /********************************************************
    ==================MAGNETOMETRO HMC5883L=======================
     ******************************************************/
    //-------------------------magx-------------------

        float MAGX;
        float var;
        nukaworld = conver1(cadena[0], cadena[1], nukaworld);
        MAGX = nukaworld * magne;
        //printf("\n magnetometroX: %f\n", MAGX);

    //--------------------------------magy-----------------------
        float MAGY;
        nukaworld=conver1(cadena[2],cadena[3],nukaworld);
        MAGY=nukaworld*magne;
        //printf("\n magnetometroY: %f\n", MAGY);
            // printf("magnetometro: %f\n ", magy);
    //--------------------------------magz-----------------------
        float MAGZ;
        nukaworld=conver1(cadena[4],cadena[5],nukaworld);
        MAGZ=nukaworld*magne;
        //printf("\n magnetometroZ: %f\n", MAGZ);

    /********************************************************
    ==================ACEL-GYR - MPU6050========================
    ******************************************************/
      //-------------------------acelerometro en x-------------------
        float ACELX;
        nukaworld=conver1(cadena[6],cadena[7],nukaworld);
        ACELX=nukaworld*a;
        //printf("\n acelerometroX: %f\n ", ACELX);
        //--------------------------------acelerometro en y-----------------------
        float ACELY;
        nukaworld=conver1(cadena[8],cadena[9],nukaworld);
        ACELY=nukaworld*a;
        // printf("\n acelerometroY: %f\n ", ACELY);
       //--------------------------------acelerometro en z-----------------------
        float ACELZ;
        nukaworld=conver1(cadena[10],cadena[11],nukaworld);
        ACELZ=nukaworld*a;
       // printf("\n acelerometroZ: %f\n ", ACELZ);
        //-------------------------giroscopio en x-------------------
        float GIRX;
        nukaworld=conver1(cadena[12],cadena[13],nukaworld);
        GIRX=nukaworld*gy;  //antes de gy era dps
        //printf("\n giroscopioX: %f\n ", GIRX);
        //--------------------------------------------------------
        //--------------------------------giroscopio en y-----------------------
        float GIRY;
        nukaworld=conver1(cadena[14],cadena[15],nukaworld);
        GIRY=nukaworld*gy;  //antes dps
        //printf("\n giroscopioY: %f\n ", GIRY);
        //-----------------------------------------------------
        //--------------------------------giroscopio en z-----------------------
        float GIRZ;
        nukaworld=conver1(cadena[16],cadena[17],nukaworld);
        GIRZ=nukaworld*gy;   //MAGNE?
        //printf("\n giroscopioZ: %f\n ", GIRZ);

    /********************************************************
    ==================BAROMETRO========================

     ******************************************************/
        // LAST
        // automatron= (int)(cadena[20]);    //conversion de tipo a short
        // float BAR;
        // u_int32_t y1;
        //  y2;
        // u_int32_t y3;
        // u_int32_t y4 = cadena[18];
        //
        // farharbor = (cadena[20] >> 4) & 0x0000000f;
        // y1 = (y4 << 12) & 0x000ff000;
        // y2 = (cadena[19] << 4) & 0x00000ffO;
        // farharbor2 = y1 | y2 | farharbor1;
        // BAR = farharbor2 * 0.01;

        // borrar
        float BAR;
        BAR = 0;

        // OLD
        // automatron & 0xf0;
        // automatron >>=4;
        //     //---------------
        // new_vegas1=(short)(cadena[19]);
        // new_vegas2=new_vegas1 & 0x0F;
        // new_vegas2 <<=4;
        //
        // farharbor = new_vegas2 | automatron;
        //
        // new_vegas3=new_vegas1& 0xf0;
        // new_vegas3 <<=4;
        //
        // farharbor1= farharbor | new_vegas3;
        //     //------------------
        // vault_tec=(short)cadena[18];    //trama[18]
        // vault_tec1 = vault_tec & 0x0F;
        // vault_tec1 <<= 12;
        // farharbor2= vault_tec1 | farharbor1;   //se obtiene el byte alto
        //
        // vault_tec2=vault_tec & 0xf0;
        // vault_tec2<<=12;
        //
        // farharbor3= farharbor2 | vault_tec2;
        //
        // BAR=farharbor3/100;//*barometro;
        // printf("\n barometro %f\n",BAR);

    /*******************************************
    //-------------------CORRIENTE ACS712----------
    //--------------------------------------------------
    ********************************************/
        float SC;
        point_lookout0 = (int)cadena[20];
        point_lookout0<<=8;
        point_lookout1= (int)cadena[21];

        point_lookout2 = point_lookout0 | point_lookout1;
        point_lookout3 = point_lookout2 & 0xfff0;
        point_lookout3>>=4;
        SC= ((point_lookout3*relacion)-2.5)/sensibilidad;
        // printf("\n CORRIENTE: %f\n",SC);

    /**------------ALTURA 1----------------------*/
        float ALT1;

        nukaworld=conver1(cadena[22],cadena[23],nukaworld);
        ALT1=nukaworld*0.01;
        // printf("ALTURA1: %f\n ", ALT1);

    /**------------ALTURA 2---------------------*/

        float ALT2;
        nukaworld=conver1(cadena[24],cadena[25],nukaworld);
        ALT2=nukaworld*0.01;
        // printf("ALTURA2: %f\n ", ALT2);
    /**------------TIMER---------------------*/
        float TIMER;
        nukaworld=conver1(cadena[26],cadena[27],nukaworld);
        TIMER=nukaworld*0.01;
        // printf("TIMER: %f\n ", TIMER);
    /**------------RELLENO---------------------*/

        float FILL;
        nukaworld=conver1(cadena[28],cadena[29],nukaworld);
        FILL=nukaworld*0;
        // printf("RELLENO: %f\n ", FILL);

    /************************************************
    ----------------------GPS--------------
    *************************************************/
    float GPSHOR;
    var = converhour(cadena[30], var);
    GPSHOR = var;
    // printf("\n hora: %f",GPSHOR);
    var = 0;
    float GPSMIN;
    var = convermin(cadena[30],cadena[31], var);
    GPSMIN = var;
    // printf(":min: %f",GPSMIN);
    var = 0;
    float GPSSEG;
    var = converseg(cadena[31],cadena[32], var);
    GPSSEG = var;
    // printf("seg: %f",GPSMIN);
    var = 0;
    float GPSDIA;
    var = converdia(cadena[32], var);
    GPSDIA = var;
    // printf("\n dia: %f ",GPSDIA);
    var = 0;
    float GPSMES;
    var = convermes(cadena[32],cadena[33], var);
    GPSMES = var;
    // printf(" mes: %f ",GPSMES);
    var = 0;
    float GPSANO;
    var = converanio(cadena[33], var);
    GPSANO = var + 2000;
    // printf(" a�o: %f \n",GPSANO);
    var = 0;
    float GPSALT;
    var = converaltura(cadena[34],cadena[35], var);
    GPSALT = var / 10;
    // printf("\n ALTURA: %f \n",GPSALT);
    var = 0;

    double GPSLAT;

    var = converlatlon(cadena[36],cadena[37],cadena[38],cadena[39], var);
    GPSLAT = var;
    // printf("\n LATITUD: %f \n",GPSLAT);
    var = 0;

    float GPSLON;
    var = converlatlon(cadena[40],cadena[41],cadena[42],cadena[43], var);
    GPSLON = var;
    // printf("\n LONGITUD: %f \n",GPSLON);


    //float datos[24];
              datos[0]=MAGX;
              datos[1]=MAGY;
              datos[2]=MAGZ;
              datos[3]=ACELX;
              datos[4]=ACELY;
              datos[5]=ACELZ;
              datos[6]=GIRX;
              datos[7]=GIRY;
              datos[8]=GIRZ;
              datos[9]=BAR;
              datos[10]=SC;
              datos[11]=ALT1;
              datos[12]=ALT2;
              datos[13]=TIMER;
              datos[14]=FILL;
              datos[15]=GPSHOR;
              datos[16]=GPSMIN;
              datos[17]=GPSSEG;
              datos[18]=GPSDIA;
              datos[19]=GPSMES;
              datos[20]=GPSANO;
              datos[21]=GPSALT;
              datos[22]=GPSLAT;
              datos[23]=GPSLON;
              /**
              datos[14]=GPSHOR;
              datos[15]=GPSMIN;
              datos[16]=GPSSEG;
              datos[17]=GPSDIA;
              datos[18]=GPSMES;
              datos[19]=GPSANO;
              datos[20]=GPSALT;
              datos[21]=GPSLAT;
              datos[22]=GPSLON;
              **/



}

short converhour(unsigned char x, short out ){
    short v1;
    v1 = (short) x;
    out = v1>>3;  //dezplazamiento de los bits de la variable hora.
    return out;
}
short convermin(unsigned char x,unsigned char y, short out){
    short v1,v2;
    v1 = (short) x;
    v2 = (short) y;
    v1 <<= 3;
    v2 >>= 5;
    out = (v1 | v2) & 0x3F;
    return out;
}
short converseg(unsigned char x, unsigned char y, short out){
    short v1,v2;
    v1 = (short) x;
    //printf("\n [30] %i",v1);
    v2 = (short) y;
    //printf("\n [30] %i",v1);
    v1 <<= 1;
    v2 >>= 7;
    out = (v1 | v2) & 0x3F;
    return out;
}
short converdia(unsigned char x, short out){
    short v1;
    v1 = (short) x;
    v1 >>= 2;
    out = v1 & 0x1F;
    return out;
}
short convermes(unsigned char x,unsigned char y, short out){
    short v1,v2;
    v1 = (short) x;
    v2 = (short) y;
    v1 <<= 2;
    v2 >>= 6;
    out = (v1 | v2) & 0x0F;
    return out;
}
short converanio(unsigned char x, short out){
    short v1;
    v1 = (short) x;
    out = v1  & 0x3F;
    return out;
}
int converaltura(unsigned char x,unsigned char y, int out){
    int v1,v2;
    v1 =  (x << 8);  //se recorre 8 bits para el bytes altos
    v2 =  y & 0x00FF;  //se hace un mask para el byte bajos
    out = (v1 | v2);
    return out;
}
double converlatlon(int h,int hm,int lm,int l,double salida ){
    int vh, vhm, vlm, vl;
    //double d;
    vh = (int) h;
    //printf("\n vh:%i",vh);
    vh = (vh << 24); //&0xFF000000; //desplazamiento de 24 bits para tener el byte mas significativo
    //printf("\n vh<<24:%i",vh);
    vhm = (int) hm;
    //printf("\n vhm:%i",vhm);
    vhm = (vhm<<16) & 0x00FF0000; //desplazamiento de 16 bits para tener el byte medio mas significativo
    //printf("\n vhm<<16:%i",vhm);
    vlm = (int) lm;
    //printf("\n vLM:%i",vlm);
    vlm = (vlm << 8) & 0x0000FF00; //desplazamiento de 24 bits para tener el byte mas significativo
    //printf("\n vlm:<<8;%i",vlm);
    vl = (int) l;
    //printf("\n vL:%i",vl);
    vl = vl & 0x000000FF; //desplazamiento de 16 bits para tener el byte medio mas significativo
    salida = (vh | vhm | vlm | vl);  // concatenacion
    return salida;
}

int conver1 (int cad1,int cad2,int salida)
{
        int valor,valor2;
        //short massfusion=58;
        valor = (int) cad1;   //se convierte (casting) de entero a short
        //printf("\n [A] %i",valor);
        valor2=(int) cad2;  //           //
        //printf(" [B]:%i ",valor2);
        int valor3 = valor << 8;    // desplazamiento de 8 bits a la izquierda        //   valor = valor << 8;
        //printf(" [A<<8].:%i ",valor3);
        salida = valor3 | valor2;     // operacion or de bit a bit
        //printf("salida = %i",salida);
        return salida;
}


void print_float_array(float *buf, int count){
    for (size_t i = 0; i < count; i++) {
        printf("%.8f, ", buf[i]);
    }
}
