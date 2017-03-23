#include <gtk/gtk.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

#include "Window.hpp"
#include "World.hpp"
#include "Viewport.hpp"
#include "DisplayFile.hpp"
#include "Objeto.hpp"
#include "Transformacao2D.hpp"
#include "formas/Ponto.hpp"
#include "formas/Linha.hpp"
#include "formas/Poligono.hpp"

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
Transformacao2D *transformador;

//Gtk and beyond
GtkBuilder *gtkBuilder;

GtkWidget *window_widget;

std::vector<Coordenadas> wireframeCoords;

//RightPanel
GtkWidget *drawing_area;
GtkTextView *outputCommandsShell;

//WindowInsertionPanel
GtkWidget *windowInsertion;
GtkWidget *windowRemove;
GtkWidget *windowTranslacao;
GtkWidget *windowEscalona;
GtkWidget *windowListaObjetos;
GtkWidget *windowRotaciona;

GtkTextBuffer *buffer;

Coordenadas inicio = Coordenadas(0.0,0.0,0.0,0.0);
Coordenadas fim = Coordenadas(600.0,600.0,0.0,0.0);

static gboolean drawWindow (GtkWidget *widget, cairo_t *cr, gpointer data){
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);
  return FALSE;
}

/**
 * Toda vez que a função draw é chamada, ativa essa função.
 */
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);

	DisplayFile * aux = world->getDisplayfile();
	std::unordered_map<std::string, Objeto*> objetos = aux->getAllObjectsFromTheWorld();

	std::string print = "";

	for (auto it = objetos.begin(); it != objetos.end(); ++it){
		print.append(it->second->getName());
		print.append("\n");
	}

	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(windowListaObjetos));
	gtk_text_buffer_set_text(buffer, print.c_str(), -1);
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
	viewportP->transformada(cr, *(windowP->getInicioDaWindow()), *(windowP->getFimDaWindow()), world->getDisplayfile());
	gtk_widget_queue_draw (drawing_area);
}

void printCommandLogs(const char* text) {
	GtkTextIter it;
	GtkTextMark *textMarks = gtk_text_buffer_get_insert(buffer);
	gtk_text_buffer_get_iter_at_mark (buffer, &it, textMarks);
	gtk_text_buffer_insert(buffer, &it, text, -1);
	gtk_text_view_scroll_to_mark(outputCommandsShell, textMarks, 0, false, 0, 0);
}

extern "C" G_MODULE_EXPORT void btn_cancel_insertion_actived () {
	printCommandLogs("btn_cancel_insertion_actived\n");
	gtk_widget_hide(windowInsertion);
}

extern "C" G_MODULE_EXPORT void insert_new_object_window () {
	printCommandLogs("insert_new_object_window\n");
	gtk_widget_show(windowInsertion);
}

extern "C" G_MODULE_EXPORT void remove_object_window () {
	printCommandLogs("remove_object_window\n");
	gtk_widget_show(windowRemove);
}

extern "C" G_MODULE_EXPORT void btn_cancel_translada_actived () {
	printCommandLogs("btn_cancel_translada_actived\n");
	gtk_widget_hide(windowTranslacao);
}

extern "C" G_MODULE_EXPORT void translada_object_window () {
	printCommandLogs("translada_object_window\n");
	gtk_widget_show(windowTranslacao);
}

extern "C" G_MODULE_EXPORT void btn_cancel_escala_actived () {
	printCommandLogs("btn_cancel_escala_actived\n");
	gtk_widget_hide(windowEscalona);
}

extern "C" G_MODULE_EXPORT void escala_object_window () {
	printCommandLogs("escala_object_window\n");
	gtk_widget_show(windowEscalona);
}

extern "C" G_MODULE_EXPORT void btn_cancel_rotaciona_actived () {
	printCommandLogs("btn_cancel_rotaciona_actived\n");
	gtk_widget_hide(windowRotaciona);
}

