#include <gtk/gtk.h>

#if GTK_MAJOR_VERSION == 4
GtkApplication *main_app_handle;
#else
GtkWidget *main_app_handle;
#endif
GtkWidget *main_window;

void print_msg(GtkWidget *widget, gpointer window) {

  g_printf("Button clicked\n");
}

static void
#if GTK_MAJOR_VERSION == 4
app_activate (GApplication *app) {
#else
app_activate (GtkWidget *app) {
#endif
  GtkWidget *lab;

#if GTK_MAJOR_VERSION == 4
  main_window = gtk_application_window_new (GTK_APPLICATION (app));
#else
  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
#endif

  gtk_window_set_title (GTK_WINDOW (main_window), "lb1");
  gtk_window_set_default_size (GTK_WINDOW (main_window), 400, 300);

  lab = gtk_label_new ("Hello.");
#if GTK_MAJOR_VERSION == 4
  gtk_window_set_child (GTK_WINDOW (main_window), lab);
#endif
  gtk_window_present (GTK_WINDOW (main_window));
}


int main(int argc, char *argv[]) {
  GtkWidget *halign;
  GtkWidget *grid;

#if GTK_MAJOR_VERSION == 4
//  GtkApplication *app;
  GtkGrid *button;
  int stat;
#else
  GtkWidget *button;

  gtk_init(&argc, &argv);
  //main_app_handle = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  app_activate(main_window);
  g_signal_connect (main_app_handle, "activate", G_CALLBACK (app_activate), NULL);
  g_object_unref (main_app_handle);
#endif

#if GTK_MAJOR_VERSION == 4
  main_app_handle = gtk_application_new ("com.github.ToshioCP.lb1", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (main_app_handle, "activate", G_CALLBACK (app_activate), NULL);
  stat = g_application_run (G_APPLICATION (main_app_handle), argc, argv);
  g_object_unref (main_app_handle);
#endif

  //gtk_window_set_title(GTK_WINDOW(main_window), "Mnemonic");
  //gtk_window_set_default_size(GTK_WINDOW(main_window), 300, 200);
//  gtk_container_set_border_width(GTK_CONTAINER(window), 15);
  
  button = gtk_button_new_with_mnemonic("_Button");

  g_signal_connect(button, "clicked",
      G_CALLBACK(print_msg), NULL);

#if GTK_MAJOR_VERSION == 4
  grid = gtk_grid_new ();
  gtk_grid_attach (grid, button, 10, 10, 10, 10);

#else
  halign = gtk_alignment_new(0, 0, 0, 0);

  gtk_container_add(GTK_CONTAINER(halign), button);
  gtk_container_add(GTK_CONTAINER(main_window), halign);  

  gtk_widget_show_all(main_window);

  g_signal_connect(G_OBJECT(main_window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL); 

  gtk_main();
#endif

  return 0;
}

