#include <gtk/gtk.h>

// Esta é a função que será chamada quando o botão for clicado
void ao_clicar_no_botao(GtkWidget *widget, gpointer data) {
    g_print("Olá! Você clicou no botão.\n"); // g_print é como o printf, mas seguro para GTK
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Criando a janela
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Meu Primeiro Botão");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    
    // Configurando para fechar o programa ao fechar a janela
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // --- NOVO: Criando um botão ---
    GtkWidget *button = gtk_button_new_with_label("Clique em Mim!");

    // --- NOVO: Conectando o clique do botão à função 'ao_clicar_no_botao' ---
    g_signal_connect(button, "clicked", G_CALLBACK(ao_clicar_no_botao), NULL);

    // --- NOVO: Colocando o botão DENTRO da janela ---
    gtk_container_add(GTK_CONTAINER(window), button);

    // Mostra tudo (janela e o botão dentro dela)
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}