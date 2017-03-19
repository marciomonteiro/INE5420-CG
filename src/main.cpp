#include <gtk/gtk.h>
#include <stdlib.h>
#include <iostream>
#include <vector>


#include "Window.hpp"
#include "World.hpp"
#include "Viewport.hpp"
#include "DisplayFile.hpp"
#include "Objeto.hpp"
#include "formas/Ponto.hpp"
#include "formas/Linha.hpp"

/**
 * Note: You need to add the flag "-std=c++11" to the command "g++..."
 * in order to compile this program.
 *
 * Note 2: If you are trying to run it in Eclipse and get the "unordered_map"
 * could not be resolved, then follow these steps:
 * 	- Right-click the project and go to "Properties" C/C++ General -> Paths and Symbols
 * 	 	-> Symbols -> GNU C++.
 * 	- Click "Add..." and paste __GXX_EXPERIMENTAL_CXX0X__ into "Name" and leave "Value"
 * 		blank. Hit Apply, do whatever it asks you to do, then hit OK.
 *
 * 	Note 3: If you intend to run it manually, then go to the root folder of the project on terminal
 * 	and run the following commands:
 * 	$ make
 * 	$ ./exec
 */

static cairo_surface_t *surface = NULL;

//Our Classes
Window *windowP;
World *world;
Viewport *viewportP;
DisplayFile *displayFile;


//Gtk and beyond
GtkBuilder *gtkBuilder;

GtkWidget *window_widget;

//TreeList
GtkTreeStore *store;
GtkWidget *treeViewList;
GtkTreeViewColumn *column;
GtkCellRenderer *renderer;
enum{
	NOME_OBJETO,
	TIPO_OBJETO
};

//RightPanel
GtkWidget *drawing_area;
GtkTextView *outputCommandsShell;


//WindowInsertionPanel
GtkWidget *windowInsertion;

GtkTextBuffer *buffer;

static gboolean drawWindow (GtkWidget *widget, cairo_t *cr, gpointer data){
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);
  return FALSE;
}

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
		CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width (widget),
		gtk_widget_get_allocated_height (widget));
	clear_surface ();
	return TRUE;
}

/* Redraw the screen from the surface */
void repaintWindow (){
	cairo_t *cr;
	clear_surface();
	cr = cairo_create (surface);
	viewportP->transformada(cr, *(windowP->getInicioDaWindow()), *(windowP->getFimDaWindow()), displayFile);
	gtk_widget_queue_draw (drawing_area);
}

void printCommandLogs(const char* text) {
	GtkTextIter it;
	GtkTextMark *textMarks = gtk_text_buffer_get_insert(buffer);
	gtk_text_buffer_get_iter_at_mark (buffer, &it, textMarks);
	gtk_text_buffer_insert(buffer, &it, text, -1);
	gtk_text_view_scroll_to_mark(outputCommandsShell, textMarks, 0, false, 0, 0);
}

void setupTree(){
	store = gtk_tree_store_new (2, G_TYPE_STRING, G_TYPE_STRING);
	treeViewList = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
	g_object_unref (G_OBJECT (store));
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Name", renderer, "text", NOME_OBJETO, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treeViewList), column);
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Type", renderer, "text", TIPO_OBJETO, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treeViewList), column);
}

