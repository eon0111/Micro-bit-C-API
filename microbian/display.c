/* display.c */
/* Copyright (c) 2020 J. M. Spivey */

/* A simple driver for the micro:bit LEDs with the same interface on
V1 and V2. */

#include "microbian.h"
#include "hardware.h"
#include <string.h>

/* Note that blank is not the same as an image that is all zeroes,
because it has the row bits set.  Copying blank and then setting
(actually, clearing) column bits for each row results in an image 
that displays properly. */

/* blank -- empty image */
const image blank =
    IMAGE(0,0,0,0,0,
          0,0,0,0,0,
          0,0,0,0,0,
          0,0,0,0,0,
          0,0,0,0,0);

/* image_clear -- set image to blank */
void image_clear(image img)
{
    memcpy(img, blank, sizeof(image));
}

/* PAIR, etc. -- encode a pair of integers in one integer */
#define PAIR(x, y) (((x) << 5) | (y))
#define XPART(p) ((p) >> 5)
#define YPART(p) ((p) & 0x1f)

#ifdef UBIT_V1
#define PIX(i, j)  PAIR(i-1, j+3)

/* img_map -- map of logical row and column bits for each physical pixel */
static unsigned img_map[5][5] = {
    { PIX(3,3), PIX(2,7), PIX(3,1), PIX(2,6), PIX(3,2) },
    { PIX(1,8), PIX(1,7), PIX(1,6), PIX(1,5), PIX(1,4) },
    { PIX(2,2), PIX(1,9), PIX(2,3), PIX(3,9), PIX(2,1) },
    { PIX(3,4), PIX(3,5), PIX(3,6), PIX(3,7), PIX(3,8) },
    { PIX(1,1), PIX(2,4), PIX(1,2), PIX(2,5), PIX(1,3) }
};

/* map_pixel -- find logical row and column for a pixel */
static unsigned map_pixel(int x, int y)
{
    return img_map[y][x];
}
#endif

#ifdef UBIT_V2
/* img_col -- map of column bits for each physical column */
static const unsigned img_col[] = {
    COL1, COL2, COL3, COL4, COL5    // NOTE: quiero entender que el tío se ha inventado un mapeo en el que el 5o bit más significativo indica el puerto del GPIO, 0 o 1 y, el resto de bits (menos significativos), el pin en ese puerto
};

/* map_pixel -- find logical row and column for a pixel */
static unsigned map_pixel(int x, int y)
{
    /* Each row is represented by two words for the two GPIO registers. */
    unsigned col = img_col[x];          // NOTE: obtiene su mapeo de la columna X
    int index = 2*(4-y) + XPART(col);   // NOTE: con XPART(col) lo que hace es recuperar el bit que indica el puerto del GPIO, porque vuelve a hacer un shift de 5 bits hacia la dcha. Con el 2*(4-y) va generando los múltiplos de 2 en el rango [0, 8], que son 5 números, es decir 5 índices para algo que no sé qué es aún FIXME:
    int bit = YPART(col);               // NOTE: con YPART(col) lo que hace es recuperar el índice del pin dentro del puerto
    return PAIR(index, bit);            // NOTE: retorna un entero compuesto, en su codificación binaria, por: puerto[b31-b6] y pin[b5-b0]
    /* Could optimise to ((4-y) << 6) | img_col[x]. */
}
#endif

/* image_set -- switch on a single pixel in an image */
void image_set(int x, int y, image img)
{
    if (x < 0 || x >= 5 || y < 0 || y >= 5) return;
    unsigned p = map_pixel(x, y);   // NOTE: el mapeo que ha escogido es el siguiente: TODO:
    CLR_BIT(img[XPART(p)], YPART(p));   // NOTE: en el bit 5 va codificado el puerto del GPIO, 0 o 1, que es el primer parámetro de la macro CLR_BIT
}

/* NOTE: la librería no disponía de una función para apagar un LED en una imagen */
void image_clear_led(int x, int y, image img)
{
    if (x < 0 || x >= 5 || y < 0 || y >= 5) return;
    unsigned p = map_pixel(x, y);
    SET_BIT(img[XPART(p)], YPART(p));
}

/* display_image is a shared variable between the client and the
display driver task, but it is read-only in the task.  Partial updates
don't really matter, because they will cause only a momentary glitch in
the display when it is changing anyway. */

/* display_image -- shared variable for currently displayed image */
static image display_image;

/* display_task -- device driver for LED display */
void display_task(int dummy)
{
    int n = 0;

#ifdef UBIT_V1
    GPIO.DIRSET = LED_MASK;
    timer_pulse(5);             /* 5ms x 3 = 15ms updates */
#endif
    
#ifdef UBIT_V2
    /* NOTE: limpia el display (apaga todos los LEDs) */
    GPIO0.DIRSET = LED_MASK0;
    GPIO1.DIRSET = LED_MASK1;
    
    gpio_drive(ROW1, GPIO_DRIVE_S0H1);
    gpio_drive(ROW2, GPIO_DRIVE_S0H1);
    gpio_drive(ROW3, GPIO_DRIVE_S0H1);
    gpio_drive(ROW4, GPIO_DRIVE_S0H1);
    gpio_drive(ROW5, GPIO_DRIVE_S0H1);

    timer_pulse(3);             /* 3ms * 5 = 15ms updates */
#endif

    image_clear(display_image);
    priority(P_HIGH);

    while (1) {
        /* Carefully change LED bits and leave other bits alone */
#ifdef UBIT_V1
        GPIO.OUTCLR = 0xfff0;
        GPIO.OUTSET = display_image[n++];
        if (n == 3) n = 0;
#endif

#ifdef UBIT_V2
        /* To avoid ghosting, clear GPIO0 (which contains the row bits)
           first and set it last. */
        /* NOTE: en el OUTCLR de los GPIO indica que las señales de todas las
         * filas (ROWx) y todas las columnas (COLx) deberán tener un valor de
         * voltaje bajo (LOW), es decir, que permanecerán "apagadas" */
        GPIO0.OUTCLR = LED_MASK0;
        GPIO1.OUTCLR = LED_MASK1;
        GPIO1.OUTSET = display_image[n+1];
        GPIO0.OUTSET = display_image[n];
        /* NOTE: el funcionamiento de esta tarea puede resumirse en:
         * 1. apaga todo
         * 2. activa fila y columna para LED en posición x,y
         * 3. repite */
        n += 2;
        if (n == 10) n = 0; /* NOTE: en cada iteración muestra una fila de la imagen */
#endif

        receive(PING, NULL);
    }
}

/* display_show -- set display from image */
void display_show(const image img)
{
    memcpy(display_image, img, sizeof(image));
}

/* display_init -- start display driver task */
void display_init(void)
{
    start("Display", display_task, 0, STACK);
}
