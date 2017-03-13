#include <gtk/gtk.h>
#include <iostream>
#include <vector>

static cairo_surface_t *surface = NULL;
GtkWidget *window_widget;
GtkWidget *drawing_area;
GtkWidget *dialog;

GtkEntry *entryStep;
GtkEntry *entryDegrees;
GtkEntry *entryNameNewObject;


const gchar *entryStepText;
const gchar *entryDegreesText;
const gchar *entryObjectName;

/*Clear the surface, removing the scribbles*/
static void clear_surface (){
	cairo_t *cr;

	cr = cairo_create (surface);

	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint (cr);

	cairo_destroy (cr);
}

/*Creates the surface*/
static gboolean configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
	if (surface)
	cairo_surface_destroy (surface);

	surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget), 
		CAIRO_CONTENT_COLOR,
		gtk_widget_get_allocated_width (widget),
		gtk_widget_get_allocated_height (widget));
	clear_surface ();
	return TRUE;
}

/* Redraw the screen from the surface */
static gboolean draw_cb (GtkWidget *widget, cairo_t   *cr,  gpointer   data){
	cairo_set_source_surface (cr, surface, 0, 0);
	cairo_paint (cr);

	return FALSE;
}

// ///////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////
// Functions that will be called by the buttons from the main window
// ///////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////

/*Function that will be called when the button up is pressed*/
extern "C" G_MODULE_EXPORT void btn_up_clicked(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 10, 10);
	cairo_line_to(cr, 20, 10);
	cairo_line_to(cr, 20, 20);
	cairo_line_to(cr, 10, 20);
	cairo_line_to(cr, 10, 10);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
} 


/*Function that will be called when the button left is pressed*/
extern "C" G_MODULE_EXPORT void btn_left_clicked(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 200, 10);
	cairo_line_to(cr, 300, 50);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
} 

/*Function that will be called when the button down is pressed*/
extern "C" G_MODULE_EXPORT void btn_down_clicked(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 100, 10);
	cairo_line_to(cr, 300, 80);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
} 

/*Function that will be called when the button right is pressed*/
extern "C" G_MODULE_EXPORT void btn_right_clicked(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 500, 10);
	cairo_line_to(cr, 300, 650);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
} 


 /*Function that will be called when the button out is pressed*/
extern "C" G_MODULE_EXPORT void btn_out_clicked(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 20, 10);
	cairo_line_to(cr, 10, 100);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
} 


  /*Function that will be called when the button get_window is pressed*/
extern "C" G_MODULE_EXPORT void btn_get_window_clicked(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 20, 10);
	cairo_line_to(cr, 30, 850);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
}

 /*Function that will be called when the button parallel change state*/
extern "C" G_MODULE_EXPORT void btn_parallel_actived(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 20, 50);
	cairo_line_to(cr, 130, 160);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
}

 /*Function that will be called when the button parallel change state*/
extern "C" G_MODULE_EXPORT void btn_ok_insert_actived(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 20, 50);
	cairo_line_to(cr, 130, 160);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
}

 /*Function that will be called when the button x is pressed*/
extern "C" G_MODULE_EXPORT void btn_x_clicked(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 20, 100);
	cairo_line_to(cr, 400, 50);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
} 

 /*Function that will be called when the button y is pressed*/
extern "C" G_MODULE_EXPORT void btn_y_clicked(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 20, 100);
	cairo_line_to(cr, 30, 500);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
} 

 /*Function that will be called when the button z is pressed*/
extern "C" G_MODULE_EXPORT void btn_z_clicked(){
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 20, 40);
	cairo_line_to(cr, 30, 250);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
} 
// ///////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////
// Function that will display the dialog to insert new objects
// ///////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////

/*Function that will display the window to insert new objects*/
extern "C" G_MODULE_EXPORT void quick_message () {
  	gtk_widget_show(dialog);
}

// // ///////////////////////////////////////////////////////////////////////
// // ///////////////////////////////////////////////////////////////////////
// // Functions that will get the text from dialog screen
// // ///////////////////////////////////////////////////////////////////////
// // ///////////////////////////////////////////////////////////////////////

/* Function that get the value put in the field EntryStepSize from GUI*/ 
extern "C" G_MODULE_EXPORT void get_text_step()
{
    /* cast the data back to a GtkEntry*  */
    entryStepText = gtk_entry_get_text (entryStep);
    g_print ("Step: %s\n", entryStepText);
}

/* Function that get the value put in the field entryDegreesText from GUI*/ 
extern "C" G_MODULE_EXPORT void get_text_degrees()
{
    /* cast the data back to a GtkEntry*  */
    entryDegreesText = gtk_entry_get_text (entryDegrees);
    g_print ("Degrees: %s\n", entryDegreesText);
}

/* Function that get the value put in the field entryDegreesText from GUI*/ 
extern "C" G_MODULE_EXPORT void get_text_name_new_object()
{
    /* cast the data back to a GtkEntry*  */
    entryObjectName = gtk_entry_get_text (entryDegrees);
    g_print ("Name: %s\n", entryObjectName);
}

int main(int argc, char *argv[]){
	GtkBuilder  *gtkBuilder;
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "Screen1_test_CG.glade", NULL);

	window_widget = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "MainWindow") );
	drawing_area = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area") );
	dialog = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "dialog1") );

	g_signal_connect (drawing_area, "draw", G_CALLBACK (draw_cb), NULL);
	g_signal_connect (drawing_area,"configure-event", G_CALLBACK (configure_event_cb), NULL);
	
	entryStep = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryStepSize"));
	entryDegrees = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryDegreesSize"));
	entryNameNewObject = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryNameNewObject"));

	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main ();
	return 0;
}
 

