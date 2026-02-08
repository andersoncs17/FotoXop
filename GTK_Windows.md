
# Compilar Código C com GTK no Windows usando MSYS2

Este guia descreve **a forma mais moderna, estável e recomendada** para compilar programas em **C + GTK3** no Windows usando **MSYS2**.

---

## 📌 1. Instalar o MSYS2

Baixe e instale a versão mais recente em:

[https://www.msys2.org/](https://www.msys2.org/)

Durante a instalação, deixe as opções padrão.

---

## 📌 2. Atualizar o MSYS2

Abra o terminal **MSYS2 MSYS** (atenção: não o MinGW ainda).

Execute:

```bash
pacman -Syu
```

Feche o terminal e abra novamente.
Depois finalize a atualização:

```bash
pacman -Su
```

---

## 📌 3. Instalar o toolchain + GTK3

Para compilar programas GTK3 em 64 bits, abra o terminal:

**MSYS2 MinGW x64**

E instale os pacotes necessários:

```bash
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-gtk3
```

Isso instalará:

* `gcc`, `g++`, `make`
* `pkg-config`
* `gtk3`
* dependências do GTK (glib, pango, cairo etc.)

---

## 📌 4. Abrir o terminal correto

Para compilar, sempre use:

```
MSYS2 MinGW 64-bit
```

⚠ Não use o terminal **MSYS** ou **UCRT** ao compilar GTK.

---

## 📌 5. Criar um arquivo C simples

Crie `main.c`:

```c
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win), "Exemplo GTK");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

    g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(win);
    gtk_main();

    return 0;
}
```

---

## 📌 6. Compilar o código

No terminal **MSYS2 MinGW 64-bit**, execute:

```bash
gcc main.c -o exemplo `pkg-config --cflags --libs gtk+-3.0`
```

ou:

```bash
gcc main.c -o exemplo $(pkg-config --cflags --libs gtk+-3.0)
```

---

## 📌 7. Executar o programa

```bash
./exemplo.exe
```

---

