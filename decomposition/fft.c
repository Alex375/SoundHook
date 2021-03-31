
//
// Created by Noé Bonne on 3/11/21.
//
// FAST FOURIER TRANSFORM
// Exemple de la FFT sur la fonction f(x) = x*(1-x)

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "/usr/local/Cellar/fftw/3.3.9/include/fftw3.h"

#define RATIO_DETECT_SPIKE 3
#define LEN_DETECT_SPIKE 3
#define NB_MAX 10

void treatOut(double* outMagn, int n_out, double time)
{
    /*int inc = 1;
    for (int i = 1; i < n_out; ++i)
    {
        if((outMagn[i] >= outMagn[i - 1]) != inc)
            if (inc == 1)
            {
                double low = outMagn[i]+1;
                if (i-LEN_DETECT_SPIKE >= 0)
                    low = outMagn[i-LEN_DETECT_SPIKE];

                double high = outMagn[i]+1;
                if (i+LEN_DETECT_SPIKE < n_out)
                    high = outMagn[i+LEN_DETECT_SPIKE];
                if(low * RATIO_DETECT_SPIKE < outMagn[i] && high * RATIO_DETECT_SPIKE < outMagn[i])
                {

                    printf("We found a new dominating frequence : %f hertz", i / time);

                    if(i / time < 100 || i / time > 10000)
                        printf("   (sus) ");
                    printf("\n");

                }
            }
            inc = !inc;
    }*/
    double fullMax = 0;
    int maxI = 0;
    for (int i = 0; i < NB_MAX; ++i) {
        for (int j = 0; j < n_out; ++j)
        {
            if (outMagn[j] > outMagn[maxI])
                maxI = j;
        }
        if (i == 0)
            fullMax = outMagn[maxI];
        if(outMagn[maxI] * RATIO_DETECT_SPIKE < fullMax)
            break;



        int f = floor(maxI / time + 0.5);

        printf("The dominating frequence is : %i hertz (%i in tab)", f, maxI);

        if(f < 100 || f > 10000)
            printf("   (sus) ");
        printf("\n");

        for (int j = -LEN_DETECT_SPIKE; j <= LEN_DETECT_SPIKE; ++j) {
            outMagn[maxI + j] = 0;
        }


    }


}



// fft init
// real numbers in
int fft(int * decoded, int sizeIn, double time)
{
    double * in  = (double*)fftw_malloc(sizeof(double) * sizeIn);
    int n_out = ((sizeIn/2)+1);
// complex numbers out
    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n_out);

    /* false in fill
    for (int i = 0; i < sizeIn; ++i)
    {
        in[i] = sin(i*2*M_PI/2.2 + M_PI/2) * 10;

    }*/
    for (int i = 0; i < sizeIn; ++i)
    {
        in[i] = ((double)decoded[i]) ;
        //printf("%f\n", in[i]);
    }


    fftw_plan plan_forward;

    // real in and complex out
    plan_forward = fftw_plan_dft_r2c_1d ( sizeIn, in, out, FFTW_ESTIMATE );

    // do it
    fftw_execute ( plan_forward );


    double * outMagn = malloc(sizeof(double) * n_out);
    for (int i = 0; i < n_out; ++i)
    {
        double mag = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        outMagn[i] = mag;
    }

    double max = 0;
    for (int j = 0; j < n_out; ++j)
    {
        if (outMagn[j] > max)
            max = outMagn[j];
    }

    for (int i = 0; i < n_out; ++i)
    {
        outMagn[i] = outMagn[i]/max*1000;
    }

    for (int i = 1990*3; i < 3100*3; ++i)
    {
        //printf("Magn Out %i : %f\n", i, outMagn[i]);

    }



    treatOut(outMagn, n_out, time);




    fftw_destroy_plan(plan_forward);
    fftw_free(in); fftw_free(out);
    free(outMagn);
    return 0;
}
/*

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  swap(a,b)  norm=(a); (a)=(b); (b)=norm

//reel[] et imag[i] sont la liste des réelles et des imaginaires
// sign = 1 donne la transformée de Fourier
// sign = -1 donne la transformée de Fourier inverse

void fft(double *reel, double *imag, int log2n, int sign) {

    int n, m, m2, i, j, k, l;
    double  c1, c2, norm, norm2, cphi, sphi;

    n = 1<<log2n;

     Inversement des bits
    for(i=0; i<n; i++) {

        for(j=log2n-1, m=0, k=i; j>=0; j--, k>>=1) m += (k&1)<<j;

        if(m>i) {
            swap(reel[i],reel[m]);
            swap(imag[i],imag[m]);
        }
    }

     normalisation de la transformée de Fourier
    norm = 1.0/sqrt((double)n);
    for(i=0; i<n ;i++) {
        reel[i] *= norm;
        imag[i] *= norm;
    }

     calcul de la FFT
    for(j=0; j < log2n; j++) {
        m = 1<<j;  m2 = 2*m;
        c1 = 1.0;
        c2 = 0.0;
        cphi = cos(sign*2.0*M_PI/((double)m2));
        sphi = sin(sign*2.0*M_PI/((double)m2));
        for(k=0; k<m; k++) {
            for(i=k; i<n; i+=m2) {
                l = i + m;
                norm  = c1*reel[l] - c2*imag[l];
                norm2 = c1*imag[l] + c2*reel[l];
                reel[l] = reel[i] - norm;
                imag[l] = imag[i] - norm2;
                reel[i] += norm;
                imag[i] += norm2;
            }
            norm  = c1*cphi - c2*sphi; // Calcul de exp(2 pi k/m) avec
            norm2 = c1*sphi + c2*cphi; // le théorème d'addition
            c1 = norm;  c2 = norm2;
        }
    }

}
int main(int argc, char *argv[])
{
    int n=16, k=4, i;
    double re[16], im[16];
    double h,x;
    FILE *fichier;
    fichier = fopen("FFT.dat","w");

    h = 1.0/(n-1);

    printf("Calcul des Points:\n");
    for(i=0; i<n; i++) {
        x = h*i;
        re[i] = x*(1-x);
        im[i] = 0;

        printf(" % lf %+lf i\n",re[i],im[i]);

    }

    fft(re,im,k,+1);
    printf("Transformation:\n");
    for(i=0; i<n; i++) {
        printf(" % lf %+lf i\n",re[i],im[i]);
        fprintf(fichier,"%d %lf %lf\n",i,re[i],im[i]);//on enregistre dans FFT.dat
    }
    fclose(fichier);

    fft(re,im,k,-1);
    printf("FFT inverse:\n");
    for(i=0; i<n; i++) {
        printf(" % lf %+lf i\n",re[i],im[i]);
    }
    system("PAUSE");
    return 0;
}
*/