#include <stdio.h>
#include <math.h>
//#include <memory.h>
#include <stdlib.h>

#include <inc/spatial_domain.h>

int SDF_computeHistogram(Image *ptr, Histogram *h, char channel)
{
    int  i, j, temp;
    int *dummyPtr;

    if((ptr->bpp != 8 && ptr->bpp != 24 &&
        ptr->bpp != 32) ||
       (ptr->bpp == 8 && channel != 'a') || (ptr->bpp == 24 && channel == 'a'))
    {
        return (-1);
    }

    if(ptr->bpp == 24 || ptr->bpp == 32)
    {
        switch(channel) {
            case 'b':   dummyPtr = ptr->bdata; break;
            case 'g':   dummyPtr = ptr->gdata; break;
            case 'r':   dummyPtr = ptr->rdata; break;
            case 'a':   if(ptr->bpp != 32)
                {
                    return -1;
                }
                else
                {
                    dummyPtr = ptr->adata;
                    break;
                }
            default: return 0;
        }
    }

    if(ptr->bpp == 8)
    {
        if(channel != 'a')
        {
            return 0;
        }
        else
        {
            dummyPtr = ptr->adata;
        }
    }

    for(i = 0; i <= 255; i++) {
        h->hist[i] = 0;
    }

    for(i = 0; i <= ptr->rows - 1; i++) {
        for(j = 0; j <= ptr->cols - 1; j++) {
            temp = *(dummyPtr + (i * ptr->cols) + j);
            temp = (temp < 0) ? 0 : temp;
            temp = (temp > 255) ? 255 : temp;
            h->hist[temp]++;
        }
    }

    return 1;
}

