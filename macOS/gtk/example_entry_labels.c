/*
Use the following to compile: 
gcc `pkg-config --cflags --libs gtk+-2.0` example_entry_labels.c -o example_program
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

GtkWidget *make_entry_with_label(GtkTable *table, const gchar *label_text, gint left_attach, gint right_attach, gint top_attach, 
                                gint bottom_attach, gint entry_length);
gint config_gui(void);
void action(GtkWidget *entry[]);

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    config_gui();
    return 0;
}

void action(GtkWidget *entry[])
{
    printf("H: %s\n", gtk_entry_get_text(GTK_ENTRY(entry[0])));
    printf("U: %s\n", gtk_entry_get_text(GTK_ENTRY(entry[1])));
    printf("P: %s\n", gtk_entry_get_text(GTK_ENTRY(entry[2])));
    printf("D: %s\n", gtk_entry_get_text(GTK_ENTRY(entry[3])));
    printf("T: %s\n", gtk_entry_get_text(GTK_ENTRY(entry[4])));
}

GtkWidget *make_entry_with_label(GtkTable *table,
                     const gchar *label_text,
                     gint left_attach,
                     gint right_attach,
                     gint top_attach,
                     gint bottom_attach,
                     gint entry_length)
{

    GtkWidget *entry;
    GtkWidget *label;

    label = gtk_label_new(label_text);
    entry = gtk_entry_new();
    gtk_table_attach(table, label, left_attach, right_attach, top_attach, bottom_attach, GTK_FILL|GTK_EXPAND, GTK_FILL|GTK_EXPAND, 5, 5);
    gtk_table_attach(table, entry, left_attach + 1, right_attach + 1, top_attach, bottom_attach, GTK_FILL|GTK_EXPAND, GTK_FILL|GTK_EXPAND, 5, 5);
    gtk_misc_set_alignment(GTK_MISC(label), 1, 0.5);
    gtk_misc_set_padding(GTK_MISC(label), 2, 2);
    gtk_entry_set_max_length(GTK_ENTRY(entry), entry_length);

    gtk_widget_show(entry);
    gtk_widget_show(label);

    return entry;
}


gint config_gui()
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *bbox;
    GtkWidget *button;
    GtkWidget *entry[5];
    GtkWidget *frame;
    GtkWidget *table;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Generic Linux system installer (GLSI)");
    gtk_widget_set_size_request(window, 350, 250);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(GTK_WINDOW(window), "delete_event", G_CALLBACK(gtk_main_quit), NULL);

    frame = gtk_frame_new("Fun fun fun:");
    vbox = gtk_vbox_new(FALSE, 5);
    table = gtk_table_new(4,2, FALSE);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(frame), table);

    entry[0] = make_entry_with_label(GTK_TABLE(table), "I Love:", 0,1,0,1,32);
    entry[1] = make_entry_with_label(GTK_TABLE(table), "Them:", 0,1,1,2,15);
    entry[2] = make_entry_with_label(GTK_TABLE(table), "Little:", 0,1,2,3,15);
    gtk_entry_set_visibility(GTK_ENTRY(entry[2]), FALSE);
    entry[3] = make_entry_with_label(GTK_TABLE(table), "Nachos:", 0,1,3,4,15);
    entry[4] = make_entry_with_label(GTK_TABLE(table), "D0od:", 0,1,4,5,15);

    bbox = gtk_hbutton_box_new();
    gtk_box_pack_start(GTK_BOX(vbox), bbox, TRUE, TRUE, 3);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_END);
    gtk_box_set_spacing(GTK_BOX(bbox), 10);

    button = gtk_button_new_from_stock(GTK_STOCK_OK);
    gtk_container_add(GTK_CONTAINER(bbox), button);
    g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(action), entry);
    button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add(GTK_CONTAINER(bbox), button);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
