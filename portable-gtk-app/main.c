#include <gtk/gtk.h>

GtkWidget *main_window;

#if GTK_MAJOR_VERSION == 4
static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  main_window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (main_window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (main_window), 200, 200);
  gtk_widget_show (main_window);
}
#endif

int main(int argc, char *argv[]) {

#if GTK_MAJOR_VERSION == 4
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

#else /* GTK_MAJOR_VERSION < 4 */
  gtk_init(&argc, &argv);

  g_printf("GTK+ version: %d.%d.%d\n", gtk_major_version, 
    gtk_minor_version, gtk_micro_version);
#endif

  g_printf("Glib version: %d.%d.%d\n", glib_major_version,
    glib_minor_version, glib_micro_version);    

#if GTK_MAJOR_VERSION < 4
  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
#else
  main_window = gtk_window_new();
#endif

  gtk_widget_show(main_window);

#if GTK_MAJOR_VERSION < 4
  g_signal_connect(main_window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);
  gtk_main();
#endif

    return 0;
}

