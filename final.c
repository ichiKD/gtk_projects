#include <gtk/gtk.h>


// gcc final.c `pkg-config --cflags --libs gtk+-3.0` -o hello

static void on_activate(GtkApplication *app, gpointer data)
{
    GtkWidget *window;

    window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "WSL GTK Works");

    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;

    int status;

    app = gtk_application_new("com.test.app", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}