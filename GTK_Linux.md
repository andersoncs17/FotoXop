
# Instalar e Compilar Código C com GTK no Linux

Este guia apresenta o **procedimento padrão e recomendado** para instalar as dependências e compilar programas em **C + GTK3** no Linux.

---

## 📌 1. Verificar distribuição Linux

Antes de instalar, identifique sua distribuição:

```bash
cat /etc/os-release
```

---

## 📌 2. Instalar dependências

### 🔹 **Ubuntu / Debian / Linux Mint**

```bash
sudo apt update
sudo apt install build-essential pkg-config libgtk-3-dev
```

---

### 🔹 Fedora

```bash
sudo dnf install gcc gcc-c++ make pkg-config gtk3-devel
```

---

### 🔹 Arch Linux / Manjaro

```bash
sudo pacman -S base-devel pkgconf gtk3
```

---

## 📌 3. Verificar instalação do GTK

Confirme se o GTK está corretamente instalado:

```bash
pkg-config --modversion gtk+-3.0
```

Se um número de versão aparecer, a instalação está correta.

---

## 📌 4. Criar um arquivo C simples

Crie o arquivo `main.c`:

```c
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win), "Exemplo GTK no Linux");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

    g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(win);
    gtk_main();

    return 0;
}
```

---

## 📌 5. Compilar o código

Compile usando `pkg-config`:

```bash
gcc main.c -o exemplo $(pkg-config --cflags --libs gtk+-3.0)
```

---

## 📌 6. Executar o programa

```bash
./exemplo
```

---