extern "C" G_MODULE_EXPORT void rotaciona_object_window () {
	printCommandLogs("rotaciona_object_window\n");
	gtk_widget_show(windowRotaciona);
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

extern "C" G_MODULE_EXPORT void btn_remove_object_actived(){
	printCommandLogs("btn_remove_object_actived\n");
	GtkEntry *entryStep = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "RemoveObjectName"));
	const char *entryStepText = (char*) gtk_entry_get_text (entryStep);
	gtk_widget_hide(windowRemove);
	if (!world->getDisplayfile()->isEmpty())
	{
		world->removeObjetosNoMundo(entryStepText);
		repaintWindow ();
	}
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

	Ponto * ponto = new Ponto(std::string(entryPointName), "Ponto", std::vector<Coordenadas>({Coordenadas(XPoint, YPoint, 0, 0)}));
	gtk_widget_hide(windowInsertion);
	world->adicionaObjetosNoMundo(ponto);
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

	Linha * linha = new Linha(std::string(entryLineName), "Linha", std::vector<Coordenadas>({Coordenadas(X1Line, Y1Line, 0, 0),Coordenadas(X2Line, Y2Line, 0, 0)}));
	gtk_widget_hide(windowInsertion);
	world->adicionaObjetosNoMundo(linha);
	repaintWindow ();
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_wireframe_actived(){
	printCommandLogs("btn_ok_insert_wireframe_actived\n");

	GtkEntry *entryNameNewWireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameNewWireframe"));
	const char *entryWireframeName = gtk_entry_get_text (entryNameNewWireframe);
	wireframeCoords.push_back(wireframeCoords.front());
	Poligono * poligono = new Poligono(std::string(entryWireframeName), "Poligono", wireframeCoords);
	gtk_widget_hide(windowInsertion);
	world->adicionaObjetosNoMundo(poligono);
	repaintWindow ();
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_coords_wireframe_actived(){
	printCommandLogs("btn_ok_insert_coords_wireframe_actived\n");
	
	GtkEntry *entryX1Wireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryX1Wireframe"));
	GtkEntry *entryY1Wireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryY1Wireframe"));
	// GtkEntry *entryZ1Wireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZ1Wireframe"));

	const char *entryX1WireframeAux = gtk_entry_get_text (entryX1Wireframe);
	const char *entryY1WireframeAux = gtk_entry_get_text (entryY1Wireframe);
	// const char *entryZ1WireframeAux = gtk_entry_get_text (entryZ1Wireframe);

	double X1Wireframe = atof(entryX1WireframeAux);
	double Y1Wireframe = atof(entryY1WireframeAux);
	// double Z1Wireframe= atof(entryZ1WireframeAux);

	wireframeCoords.push_back(Coordenadas(X1Wireframe, Y1Wireframe, 0.0, 0.0));
}

extern "C" G_MODULE_EXPORT void btn_ok_translacao_objeto(){
	printCommandLogs("btn_ok_translacao_objeto\n");
	
	GtkEntry *entryNameObjeto = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameObjeto"));
	GtkEntry *entryXTranslacao = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryXTranslacao"));
	GtkEntry *entryYTranslacao = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryYTranslacao"));
	// GtkEntry *entryZTranslacao = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZTranslacao"));

	const char *entryObjetoName = gtk_entry_get_text (entryNameObjeto);
	const char *entryXTranslacaoAux = gtk_entry_get_text (entryXTranslacao);
	const char *entryYTranslacaoAux = gtk_entry_get_text (entryYTranslacao);
	// const char *entryZTranslacaoAux = gtk_entry_get_text (entryZTranslacao);

	double XTranslacao = atof(entryXTranslacaoAux);
	double YTranslacao = atof(entryYTranslacaoAux);
	// double ZTranslacao = atof(entryZTranslacaoAux);

	gtk_widget_hide(windowTranslacao);
	world->transformarObjeto(std::string(entryObjetoName),transformador->translacao(XTranslacao, YTranslacao));
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_ok_escalona_objeto(){
	printCommandLogs("btn_ok_escalona_objeto\n");
	
	GtkEntry *entryNameObjeto = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameObjetoEsc"));
	GtkEntry *entryXEscalona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryXEscalona"));
	GtkEntry *entryYEscalona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryYEscalona"));
	// GtkEntry *entryZEscalona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZEscalona"));

	const char *entryObjetoName = gtk_entry_get_text (entryNameObjeto);
	const char *entryXEscalonaAux = gtk_entry_get_text (entryXEscalona);
	const char *entryYEscalonaAux = gtk_entry_get_text (entryYEscalona);
	// const char *entryZEscalonaAux = gtk_entry_get_text (entryZEscalona);

	double XEscalona = atof(entryXEscalonaAux);
	double YEscalona = atof(entryYEscalonaAux);
	// double ZEscalona = atof(entryZEscalonaAux);

	gtk_widget_hide(windowEscalona);
	world->scalonarObjeto(std::string(entryObjetoName),transformador->escalonamento(XEscalona, YEscalona));
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_ok_rotaciona_objeto(){
	printCommandLogs("btn_ok_rotaciona_objeto\n");
	
	GtkEntry *entryNameObjeto = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameObjetoRot"));
	GtkEntry *entryAngleRotaciona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "AngleToRotate"));
	const char *entryObjetoName = gtk_entry_get_text (entryNameObjeto);
	const char *entryAngleRotate = gtk_entry_get_text (entryAngleRotaciona);
	double angulo = atof(entryAngleRotate);

	GtkToggleButton *BotaoCentroDoMundo = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "botaoCentroDoMundo"));
	GtkToggleButton *BotaCentroDoObjeto = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "botaCentroDoObjeto"));
	gtk_widget_hide(windowRotaciona);

	if (gtk_toggle_button_get_active(BotaoCentroDoMundo)){
		Coordenadas centroDoMundo = Coordenadas(0.0,0.0,0.0,0.0);
		world->rotacionarObjeto(std::string(entryObjetoName), false, centroDoMundo, transformador->rotacao(angulo));
	}
	if (gtk_toggle_button_get_active(BotaCentroDoObjeto)){
		Objeto* ob = world->getDisplayfile()->getTheObjectFromTheWorld(std::string(entryObjetoName));
		world->rotacionarObjeto(std::string(entryObjetoName),false, ob->centroDoObjeto(), transformador->rotacao(angulo));
	} else {
		GtkEntry *entryXRotaciona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryXRotaciona"));
		GtkEntry *entryYRotaciona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryYRotaciona"));
		// GtkEntry *entryZRotaciona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZRotaciona"));
		const char *entryXRotacionaAux = gtk_entry_get_text (entryXRotaciona);
		const char *entryYRotacionaAux = gtk_entry_get_text (entryYRotaciona);
		// const char *entryZRotacionaAux = gtk_entry_get_text (entryZRotaciona);
		double XRotaciona = atof(entryXRotacionaAux);
		double YRotaciona = atof(entryYRotacionaAux);
		// double ZRotaciona = atof(entryZRotacionaAux);
		world->rotacionarObjeto(std::string(entryObjetoName),true, Coordenadas{XRotaciona, YRotaciona, 0.0,0.0}, transformador->rotacao(angulo));
	}
	repaintWindow();
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

