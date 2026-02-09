# FotoXop

Editor de imagens desenvolvido em **C** com interface gráfica **GTK3**, como Exercício Programa da disciplina de **Estruturas de Dados I** — UFES (2025/2).

O projeto aplica conceitos fundamentais de estruturas de dados no contexto de processamento digital de imagens, permitindo aplicar filtros, desfazer operações e buscar/trocar cores de forma eficiente.

## Funcionalidades

- **Abertura e salvamento** de imagens no formato PPM (P3)
- **Filtros de imagem**: Escala de Cinza, Sobel (detecção de bordas), Laplace e filtro customizado
- **Desfazer (Undo)**: reverte operações sequencialmente usando uma Pilha
- **Busca e troca de cores**: clique com botão direito em um pixel para substituir sua cor (exata ou aproximada via tolerância) em toda a imagem

## Estruturas de Dados Utilizadas

| Estrutura | Uso no projeto |
|---|---|
| **Pilha** (Stack) | Armazena cópias da imagem para funcionalidade de desfazer |
| **Lista Encadeada** | Armazena as posições (linha, coluna) de pixels com determinada cor |
| **Árvore AVL** | Indexa todas as cores da imagem para busca eficiente — O(log n) — com suporte a busca exata e aproximada |

## Etapas de Implementação

| Etapa | Descrição |
|---|---|
| 0 | Manipulação básica de imagem (alocação, cópia, leitura/escrita PPM) |
| 1 | Filtros (Escala de Cinza, Sobel, Laplace, filtro customizado) |
| 2 | Implementação da Pilha |
| 3 | Integração do Undo com a interface |
| 4 | Implementação da Lista Encadeada |
| 5 | Implementação da Árvore AVL |
| 6 | Busca e troca de cores via AVL com tolerância |

## Como Compilar e Executar

Requer **GTK3** instalado. Consulte [GTK_Windows.md](EP/GTK_Windows.md) ou [GTK_Linux.md](EP/GTK_Linux.md) para instruções de configuração.

```bash
make            # Compilar
make run        # Compilar e executar
make clean      # Limpar arquivos objeto
```

## Estrutura do Projeto

```
EP/
├── main.c          # Ponto de entrada
├── Imagem.c/h      # Manipulação de imagem e I/O PPM
├── Cor.c/h         # Operações com cores (distância, comparação)
├── Filtros.c/h     # Implementação dos filtros
├── Pilha.c/h       # Pilha (LIFO)
├── Lista.c/h       # Lista encadeada simples
├── AVL.c/h         # Árvore AVL para indexação de cores
├── UI.c/h          # Interface GTK3
├── Testes.c/h      # Testes unitários
├── Util.c/h        # Funções utilitárias
├── Makefile         # Automação de build
└── estilo.css       # Estilização da interface
```

## Disciplina

**Estruturas de Dados I** — Universidade Federal do Espírito Santo (UFES), 2025/2.

## Autor

Anderson Sousa
