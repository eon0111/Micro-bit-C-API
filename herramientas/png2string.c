#include <stdio.h>
#include <png.h>
#include <stdlib.h>
#include <string.h>

#define DIM             5
#define NOM_OUTPUT_DEF  "resultado.txt"

#define abs(x) (x < 0) ? -x : x

void
comprueba_fichero(FILE *fp, char *nombre)
{
    if (!fp)
    {
        printf("error: no se pudo abrir \"%s\"!\n", nombre);
        exit(-1);
    }
}

void
main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("error: número insuficiente de parámetros\n");
        exit(-1);
    }
    
    FILE *fich_imagen, *fich_imagen_txt;
    char *nom_fich_imagen_txt = "", *nom_fich_imagen_png;
    png_structp datos_imagen;
    png_infop info_imagen;
    png_bytepp filas;
    int i, j, k;

    /* Obtenemos el nombre del fichero de salida */
    for (i = 1; i < argc - 1; i++)
    {
        if (strcmp(argv[i], "-o") == 0)
        {
            if (argc == 3)
            {
                printf("error: no indicó ningún fichero de imagen\n");
                exit(-1);
            }

            nom_fich_imagen_txt = (char *)malloc(strlen(argv[i + 1]));
            strcpy(nom_fich_imagen_txt, argv[i + 1]);
            break;
        }
    }
    if (strlen(nom_fich_imagen_txt) == 0)
    {
        nom_fich_imagen_txt = (char *)malloc(strlen("resultado.txt") + 1);
        strcpy(nom_fich_imagen_txt, "resultado.txt");
    }

    /* Abrimos el descriptor del fichero de resultados */
    fich_imagen_txt = fopen(nom_fich_imagen_txt, "w");

    /* Procesamos las imágenes y depositamos las conversiones en el fichero de salida */
    for (k = 1; k < argc; k++)
    {
        nom_fich_imagen_png = argv[k];
        if (strcmp(nom_fich_imagen_png, "-o") == 0)
        {
            k++;
            continue;
        }

        /* Abrimos el descriptor del fichero de imagen */
        fich_imagen = fopen(nom_fich_imagen_png, "rb");

        /* Comprobamos que los ficheros se abrieron correctamente */
        comprueba_fichero(fich_imagen, nom_fich_imagen_png);
        comprueba_fichero(fich_imagen_txt, nom_fich_imagen_txt);

        /* 
         * - "datos_imagen" contiene la información de cada pixel
         * - "info_imagen" contiene información sobre el fichero de imagen
         * - Con "png_set_palette_to_rgb" conseguimos que la información de la
         *   se procese como datos RGB
         */
        datos_imagen = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        info_imagen = png_create_info_struct(datos_imagen);
        png_set_palette_to_rgb(datos_imagen);

        /* Establecemos el "puente" entre el descriptor del fichero de imagen y la
         * estructura donde serán leídos sus datos tras ser convertidos a info. RGB */
        png_init_io(datos_imagen, fich_imagen);

        /* Leemos el fichero de imagen */
        png_read_png(datos_imagen, info_imagen, PNG_TRANSFORM_IDENTITY, NULL);
        filas = png_get_rows(datos_imagen, info_imagen);

        /* Construimos el array correspondiente a la imagen actual */
        // fprintf(fich_imagen_txt, "{");
        fprintf(fich_imagen_txt, "\"");
        for (i = 0; i < DIM; i++)
        {
            // fprintf(fich_imagen_txt, "{");
            for (j = 0; j < DIM * 3; j += 3)
            {
                fprintf(fich_imagen_txt, (!filas[i][j]) ? "1" : "0");
                //fprintf(fich_imagen_txt, (j < DIM * 2) ? "," : "");
            }
            // fprintf(fich_imagen_txt, (i < DIM - 1) ? "}," : "}");
        
        }
        fprintf(fich_imagen_txt, "\",    /* %s */\n", nom_fich_imagen_png);
        // fprintf(fich_imagen_txt, "},   /* %s */\n", nom_fich_imagen_png);
        // fprintf(fich_imagen_txt, "\t/* %s */\n", nom_fich_imagen_png);

        fclose(fich_imagen);
    }

    free(nom_fich_imagen_txt);
    exit(0);
}
