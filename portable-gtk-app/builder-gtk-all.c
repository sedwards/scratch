#include <gtk/gtk.h>

static GtkBuilder *builder;
//static GtkBuilder *do_widget;
static GtkWidget *do_widget;

#if GTK_MAJOR_VERSION == 4
GtkApplication *main_app_handle;
#else
GtkWidget *main_app_handle;
#endif
GtkWidget *main_window;

GtkWidget *
do_builder (GtkWidget *do_widget);


static void
#if GTK_MAJOR_VERSION == 4
app_activate (GApplication *app) {
#else
app_activate (GtkWidget *app) {
#endif
  GtkWidget *lab;
  GtkWidget *halign;
  GtkWidget *button;
#if GTK_MAJOR_VERSION == 4
  GtkGrid *grid;

  main_window = gtk_application_window_new (GTK_APPLICATION (app));
#else
  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
#endif
   do_builder(do_widget);
}

#if GTK_MAJOR_VERSION < 4
G_MODULE_EXPORT void
quit_activate (GtkAction *action)
{
  GtkWidget *window;

  window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
  gtk_widget_destroy (window);
}

G_MODULE_EXPORT void
about_activate (GtkAction *action)
{
  GtkWidget *about_dlg;

  about_dlg = GTK_WIDGET (gtk_builder_get_object (builder, "aboutdialog1"));
  gtk_dialog_run (GTK_DIALOG (about_dlg));
  gtk_widget_hide (about_dlg);
}
#endif

GtkWidget *
do_builder (GtkWidget *do_widget)
{
  static GtkWidget *window = NULL;
  GError *err = NULL;
  gchar *filename;
  
  if (!window)
    {

      builder = gtk_builder_new ();
      //filename = demo_find_file ("builder-gtk2.ui", NULL);
      //gtk_builder_add_from_file (builder, filename, &err);
#if GTK_MAJOR_VERSION < 4
      gtk_builder_add_from_file (builder, "builder-gtk3.ui", &err);
#else
      gtk_builder_add_from_file (builder, "builder-gtk4.ui", &err);
#endif
      if (err)
	{
	  g_error ("ERROR: %s\n", err->message);
	  return NULL;
	}

 #if GTK_MAJOR_VERSION < 4
      gtk_builder_connect_signals (builder, NULL);
 #endif
      window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
 #if GTK_MAJOR_VERSION < 4
      gtk_window_set_screen (GTK_WINDOW (window),
			     gtk_widget_get_screen (do_widget));
      g_signal_connect (window, "destroy",
			G_CALLBACK (gtk_widget_destroyed), &window);
 #endif
    }

 #if GTK_MAJOR_VERSION < 4
  if (!gtk_widget_get_visible (window))
    {
      gtk_widget_show_all (window);
    }
  else
    {	 
      gtk_widget_destroy (window);
      window = NULL;
    }
 #endif

  return window;
}

int main(int argc, char *argv[]) {
  int stat;

#if GTK_MAJOR_VERSION < 4
  gtk_init(&argc, &argv);
  do_builder(do_widget);
  //g_signal_connect (main_app_handle, "activate", G_CALLBACK (app_activate), NULL);
#else
  main_app_handle = gtk_application_new ("com.github.ToshioCP.lb1", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (main_app_handle, "activate", G_CALLBACK (app_activate), NULL);
  stat = g_application_run (G_APPLICATION (main_app_handle), argc, argv);
#endif
  //g_object_unref (main_app_handle);

#if GTK_MAJOR_VERSION < 4
  gtk_main();

  g_signal_connect(G_OBJECT(do_widget), "destroy",
    G_CALLBACK(gtk_main_quit), NULL);
#endif

  return 0;
}

