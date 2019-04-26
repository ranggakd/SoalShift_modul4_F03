#include<stdio.h>
#include<string.h>

int main()
{
    char cip[189];
    strcpy(cip,"qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0");
    char contoh[16];
    strcpy(contoh," A_");
    int counter=strlen(contoh);
    char kar;
    //enkrip
    // printf("%d\n",counter);
    for(int i = 0; i < counter; i++)
    {
        kar = contoh[i];
        // printf("%c\n",kar);
        for(int j = 0; j<111 ; j++)
        {
            // printf("%c_",cip[j]);
            if (kar == cip[j])
            {
                kar = cip[j+17];
                contoh[i]=kar;
                // printf("contoh%c\n",contoh[i]);
                break;
            }
        }
    }
    //dekrip
    printf("%s\n",contoh);
    for(int i = counter-1; i >= 0; i--)
    {
        kar = contoh[i];
        // printf("%c\n",kar);
        for(int j = 111-1; j >=0 ; j--)
        {
            // printf("%c_",cip[j]);
            if (kar == cip[j])
            {
                kar = cip[j-17];
                contoh[i]=kar;
                // printf("contoh%c\n",contoh[i]);
                break;
            }
        }
    }
    printf("%s\n",contoh);
    return 0;
}
/*
n,nsbZ]wio/QBE#
*/