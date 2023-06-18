/**
 * @file png2string.c
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief Programa que obtiene el equivalente numérico, según el formato empleado
 * para las imágenes por la librería "ubit", de una imagen en formato PNG con unas
 * dimensiones de 5 por 5 píxeles
 * @version TODO:
 * @date TODO:
 * 
 */

#include <stdio.h>
#include <png.h>
#include <stdlib.h>
#include <string.h>

/* El nombre que recibe por defecto el fichero de resultados */
#define NOM_FICH_IMAGEN_TXT_DEF "resultado.txt"

/* La dimensión de la matriz de LEDs de la placa */
#define DIM 5

/* Mensaje de ayuda sobre la utilización de la aplicación */
#define MSJ_AYUDA "Uso: png2string -i {imágenes} -f <fich. salida>\n\n\
    -i  {imágenes}      Las imágenes que deberá procesar la aplicación\n\
    -f  <fich. salida>  El fichero donde la aplicación depositará el resultado de la conversión\n\
    -h                  Muestra la ayuda\n\n\
Ejemplo:\n\n\
    $ png2string -i imagen_1 ... imagen_N -f conversion.txt\n"

/**
 * @brief Programa principal.
 * 
 */
void
main(int argc, char *argv[])
{
    png_structp datos_imagen;   /* La información de cada píxel */
    png_infop info_imagen;      /* La información sobre el fichero de imagen */
    png_bytepp filas;

    FILE *fich_imagen, *fich_imagen_txt;
    char *nom_fich_imagen_txt = NOM_FICH_IMAGEN_TXT_DEF, *nom_fich_imagen_png;
    int i, j, k, lista_png_ini = -1;

    /* Busca el flag de ayuda (-h) y, si lo encuentra, no se procesa ninguna
     * imagen y el programa termina. También busca el flag con el que se indica
     * el fichero de salida (-f) para que más adelante se depositen los resultados
     * de las conversiones en el fichero adecuado */
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            printf("%s\n", MSJ_AYUDA);
            exit(0);
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            if (strcmp("-i", argv[(i + 1) % argc]) == 0 ||
                strcmp("-h", argv[(i + 1) % argc]) == 0 || i == argc - 1)
            {
                printf("[!] png2string: error: no indicó el nombre del fichero de salida.\n");
                exit(-1);
            }

            nom_fich_imagen_txt = (char *)malloc(strlen(argv[i + 1]));
            strcpy(nom_fich_imagen_txt, argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            if (strcmp("-f", argv[(i + 1) % argc]) == 0 ||
                strcmp("-h", argv[(i + 1) % argc]) == 0 || i == argc - 1)
            {
                printf("[!] png2string: error: no indicó ningún fichero de imagen.\n");
                exit(-1);
            }

            /* No comienza a procesar las imágenes en este punto de la ejecución
             * puesto que el usuario podría haber indicado el nombre del fichero
             * de resultados después de la lista de imágenes a procesar */
            lista_png_ini = i + 1;
        }
    }

    /* Comprueba que se ha indicado algún fichero de imagen con el flag -i */
    if (lista_png_ini == -1)
    {
        printf("[!] png2string: error: no indicó ningún fichero de imagen.\n");
        exit(-1);
    }

    /* Abre el fichero de resultados */
    fich_imagen_txt = fopen(nom_fich_imagen_txt, "w");
    if (!fich_imagen_txt)
    {
        printf("[!] error: no se pudo abrir \"%s\"\n", nom_fich_imagen_txt);
        exit(-1);
    }

    /* Procesa el listado de imágenes indicado por el usuario */
    k = lista_png_ini;
    while (strcmp(argv[(k + 1) % argc], "-f") != 0 && k < argc)
    {
        nom_fich_imagen_png = argv[k];
        printf("[*] Procesando \"%s\"\n", nom_fich_imagen_png);

        /* Abrimos el descriptor del fichero de imagen */
        fich_imagen = fopen(nom_fich_imagen_png, "rb");
        if (!fich_imagen)
        {
            printf("[!] error: no se pudo abrir \"%s\"\n", nom_fich_imagen_png);
            exit(-1);
        }

        datos_imagen = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        info_imagen = png_create_info_struct(datos_imagen);

        /* Con "png_set_palette_to_rgb" conseguimos que la información de la
         * imagen se lea como datos RGB */
        png_set_palette_to_rgb(datos_imagen);

        /* Establecemos el "puente" entre el descriptor del fichero de imagen y
         * la estructura donde serán leídos sus datos tras ser convertidos a info.
         * RGB */
        png_init_io(datos_imagen, fich_imagen);

        /* Leemos el fichero de imagen */
        png_read_png(datos_imagen, info_imagen, PNG_TRANSFORM_IDENTITY, NULL);
        filas = png_get_rows(datos_imagen, info_imagen);

        /* Construimos el array correspondiente a la imagen actual */
        fprintf(fich_imagen_txt, "\"");
        for (i = 0; i < DIM; i++)
        {
            for (j = 0; j < DIM * 3; j += 3)
            {
                fprintf(fich_imagen_txt, (!filas[i][j]) ? "1" : "0");
            }
        
        }
        fprintf(fich_imagen_txt, "\",    /* %s */\n", nom_fich_imagen_png);

        fclose(fich_imagen);
        k++;
    }

    printf("[*] Conversión guardada en \"%s\"\n", nom_fich_imagen_txt);

    exit(0);
}
