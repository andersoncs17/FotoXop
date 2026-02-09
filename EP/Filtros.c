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
    //Percorre todos os pixels da imagem
    for(int i = 0; i < obtemAltura(img); i++){
        for(int j = 0; j < obtemLargura(img); j++){
            //Obtém a cor do pixel atual
            Cor pixel = obtemCorPixel(img, i, j);

            //Calcula o valor de cinza usando a fórmula de luminosidade
            double cinza = 0.3 * pixel.r + 0.59 * pixel.g + 0.11 * pixel.b;

            //Aplica o teto (ceiling) e ajusta para o intervalo [0, 255]
            Byte valorCinza = ajustaCor((int)ceil(cinza));

            //Recolore o pixel com o mesmo valor em R, G e B (tom de cinza)
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
    //Cópia da imagem original
    Imagem *copia = copiaImagem(img);

    //Detectar bordas
    int Gx[3][3] = {{-1, 0, +1}, {-2, 0, +2}, {-1, 0, +1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {+1, +2, +1}};

    int altura = obtemAltura(img);
    int largura = obtemLargura(img);

    //Percorre todos os pixels menos as bordas
    for (int i = 1; i < altura - 1; i++) {
        for (int j = 1; j < largura - 1; j++) {
            //Calcular gradientes para cada canal de cor
            int somaGxR = 0, somaGyR = 0;
            int somaGxG = 0, somaGyG = 0;
            int somaGxB = 0, somaGyB = 0;

            //Aplicar máscaras na vizinhança 3×3
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    Cor pixel = obtemCorPixel(copia, i + ki, j + kj);
                    int mascara = Gx[ki + 1][kj + 1];
                    int mascaraY = Gy[ki + 1][kj + 1];

                    //Aplicar máscaras em cada canal
                    somaGxR += pixel.r * mascara;
                    somaGyR += pixel.r * mascaraY;

                    somaGxG += pixel.g * mascara;
                    somaGyG += pixel.g * mascaraY;

                    somaGxB += pixel.b * mascara;
                    somaGyB += pixel.b * mascaraY;
                }
            }

            //√(Gx² + Gy²)
            int magnitudeR = (int)sqrt(somaGxR * somaGxR + somaGyR * somaGyR);
            int magnitudeG = (int)sqrt(somaGxG * somaGxG + somaGyG * somaGyG);
            int magnitudeB = (int)sqrt(somaGxB * somaGxB + somaGyB * somaGyB);

            //Garantir que os valores estão entre 0 e 255
            if (magnitudeR > 255) magnitudeR = 255;
            if (magnitudeG > 255) magnitudeG = 255;
            if (magnitudeB > 255) magnitudeB = 255;

            //Aplicar os valores em cada canal
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
    //Cópia da imagem original
    Imagem *copia = copiaImagem(img);

    //Máscara Laplaciana para detectar bordas
    int kernel[3][3] = {
        { 0, -1,  0},
        {-1,  4, -1},
        { 0, -1,  0}
    };

    int altura = obtemAltura(img);
    int largura = obtemLargura(img);

    //Percorre todos os pixels menos as bordas
    for (int i = 1; i < altura - 1; i++) {
        for (int j = 1; j < largura - 1; j++) {
            //Calcula cada canal de cor
            int somaR = 0;
            int somaG = 0;
            int somaB = 0;

            //Aplicar máscara na vizinhança 3×3
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    Cor pixel = obtemCorPixel(copia, i + ki, j + kj);
                    int peso = kernel[ki + 1][kj + 1];

                    somaR += pixel.r * peso;
                    somaG += pixel.g * peso;
                    somaB += pixel.b * peso;
                }
            }

            //Usa valor absoluto para pegar bordas em ambas direções
            int valorR = abs(somaR);
            int valorG = abs(somaG);
            int valorB = abs(somaB);

            //Garantir que os valores estão entre 0 e 255
            if (valorR > 255) valorR = 255;
            if (valorG > 255) valorG = 255;
            if (valorB > 255) valorB = 255;

            //Aplicar os valores em cada canal
            Cor novaCor = {valorR, valorG, valorB};
            recolorePixel(img, i, j, novaCor);
        }
    }

    liberaImagem(copia);
}

/**
 * @brief Aplica um filtro de "Gramado Perfeito" à imagem
 *
 * Realça os tons de verde da imagem, tornando-os mais vibrantes e saturados,
 * simulando o efeito visual usado em transmissões de TV de eventos esportivos.
 *
 * @param img Ponteiro para a imagem a ser filtrada
 */
void meuFiltro(Imagem *img){
    if (!img) 
        return;

    int altura = obtemAltura(img);
    int largura = obtemLargura(img);

    //Percorre todos os pixels da imagem
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            Cor pixel = obtemCorPixel(img, i, j);

            //Verifica se o pixel é predominantemente verde
            if (pixel.g > pixel.r && pixel.g > pixel.b) {
                //Calcula o quanto ele domina
                int diferencaR = pixel.g - pixel.r;
                int diferencaB = pixel.g - pixel.b;
                int forcaVerde = (diferencaR + diferencaB) / 2;

                //Quanto mais verde já é, mais intensificamos
                double fatorIntensificacao = 1.3;
                if (forcaVerde > 50) {
                    fatorIntensificacao = 1.4;  //Verde forte
                }

                // Aplica o filtro
                int novoG = pixel.g * fatorIntensificacao;
                int novoR = pixel.r * 0.7;  //Reduz vermelho
                int novoB = pixel.b * 0.8;  //Reduz azul 

                //Ajusta os valores para o intervalo [0, 255]
                Cor novaCor = {
                    ajustaCor(novoR),
                    ajustaCor(novoG),
                    ajustaCor(novoB)
                };

                recolorePixel(img, i, j, novaCor);
            }
        }
    }
}