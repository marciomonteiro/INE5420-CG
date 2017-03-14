#include <gtk/gtk.h>
#include <iostream>
#include <vector>

static cairo_surface_t *surface = NULL;

GtkWidget *window_widget;
GtkWidget *drawing_area;
GtkWidget *windowInsertion;

GtkEntry *entryStep;
GtkEntry *entryDegrees;

// Point
GtkEntry *entryNameNewPoint;
GtkEntry *entryXPoint;
GtkEntry *entryYPoint;
GtkEntry *entryZPoint;

// Line
GtkEntry *entryNameNewLine;
GtkEntry *entryX1Line;
GtkEntry *entryY1Line;
GtkEntry *entryZ1Line;
GtkEntry *entryX2Line;
GtkEntry *entryY2Line;
GtkEntry *entryZ2Line;

// GtkEntry *entryNameNew???;
// GtkEntry *entryNameNew???;
// GtkEntry *entryNameNew???;
// GtkEntry *entryNameNew???;
// GtkEntry *entryNameNew???;
// GtkEntry *entryNameNew???;
// GtkEntry *entryNameNew???;
// GtkEntry *entryNameNew???;
// GtkEntry *entryNameNew???;


const gchar *entryStepText;
const gchar *entryDegreesText;

// point name and position
const gchar *entryPointName;
const gchar *entryXPointAux;
const gchar *entryYPointAux;
const gchar *entryZPointAux;

// line name and points
const gchar *entryLineName;
const gchar *entryX1LineAux;
const gchar *entryY1LineAux;
const gchar *entryZ1LineAux;
const gchar *entryX2LineAux;
const gchar *entryY2LineAux;
const gchar *entryZ2LineAux;

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


extern "C" G_MODULE_EXPORT void btn_ok_insert_point_actived(){
	// Change this code to draw one dot.
	entryPointName = gtk_entry_get_text (entryNameNewPoint);
	entryXPointAux = gtk_entry_get_text (entryXPoint);
	entryYPointAux = gtk_entry_get_text (entryYPoint);
	g_print ("Point: %s\tX: %s\tY: %s\n", entryPointName, entryXPointAux, entryYPointAux);
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, 0, 0);
	cairo_line_to (cr, (double) *entryXPointAux *2, (double) *entryYPointAux *2);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_line_actived(){
	// Change this code to draw one dot.
	entryLineName = gtk_entry_get_text (entryNameNewLine);
	entryX1LineAux = gtk_entry_get_text (entryX1Line);
	entryY1LineAux = gtk_entry_get_text (entryY1Line);
	entryX2LineAux = gtk_entry_get_text (entryX2Line);
	entryY2LineAux = gtk_entry_get_text (entryY2Line);
	g_print ("Line: %s\tX1: %s\tY1: %s\tX2: %s\tY2: %s\n", entryLineName, entryX1LineAux, entryY1LineAux, entryX2LineAux, entryY2LineAux);
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, (double) *entryX1LineAux, (double) *entryY1LineAux);
	cairo_line_to (cr, (double) *entryX2LineAux, (double) *entryY2LineAux);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
}
// ///////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////
// Function that will display the windowInsertion to insert new objects
// ///////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////

/*Function that will display the window to insert new objects*/
extern "C" G_MODULE_EXPORT void quick_message () {
  	gtk_widget_show(windowInsertion);
}

// // ///////////////////////////////////////////////////////////////////////
// // ///////////////////////////////////////////////////////////////////////
// // Functions that will get the text from windowInsertion screen
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

int main(int argc, char *argv[]){
	GtkBuilder  *gtkBuilder;
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "Screen1_test_CG.glade", NULL);

	window_widget = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "MainWindow") );
	drawing_area = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area") );
	windowInsertion = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "WindowInsertion") );

	g_signal_connect (drawing_area, "draw", G_CALLBACK (draw_cb), NULL);
	g_signal_connect (drawing_area,"configure-event", G_CALLBACK (configure_event_cb), NULL);
	
	// size of step
	entryStep = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryStepSize"));
	
	// degree to change
	entryDegrees = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryDegreesSize"));
	
	// Point
	entryNameNewPoint = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryNameNewPoint"));
	entryXPoint = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryXPoint"));
	entryYPoint = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryYPoint"));
	entryZPoint = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryZPoint"));
	
	// Line 
	entryNameNewLine = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryNameNewLine"));
	entryX1Line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryX1Line"));
	entryY1Line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryY1Line"));
	entryZ1Line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryZ1Line"));
	entryX2Line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryX2Line"));
	entryY2Line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryY2Line"));
	entryZ2Line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "EntryZ2Line"));

	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main ();
	return 0;
}
 

