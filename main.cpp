#include <gtk/gtk.h>
#include <iostream>
#include <vector>

#include "include/DisplayFile.h"

static cairo_surface_t *surface = NULL;

GtkBuilder  *gtkBuilder;

GtkWidget *window_widget;
GtkWidget *drawing_area;
GtkWidget *windowInsertion;
GtkWidget *text_view;
GtkWidget *scrolled_window;

GtkTextView *showCommandsInserted;

GtkTextBuffer *buffer;

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
static gboolean repaintWindow (GtkWidget *widget, cairo_t   *cr,  gpointer   data){
	cairo_set_source_surface (cr, surface, 0, 0);
	cairo_paint (cr);

	return FALSE;
}

extern "C" G_MODULE_EXPORT void insert_new_object_window () {
	printCommandLogs("insert_new_object_window\n");
  	gtk_widget_show(windowInsertion);
}

extern "C" G_MODULE_EXPORT void get_text_step(){
	printCommandLogs("get_text_step\n");
	GtkEntry *entryStep = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryStepSize"));
    const char *entryStepText = (char*) gtk_entry_get_text (entryStep);
    printf("Step: %d\n", atoi(entryStepText) );
}

extern "C" G_MODULE_EXPORT void get_text_degrees(){
	printCommandLogs("get_text_degrees\n");
	GtkEntry *entryDegrees = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryDegreesSize"));
    const char *entryDegreesText = gtk_entry_get_text (entryDegrees);
    printf("Degrees: %f\n", atof(entryDegreesText));
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_point_actived(){
	printCommandLogs("btn_ok_insert_point_actived\n");

	GtkEntry *entryNameNewPoint =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameNewPoint"));
	GtkEntry *entryXPoint =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryXPoint"));
	GtkEntry *entryYPoint =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryYPoint"));
	// GtkEntry *entryZPoint =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZPoint"));

	const char *entryPointName = gtk_entry_get_text (entryNameNewPoint);
	const char *entryXPointAux = gtk_entry_get_text (entryXPoint);
	const char *entryYPointAux = gtk_entry_get_text (entryYPoint);
	// const char *entryZPointAux = gtk_entry_get_text (entryZPoint);

	double XPoint = atof(entryXPointAux);
	double YPoint = atof(entryYPointAux);
	// double zPoint= atof(entryZPointAux);

	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_move_to(cr, XPoint, YPoint);
	cairo_line_to (cr, XPoint +1.0, YPoint +1.0);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
	repaintWindow(window_widget, cr, NULL);
	gtk_widget_hide(windowInsertion);
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_line_actived(){
	printCommandLogs("btn_ok_insert_line_actived\n");

	GtkEntry *entryNameNewLine = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameNewLine"));
	GtkEntry *entryX1Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryX1Line"));
	GtkEntry *entryY1Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryY1Line"));
	// GtkEntry *entryZ1Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZ1Line"));
	GtkEntry *entryX2Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryX2Line"));
	GtkEntry *entryY2Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryY2Line"));
	// GtkEntry *entryZ2Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZ2Line"));

	const char *entryLineName = gtk_entry_get_text (entryNameNewLine);
	const char *entryX1LineAux = gtk_entry_get_text (entryX1Line);
	const char *entryY1LineAux = gtk_entry_get_text (entryY1Line);
	// const char *entryZ1LineAux = gtk_entry_get_text (entryZ1Line);
	const char *entryX2LineAux = gtk_entry_get_text (entryX2Line);
	const char *entryY2LineAux = gtk_entry_get_text (entryY2Line);
	// const char *entryZ2LineAux = gtk_entry_get_text (entryZ2Line);

	double X1Line = atof(entryX1LineAux);
	double Y1Line = atof(entryY1LineAux);
	// double Z1Line= atof(entryZ1LineAux);
	double X2Line= atof(entryX2LineAux);
	double Y2Line= atof(entryY2LineAux);
	// double Z2Line= atof(entryZ2LineAux);

	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_set_line_width(cr, 1);
	cairo_move_to(cr, X1Line, Y1Line);
	cairo_line_to (cr, X2Line, Y2Line);
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_widget);
	repaintWindow(window_widget, cr, NULL);
	gtk_widget_hide(windowInsertion);
}

void printCommandLogs(const char* text) {
    GtkTextIter log_iter;
    GtkTextMark *log_mark = gtk_text_buffer_get_insert(buffer);
    gtk_text_buffer_get_iter_at_mark (buffer, &log_iter, log_mark);
    gtk_text_buffer_insert(buffer, &log_iter, text, -1);
    gtk_text_view_scroll_to_mark(showCommandsInserted, log_mark, 0, false, 0, 0);
}

extern "C" G_MODULE_EXPORT void btn_up_clicked(){
	printCommandLogs("btn_up_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_left_clicked(){
	printCommandLogs("btn_left_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_down_clicked(){
	printCommandLogs("btn_down_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_right_clicked(){
	printCommandLogs("btn_right_clicked\n");
}

extern "C" G_MODULE_EXPORT void btn_out_clicked(){
	printCommandLogs("btn_out_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_get_window_clicked(){
	printCommandLogs("btn_get_window_clicked\n");
}

extern "C" G_MODULE_EXPORT void btn_parallel_actived(){
	printCommandLogs("btn_parallel_actived\n");
}

extern "C" G_MODULE_EXPORT void btn_x_clicked(){
	printCommandLogs("btn_x_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_y_clicked(){
	printCommandLogs("btn_y_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_z_clicked(){
	printCommandLogs("btn_z_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_zoom_in_clicked(){
	printCommandLogs("btn_zoom_in_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_zoom_out_clicked(){
	printCommandLogs("btn_zoom_out_clicked\n");
} 

int main(int argc, char *argv[]){
	
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "mainwindow.glade", NULL);

	window_widget = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "MainWindow") );
	drawing_area = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area") );
	windowInsertion = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "WindowInsertion") );
	showCommandsInserted = GTK_TEXT_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "textview1"));

	buffer = gtk_text_buffer_new(NULL);
	gtk_text_view_set_buffer(showCommandsInserted, buffer);
	gtk_text_view_set_wrap_mode (showCommandsInserted, GTK_WRAP_NONE); 

	g_signal_connect (drawing_area, "draw", G_CALLBACK (repaintWindow), NULL);
	g_signal_connect (drawing_area,"configure-event", G_CALLBACK (configure_event_cb), NULL);

	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main ();
	return 0;
}