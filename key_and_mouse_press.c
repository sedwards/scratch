#include <gtk/gtk.h>

int key_press_active, button_press_active; 

static gboolean
key_press_event(GtkWidget *widget,
          GdkEventKey *event)
{
    GtkWidget *window;
    g_printerr("Key Press %s\n",
               gdk_keyval_name (event->keyval));

    key_press_active = 1;

    return FALSE;
}

static gboolean
key_release_event(GtkWidget *widget,
          GdkEventKey *event)
{
    GtkWidget *window;
    g_printerr("Key Release %s\n",
               gdk_keyval_name (event->keyval));


    key_press_active = 0;

    return FALSE;
}

static
gboolean button_press_cb(GtkWidget *wi, GdkEventButton *ev, gpointer user_data)
{
  GtkWidget *window;
  gdouble x,y;

  GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(wi));

  g_printerr("Button press\n");

  x = ((GdkEventButton*)ev)->x;
  y = ((GdkEventButton*)ev)->y;

  window = gtk_widget_get_toplevel (wi);

  g_printerr("%f ,%f\n", x, y);

  gtk_window_begin_move_drag(GTK_WINDOW(window), ev->button, ev->x_root, ev->y_root, ev->time);
  gtk_window_begin_move_drag(wi, ev->button, ev->x_root, ev->y_root, ev->time);

//  Works but jumps/jerks
//  gdk_window_move (gdk_window, ev->x_root, ev->y_root);

// worthless hack
#if 0
 int a = 1;

  while (ev->button &&  a < 1000 ){
    g_printerr("button held");
    gdk_window_move (gdk_window, ev->x_root, ev->y_root);
    a++;
  }
#endif

  return FALSE;
}

static
gboolean button_release_cb(GtkWidget *wi, GdkEventButton *ev, gpointer user_data)
{
  GtkWidget *window;
  gdouble x,y;

  GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(wi));

  g_printerr("Button release\n");

  x = ((GdkEventButton*)ev)->x;
  y = ((GdkEventButton*)ev)->y;

  window = gtk_widget_get_toplevel (wi);

  g_printerr("%f ,%f\n", x, y);

  gtk_window_begin_move_drag(GTK_WINDOW(window), ev->button, ev->x_root, ev->y_root, ev->time);
  gtk_window_begin_move_drag(wi, ev->button, ev->x_root, ev->y_root, ev->time);

//  Works but jumps/jerks
//  gdk_window_move (gdk_window, ev->x_root, ev->y_root);

// worthless hack
#if 0
 int a = 1;

  while (ev->button &&  a < 1000 ){
    g_printerr("button held");
    gdk_window_move (gdk_window, ev->x_root, ev->y_root);
    a++;
  }
#endif

  return FALSE;
}

#if 0
void move_while_holding()
{
if key_press_event (META)
  while !key_release_event

&&

if !button-press-event” 
while ! “button-press-event” 
 do move

   get_mouse_pos
   move window (new mouse_pos)
done

or

  while key_press_event
    pos = gdk_screen_pointer
  move_window (pos)

}
#endif


int main( int   argc,
          char *argv[] )
{

    GtkWidget *window;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);
  gtk_widget_add_events(window, GDK_BUTTON_RELEASE_MASK);
  gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
  gtk_widget_add_events(window, GDK_KEY_RELEASE_MASK);
   
  g_signal_connect(window, "button-press-event", G_CALLBACK(button_press_cb), NULL);
  g_signal_connect(window, "button-release-event", G_CALLBACK(button_release_cb), NULL);

  g_signal_connect(window, "key-press-event", G_CALLBACK(key_press_event), NULL);
  g_signal_connect(window, "key-release-event", G_CALLBACK(key_release_event), NULL);

    gtk_widget_show (window);

    gtk_main ();

    return 0;
}



#if 0

gtk_widget_get_pointer ()
void
gtk_widget_get_pointer (GtkWidget *widget,
                        gint *x,
                        gint *y);
gtk_widget_get_pointer has been deprecated since version 3.4 and should not be used in newly-written code.
Use gdk_window_get_device_position() instead.
Obtains the location of the mouse pointer in widget coordinates. Widget coordinates are a bit odd; for historical reasons, they are defined as widget->window coordinates for widgets that return TRUE for gtk_widget_get_has_window(); and are relative to widget->allocation.x , widget->allocation.y otherwise.
Parameters
widget
a GtkWidget
 
x
return location for the X coordinate, or NULL.
[out][allow-none]
y
return location for the Y coordinate, or NULL.
[out][allow-none]

#endif
