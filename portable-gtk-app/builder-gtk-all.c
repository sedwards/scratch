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

#else

static void
remove_timeout (gpointer data)
{
  guint id = GPOINTER_TO_UINT (data);

  g_source_remove (id);
}

static gboolean
pop_status (gpointer data)
{
  gtk_statusbar_pop (GTK_STATUSBAR (data), 0);
  g_object_set_data (G_OBJECT (data), "timeout", NULL);
  return G_SOURCE_REMOVE;
}

static void
status_message (GtkStatusbar *status,
                const char   *text)
{
  guint id;

  gtk_statusbar_push (GTK_STATUSBAR (status), 0, text);
  id = g_timeout_add (5000, pop_status, status);

  g_object_set_data_full (G_OBJECT (status), "timeout", GUINT_TO_POINTER (id), remove_timeout);
}

static void
help_activate (GSimpleAction *action,
               GVariant      *parameter,
               gpointer       user_data)
{
  GtkWidget *status;

  status = GTK_WIDGET (g_object_get_data (G_OBJECT (user_data), "status"));
  status_message (GTK_STATUSBAR (status), "Help not available");
 }

static void
not_implemented (GSimpleAction *action,
                 GVariant      *parameter,
                 gpointer       user_data)
{
  GtkWidget *status;
  char *text;

  text = g_strdup_printf ("Action “%s” not implemented", g_action_get_name (G_ACTION (action)));
  status = GTK_WIDGET (g_object_get_data (G_OBJECT (user_data), "status"));
  status_message (GTK_STATUSBAR (status), text);
  g_free (text);
}

static GActionEntry win_entries[] = {
  { "new", not_implemented, NULL, NULL, NULL },
  { "open", not_implemented, NULL, NULL, NULL },
  { "save", not_implemented, NULL, NULL, NULL },
  { "save-as", not_implemented, NULL, NULL, NULL },
  { "copy", not_implemented, NULL, NULL, NULL },
  { "cut", not_implemented, NULL, NULL, NULL },
  { "paste", not_implemented, NULL, NULL, NULL },
  { "quit", quit_activate, NULL, NULL, NULL },
  { "about", about_activate, NULL, NULL, NULL },
  { "help", help_activate, NULL, NULL, NULL }
};
#endif

GtkWidget *
do_builder (GtkWidget *do_widget)
{
  static GtkWidget *window = NULL;
  GError *err = NULL;
  gchar *filename;
  
  if (!window)
    {
      GtkWidget *about;
      GtkWidget *status;

      builder = gtk_builder_new ();
#if GTK_MAJOR_VERSION == 4
      gtk_builder_add_from_file (builder, "builder-gtk4.ui", &err);
#else
      gtk_builder_add_from_file (builder, "builder-gtk-all.ui", &err);
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

#if GTK_MAJOR_VERSION == 4
      gtk_window_set_display (GTK_WINDOW (window),
                              gtk_widget_get_display (do_widget));
      g_object_add_weak_pointer (G_OBJECT (window), (gpointer *)&window);
      actions = (GActionGroup*)g_simple_action_group_new ();
      g_action_map_add_action_entries (G_ACTION_MAP (actions),
                                       win_entries, G_N_ELEMENTS (win_entries),
                                       window);
      gtk_widget_insert_action_group (window, "win", actions);

      controller = gtk_shortcut_controller_new ();
      gtk_shortcut_controller_set_scope (GTK_SHORTCUT_CONTROLLER (controller),
                                         GTK_SHORTCUT_SCOPE_GLOBAL);
      gtk_widget_add_controller (window, controller);
      gtk_shortcut_controller_add_shortcut (GTK_SHORTCUT_CONTROLLER (controller),
           gtk_shortcut_new (gtk_keyval_trigger_new (GDK_KEY_n, GDK_CONTROL_MASK),
                             gtk_named_action_new ("win.new")));
      gtk_shortcut_controller_add_shortcut (GTK_SHORTCUT_CONTROLLER (controller),
           gtk_shortcut_new (gtk_keyval_trigger_new (GDK_KEY_o, GDK_CONTROL_MASK),
                             gtk_named_action_new ("win.open")));
      gtk_shortcut_controller_add_shortcut (GTK_SHORTCUT_CONTROLLER (controller),
           gtk_shortcut_new (gtk_keyval_trigger_new (GDK_KEY_s, GDK_CONTROL_MASK),
                             gtk_named_action_new ("win.save")));
      gtk_shortcut_controller_add_shortcut (GTK_SHORTCUT_CONTROLLER (controller),
           gtk_shortcut_new (gtk_keyval_trigger_new (GDK_KEY_s, GDK_CONTROL_MASK|GDK_SHIFT_MASK),
                             gtk_named_action_new ("win.save-as")));
      gtk_shortcut_controller_add_shortcut (GTK_SHORTCUT_CONTROLLER (controller),
           gtk_shortcut_new (gtk_keyval_trigger_new (GDK_KEY_q, GDK_CONTROL_MASK),
                             gtk_named_action_new ("win.quit")));
      gtk_shortcut_controller_add_shortcut (GTK_SHORTCUT_CONTROLLER (controller),
           gtk_shortcut_new (gtk_keyval_trigger_new (GDK_KEY_c, GDK_CONTROL_MASK),
                             gtk_named_action_new ("win.copy")));
      gtk_shortcut_controller_add_shortcut (GTK_SHORTCUT_CONTROLLER (controller),
           gtk_shortcut_new (gtk_keyval_trigger_new (GDK_KEY_x, GDK_CONTROL_MASK),
                             gtk_named_action_new ("win.cut")));
      gtk_shortcut_controller_add_shortcut (GTK_SHORTCUT_CONTROLLER (controller),
           gtk_shortcut_new (gtk_keyval_trigger_new (GDK_KEY_v, GDK_CONTROL_MASK),
                             gtk_named_action_new ("win.paste")));
      gtk_shortcut_controller_add_shortcut (GTK_SHORTCUT_CONTROLLER (controller),
           gtk_shortcut_new (gtk_keyval_trigger_new (GDK_KEY_F1, 0),
                             gtk_named_action_new ("win.help")));
      gtk_shortcut_controller_add_shortcut (GTK_SHORTCUT_CONTROLLER (controller),
           gtk_shortcut_new (gtk_keyval_trigger_new (GDK_KEY_F7, 0),
                             gtk_named_action_new ("win.about")));

      about = GTK_WIDGET (gtk_builder_get_object (builder, "aboutdialog1"));
      gtk_window_set_transient_for (GTK_WINDOW (about), GTK_WINDOW (window));
      gtk_window_set_hide_on_close (GTK_WINDOW (about), TRUE);
      g_object_set_data_full (G_OBJECT (window), "about",
                              about, (GDestroyNotify)gtk_window_destroy);

      status = GTK_WIDGET (gtk_builder_get_object (builder, "statusbar1"));
      g_object_set_data (G_OBJECT (window), "status", status);

      g_object_unref (builder);
#endif

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
  main_app_handle = gtk_application_new ("com.github.sedwards.gtk-builder-demo", G_APPLICATION_FLAGS_NONE);
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

