#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Imagem.h"
#include "Filtros.h"

/**
 * @brief Converte uma imagem para escala de cinza
 * 
 * @param img Ponteiro para a imagem a ser convertida
 */
void escalaDeCinzaImagem(Imagem *img){
    // Percorre todos os pixels da imagem
    for(int i = 0; i < obtemAltura(img); i++){
        for(int j = 0; j < obtemLargura(img); j++){
            // Obtém a cor do pixel atual
            Cor pixel = obtemCorPixel(img, i, j);

            // Calcula o valor de cinza usando a fórmula de luminosidade
            double cinza = 0.3 * pixel.r + 0.59 * pixel.g + 0.11 * pixel.b;

            // Aplica o teto (ceiling) e ajusta para o intervalo [0, 255]
            Byte valorCinza = ajustaCor((int)ceil(cinza));

            // Recolore o pixel com o mesmo valor em R, G e B (tom de cinza)
            Cor novaCor = {valorCinza, valorCinza, valorCinza};
            recolorePixel(img, i, j, novaCor);
        }
    }
}

/**
 * @brief Aplica o filtro Sobel a uma imagem
 * 
 * @param img Ponteiro para a imagem a ser filtrada
 */
void filtroSobel(Imagem *img){
    // Criar cópia da imagem original
    Imagem *copia = copiaImagem(img);

    // Máscaras Sobel para detectar bordas
    int Gx[3][3] = {{-1, 0, +1}, {-2, 0, +2}, {-1, 0, +1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {+1, +2, +1}};

    int altura = obtemAltura(img);
    int largura = obtemLargura(img);

    // Percorrer todos os pixels (exceto bordas)
    for (int i = 1; i < altura - 1; i++) {
        for (int j = 1; j < largura - 1; j++) {
            // Calcular gradientes para cada canal de cor separadamente
            int somaGxR = 0, somaGyR = 0;
            int somaGxG = 0, somaGyG = 0;
            int somaGxB = 0, somaGyB = 0;

            // Aplicar máscaras na vizinhança 3×3
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    Cor pixel = obtemCorPixel(copia, i + ki, j + kj);
                    int mascara = Gx[ki + 1][kj + 1];
                    int mascaraY = Gy[ki + 1][kj + 1];

                    // Aplicar máscaras em cada canal separadamente
                    somaGxR += pixel.r * mascara;
                    somaGyR += pixel.r * mascaraY;

                    somaGxG += pixel.g * mascara;
                    somaGyG += pixel.g * mascaraY;

                    somaGxB += pixel.b * mascara;
                    somaGyB += pixel.b * mascaraY;
                }
            }

            // Calcular magnitude para cada canal: √(Gx² + Gy²)
            int magnitudeR = (int)sqrt(somaGxR * somaGxR + somaGyR * somaGyR);
            int magnitudeG = (int)sqrt(somaGxG * somaGxG + somaGyG * somaGyG);
            int magnitudeB = (int)sqrt(somaGxB * somaGxB + somaGyB * somaGyB);

            // Garantir que os valores estão entre 0 e 255
            if (magnitudeR > 255) magnitudeR = 255;
            if (magnitudeG > 255) magnitudeG = 255;
            if (magnitudeB > 255) magnitudeB = 255;

            // Aplicar os valores de magnitude em cada canal
            Cor novaCor = {magnitudeR, magnitudeG, magnitudeB};
            recolorePixel(img, i, j, novaCor);
        }
    }

    liberaImagem(copia);
}

/**
 * @brief Aplica o filtro Laplace a uma imagem
 * 
 * @param img Ponteiro para a imagem a ser filtrada
 */
void deteccaoBordasLaplace(Imagem *img) {
    // Criar cópia da imagem original
    Imagem *copia = copiaImagem(img);

    // Máscara Laplaciana para detectar bordas
    int kernel[3][3] = {
        { 0, -1,  0},
        {-1,  4, -1},
        { 0, -1,  0}
    };

    int altura = obtemAltura(img);
    int largura = obtemLargura(img);

    // Percorrer todos os pixels (exceto bordas)
    for (int i = 1; i < altura - 1; i++) {
        for (int j = 1; j < largura - 1; j++) {
            // Calcular para cada canal de cor separadamente
            int somaR = 0;
            int somaG = 0;
            int somaB = 0;

            // Aplicar máscara na vizinhança 3×3
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    Cor pixel = obtemCorPixel(copia, i + ki, j + kj);
                    int peso = kernel[ki + 1][kj + 1];

                    somaR += pixel.r * peso;
                    somaG += pixel.g * peso;
                    somaB += pixel.b * peso;
                }
            }

            // Usar valor absoluto para pegar bordas em ambas direções
            int valorR = abs(somaR);
            int valorG = abs(somaG);
            int valorB = abs(somaB);

            // Garantir que os valores estão entre 0 e 255
            if (valorR > 255) valorR = 255;
            if (valorG > 255) valorG = 255;
            if (valorB > 255) valorB = 255;

            // Aplicar os valores em cada canal
            Cor novaCor = {valorR, valorG, valorB};
            recolorePixel(img, i, j, novaCor);
        }
    }

    liberaImagem(copia);
}

/**
 * @brief Aplica um filtro personalizado a uma imagem
 * 
 * @param img Ponteiro para a imagem a ser filtrada
 */
void meuFiltro(Imagem *img){
    // Filtro de Nitidez (Sharpen)
    // Realça os detalhes e bordas da imagem

    // Criar cópia da imagem original
    Imagem *copia = copiaImagem(img);

    // Máscara de nitidez (Sharpen kernel)
    int kernel[3][3] = {
        { 0, -1,  0},
        {-1,  5, -1},
        { 0, -1,  0}
    };

    int altura = obtemAltura(img);
    int largura = obtemLargura(img);

    // Percorrer todos os pixels (exceto bordas)
    for (int i = 1; i < altura - 1; i++) {
        for (int j = 1; j < largura - 1; j++) {
            // Calcular para cada canal de cor separadamente
            int somaR = 0;
            int somaG = 0;
            int somaB = 0;

            // Aplicar máscara na vizinhança 3×3
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    Cor pixel = obtemCorPixel(copia, i + ki, j + kj);
                    int peso = kernel[ki + 1][kj + 1];

                    somaR += pixel.r * peso;
                    somaG += pixel.g * peso;
                    somaB += pixel.b * peso;
                }
            }

            // Garantir que os valores estão entre 0 e 255
            if (somaR < 0) somaR = 0;
            if (somaR > 255) somaR = 255;

            if (somaG < 0) somaG = 0;
            if (somaG > 255) somaG = 255;

            if (somaB < 0) somaB = 0;
            if (somaB > 255) somaB = 255;

            // Aplicar os valores em cada canal
            Cor novaCor = {somaR, somaG, somaB};
            recolorePixel(img, i, j, novaCor);
        }
    }

    liberaImagem(copia);
}