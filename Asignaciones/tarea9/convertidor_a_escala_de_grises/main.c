#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libs/stb_image_write.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <imagen.jpg>\n", argv[0]);
        return 1;
    }

    int width, height, channels;
    unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);
    if (!img) {
        printf("Error al cargar la imagen.\n");
        return 1;
    }

     // Crear nuevo buffer para la imagen en gris
    unsigned char *gray = malloc(width * height);
    if (!gray) {
        printf("No se pudo asignar memoria.\n");
        stbi_image_free(img);
        return 1;
    }

    // Convertir a gris: promedio o frmula de luminosidad
    for (int i = 0; i < width * height; i++) {
        int r = img[i * channels + 0];
        int g = img[i * channels + 1];
        int b = img[i * channels + 2];
    // frmula para convertir a escala de grises
        gray[i] = (unsigned char)(0.3 * r + 0.59 * g + 0.11 * b);
    }

    // Guardar como jpg en escala de grises
    stbi_write_png("imagen_gris.jpg", width, height, 1, gray, width);
    printf("Imagen guardada como imagen_gris.jpg\n");

    // Liberar memoria
    stbi_image_free(img);
    free(gray);
    return 0;
}