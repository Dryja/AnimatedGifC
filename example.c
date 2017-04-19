#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "gifsave.h"


#define WIDTH        1000
#define HEIGHT       1000
#define NUMCOLORS      5  //number of colors to be definied  
#define COLORRES       8  /* number of bits for each primary color */
#define FILENAME "example.gif"

/* the image buffer */
static unsigned char Screen[WIDTH][HEIGHT];



/**************************************************************************
 *                                                                        *
 *                   P R I V A T E    F U N C T I O N S                   *
 *                                                                        *
 **************************************************************************/



/*-------------------------------------------------------------------------
 *
 *  NAME          GetPixel
 *
 *  DESCRIPTION   Callback function fetching a pixel value from the buffer.
 *
 *  INPUT         x,y     the location of the pixel
 *
 *  RETURNS       Pixel value, in the range [0, NUMCOLORS).
 */
static int GetPixel(int x, int y)
{
    return Screen[x][y];
}



/*-------------------------------------------------------------------------
 *
 *  NAME          DrawImage
 *
 *  DESCRIPTION   Produces some output inn the image buffer.
 */
static void
DrawColor(int color)
{
    int i,j;
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT;j++){
            Screen[i][j] = color;
        }
    }

}

int
main(void)
{
    /* create and set up the GIF-file */
    GIF_Create(FILENAME, WIDTH, HEIGHT, NUMCOLORS, COLORRES);
    /* define a few colors matching the pixel values used */
    GIF_SetColor(0, 0, 0, 0);        /* black, the background */
    GIF_SetColor(1, 255, 0, 0);      /* red */
    GIF_SetColor(2, 0, 255, 0);      /* green */
    GIF_SetColor(3, 0, 0, 255);      /* blue */
    GIF_SetColor(4, 255, 255, 255);  /* white */
    /* store the image, using the GetPixel function to extract pixel values */
    GIF_WriteHeader(0);
    DrawColor(4);
    GIF_AddFrame(0, 0, -1, -1,10, GetPixel);
    DrawColor(2);
    GIF_AddFrame(0, 0, -1, -1,10, GetPixel);
    DrawColor(3);
    GIF_AddFrame(0, 0, -1, -1,10, GetPixel);
    GIF_Close();
    return 0;
}
