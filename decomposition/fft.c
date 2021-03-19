<<<<<<< Updated upstream
//
// Created by Noé Bonne on 3/11/21.
//
// FAST FOURIER TRANSFORM
// Exemple de la FFT sur la fonction f(x) = x*(1-x)
=======
#include <stdio.h>
#include "/usr/local/Cellar/fftw/3.3.9/include/fftw3.h"



// fft init
// real numbers in
int fft()
{
    int buffer_size = 16;

    double * in  = (double*)fftw_malloc(sizeof(double) * buffer_size);
    int n_out = ((buffer_size/2)+1);
// complex numbers out
    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n_out);
    int current_entry = 0;
    int filled = 0;

    printf("ffting");
    return 0;
}
>>>>>>> Stashed changes

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

    /* Inversement des bits */
    for(i=0; i<n; i++) {

        for(j=log2n-1, m=0, k=i; j>=0; j--, k>>=1) m += (k&1)<<j;

        if(m>i) {
            swap(reel[i],reel[m]);
            swap(imag[i],imag[m]);
        }
    }

    /* normalisation de la transformée de Fourier */
    norm = 1.0/sqrt((double)n);
    for(i=0; i<n ;i++) {
        reel[i] *= norm;
        imag[i] *= norm;
    }

    /* calcul de la FFT */
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