extern "C" G_MODULE_EXPORT void btn_cancel_insertion_actived () {
	printCommandLogs("btn_cancel_insertion_actived\n");
	gtk_widget_hide(windowInsertion);
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
	// printf("Degrees: %f\n", atof(entryDegreesText));
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

	//Arrumar quando adicionar Z e Aux
	Ponto * ponto = new Ponto(entryPointName, "Ponto", std::vector<Coordenadas>({Coordenadas(XPoint, YPoint, 0, 0)}));
	gtk_widget_hide(windowInsertion);
	displayFile->addObjectInTheWorld(ponto);

	repaintWindow ();
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


	//Arrumar quando adicionar Z e Aux
	Linha * linha = new Linha(entryLineName, "Linha", std::vector<Coordenadas>({Coordenadas(X1Line, Y1Line, 0, 0),Coordenadas(X2Line, Y2Line, 0, 0)}));
	gtk_widget_hide(windowInsertion);
	displayFile->addObjectInTheWorld(linha);

	repaintWindow ();
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_wireframe_actived(){
	printCommandLogs("btn_ok_insert_wireframe_actived\n");
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_curve_actived(){
	printCommandLogs("btn_ok_insert_curve_actived\n");
}

extern "C" G_MODULE_EXPORT void btn_up_clicked(){
	printCommandLogs("btn_up_clicked\n");
	windowP->mover(0,10,0);
	repaintWindow ();
}

extern "C" G_MODULE_EXPORT void btn_down_clicked(){
	printCommandLogs("btn_down_clicked\n");
	windowP->mover(0,-10,0);
	repaintWindow ();
}

extern "C" G_MODULE_EXPORT void btn_left_clicked(){
	printCommandLogs("btn_left_clicked\n");
	windowP->mover(-10,0,0);
	repaintWindow ();
}

extern "C" G_MODULE_EXPORT void btn_right_clicked(){
	printCommandLogs("btn_right_clicked\n");
	windowP->mover(10,0,0);
	repaintWindow ();
}

// I don't know if this function is really necessary
extern "C" G_MODULE_EXPORT void btn_get_step_in_clicked(){
	printCommandLogs("btn_get_step_in_clicked\n");
}

// I don't know if this function is really necessary
extern "C" G_MODULE_EXPORT void btn_get_step_out_clicked(){
	printCommandLogs("btn_get_step_out_clicked\n");
}

extern "C" G_MODULE_EXPORT void btn_zoom_in_clicked(){
	printCommandLogs("btn_zoom_in_clicked\n");
	windowP->zoom(1.1);
	repaintWindow ();
}

extern "C" G_MODULE_EXPORT void btn_zoom_out_clicked(){
	printCommandLogs("btn_zoom_out_clicked\n");
	windowP->zoom(0.9);
	repaintWindow ();
}

// I don't know if this function is really necessary
extern "C" G_MODULE_EXPORT void btn_x_clicked(){
	printCommandLogs("btn_x_clicked\n");
}

// I don't know if this function is really necessary
extern "C" G_MODULE_EXPORT void btn_y_clicked(){
	printCommandLogs("btn_y_clicked\n");
}

// I don't know if this function is really necessary
extern "C" G_MODULE_EXPORT void btn_z_clicked(){
	printCommandLogs("btn_z_clicked\n");
}

extern "C" G_MODULE_EXPORT void btn_get_window_clicked(){
	printCommandLogs("btn_get_window_clicked\n");
}

extern "C" G_MODULE_EXPORT void btn_parallel_actived(){
	printCommandLogs("btn_parallel_actived\n");
}

// // TO DO

// extern "C" G_MODULE_EXPORT void btn_ok_insert_wireframe_actived(){
// 	printCommandLogs("btn_ok_insert_wireframe_actived\n");
// 	gtk_widget_hide(windowInsertion);
// }

// // TO DO

// extern "C" G_MODULE_EXPORT void btn_ok_insert_curve_actived(){
// 	printCommandLogs("btn_ok_insert_curve_actived\n");
// 	gtk_widget_hide(windowInsertion);
// }


int main(int argc, char *argv[]){
	
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "mainwindow.glade", NULL);

	window_widget = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "MainWindow") );
	drawing_area = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area") );
	windowInsertion = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "WindowInsertion") );
	outputCommandsShell = GTK_TEXT_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "OutputCommandsShell"));

	buffer = gtk_text_buffer_new(NULL);
	gtk_text_view_set_buffer(outputCommandsShell, buffer);
	gtk_text_view_set_wrap_mode(outputCommandsShell, GTK_WRAP_NONE);

	// inicializa o displayfile, viewport e window
	Coordenadas inicio = Coordenadas(0.0,0.0,0.0,0.0);
	Coordenadas fim = Coordenadas(300.0,300.0,0.0,0.0);
	DisplayFile dp = DisplayFile();
	displayFile = &dp;
	Viewport vp = Viewport();
	viewportP = &vp;
	Window cWindow = Window(&inicio, &fim, displayFile);
	windowP = &cWindow;

	setupTree();
	g_signal_connect (drawing_area, "draw", G_CALLBACK (drawWindow), NULL);
	g_signal_connect (drawing_area,"configure-event", G_CALLBACK (configure_event_cb), NULL);

	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main ();
	return 0;
}
