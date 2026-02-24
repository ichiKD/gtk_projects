#include <gtk/gtk.h>
// gcc minimal.c -o minimal $(pkg-config --cflags --libs gtk+-3.0)  && ./minimal
int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Test");
    gtk_widget_show(window);
    gtk_main();
    return 0;
}