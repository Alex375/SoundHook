//
// Created by Alexandre Josien on 20/06/2021.
//

/*void treatOut(double* outMagn, int n_out, double time, fftw_complex* out)
{
    int inc = 1;
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

    //////////////

    /*
    int fullMaxI = 0;
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


        int f = floor(maxI / time + 0.5);
        if(f < MIN_F || outMagn[maxI] * RATIO_DETECT_SPIKE < fullMax)
        {
            iSpikes[i] = -1;
            break;
        }


        iSpikes[i] = maxI;


        printf("The dominating frequence is : %i hertz (%i in tab) = %f", f, maxI, outMagn[maxI]);

        if(f < 70 || f > 4000)
            printf("   (sus) ");
        printf("\n");

        for (int j = -LEN_DETECT_SPIKE; j <= LEN_DETECT_SPIKE; ++j) {
            outMagn[maxI + j] = 0;
        }


    }*/