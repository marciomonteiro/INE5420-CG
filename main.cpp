#include <gtk/gtk.h>
#include <iostream>
#include <vector>


#include "include/DisplayFile.h"


static cairo_surface_t *surface = NULL;

GtkWidget *window_widget;
GtkWidget *drawing_area;
GtkWidget *windowInsertion;

GtkTreeModel* objectListTree;


double windowSizeStep = 100;
double zoomStepSize = 2;

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

extern "C" G_MODULE_EXPORT void btn_up_clicked(){
	printf("btn_up_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_left_clicked(){
	printf("btn_left_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_down_clicked(){
	printf("btn_down_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_right_clicked(){
	printf("btn_right_clicked\n");
}

extern "C" G_MODULE_EXPORT void btn_out_clicked(){
	printf("btn_out_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_get_window_clicked(){
	printf("btn_get_window_clicked\n");
}

extern "C" G_MODULE_EXPORT void btn_parallel_actived(){
	printf("btn_parallel_actived\n");
}

extern "C" G_MODULE_EXPORT void btn_x_clicked(){
	printf("btn_x_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_y_clicked(){
	printf("btn_y_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_z_clicked(){
	printf("btn_z_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_zoom_in_clicked(){
	printf("btn_zoom_in_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_zoom_out_clicked(){
	printf("btn_zoom_out_clicked\n");
} 

extern "C" G_MODULE_EXPORT void btn_ok_insert_point_actived(){
	printf("btn_ok_insert_point_actived\n");
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
	printf("btn_ok_insert_line_actived\n");
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
extern "C" G_MODULE_EXPORT void insert_new_object_window () {
	printf("insert_new_object_window\n");
  	gtk_widget_show(windowInsertion);
}
static gboolean add_object_on_list_to_store(const std::string name, const char* type){
	GtkListStore *listToStore = GTK_LIST_STORE(objectListTree);
	GtkTreeIter it;

	gtk_list_store_append(listToStore, &it);
	gtk_list_store_set(listToStore, &it, 0, name.c_str(), 1, type, -1);
}

// // ///////////////////////////////////////////////////////////////////////
// // ///////////////////////////////////////////////////////////////////////
// // Functions that will get the text from windowInsertion screen
// // ///////////////////////////////////////////////////////////////////////
// // ///////////////////////////////////////////////////////////////////////

/* Function that get the value put in the field EntryStepSize from GUI*/ 
extern "C" G_MODULE_EXPORT void get_text_step(){
	printf("get_text_step\n");
    entryStepText = gtk_entry_get_text (entryStep);
    g_print ("Step: %s\n", entryStepText);
}

/* Function that get the value put in the field entryDegreesText from GUI*/ 
extern "C" G_MODULE_EXPORT void get_text_degrees(){
	printf("get_text_degrees\n");
    entryDegreesText = gtk_entry_get_text (entryDegrees);
    g_print ("Degrees: %s\n", entryDegreesText);
}

int main(int argc, char *argv[]){
	GtkBuilder  *gtkBuilder;
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "mainwindow.glade", NULL);

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

	// Tree object list
	objectListTree = gtk_tree_view_get_model(GTK_TREE_VIEW( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "ObjectTreeViewList" ) ));

	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main ();
	return 0;
}
 