extern "C" G_MODULE_EXPORT void btn_zoom_in_clicked(){
	printCommandLogs("btn_zoom_in_clicked\n");
	windowP->zoom(0.9);
	repaintWindow ();
}

extern "C" G_MODULE_EXPORT void btn_zoom_out_clicked(){
	printCommandLogs("btn_zoom_out_clicked\n");
	windowP->zoom(1.1);
	repaintWindow ();
}

extern "C" G_MODULE_EXPORT void btn_reset_zoom_actived(){
	printCommandLogs("btn_reset_zoom_actived\n");
	inicio = Coordenadas(0.0,0.0,0.0,0.0);
	fim = Coordenadas(600.0,600.0,0.0,0.0);
	repaintWindow ();
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_curve_actived(){
	printCommandLogs("btn_ok_insert_curve_actived\n");
}

// I don't know if this function is really necessary
extern "C" G_MODULE_EXPORT void btn_get_step_in_clicked(){
	printCommandLogs("btn_get_step_in_clicked\n");
}

// I don't know if this function is really necessary
extern "C" G_MODULE_EXPORT void btn_get_step_out_clicked(){
	printCommandLogs("btn_get_step_out_clicked\n");
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

int main(int argc, char *argv[]){
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "mainwindow.glade", NULL);
	window_widget = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "MainWindow") );
	drawing_area = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area") );
	windowInsertion = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "WindowInsertion") );
	windowRemove = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "removeObject") );
	outputCommandsShell = GTK_TEXT_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "OutputCommandsShell"));
	windowTranslacao = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "WindowTranslacao"));
	windowEscalona = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "WindowEscalonamento"));
	windowRotaciona = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "WindowRotaciona"));
	windowListaObjetos = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "ObjectsInTheWorldInterface"));

	gtk_text_view_set_editable(GTK_TEXT_VIEW(windowListaObjetos), FALSE);
	buffer = gtk_text_buffer_new(NULL);
	gtk_text_view_set_buffer(outputCommandsShell, buffer);
	gtk_text_view_set_wrap_mode(outputCommandsShell, GTK_WRAP_NONE);

	// inicializa o displayfile, viewport e window
	DisplayFile dp = DisplayFile();
	displayFile = &dp;
	Viewport vp = Viewport(inicio, fim);
	viewportP = &vp;
	Window cWindow = Window(&inicio, &fim, displayFile);
	windowP = &cWindow;
	World wd = World();
	world = &wd;
	Transformacao2D t = Transformacao2D();
	transformador = &t;

	g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw_event), NULL);
	g_signal_connect (drawing_area, "draw", G_CALLBACK (drawWindow), NULL);
	g_signal_connect (drawing_area,"configure-event", G_CALLBACK (configure_event_cb), NULL);

	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main ();
	return 0;
}