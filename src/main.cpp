/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $main.cpp
 *
 *  Created on: $13 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

#include "Window.hpp"
#include "World.hpp"
#include "Viewport.hpp"
#include "DisplayFile.hpp"
#include "Objeto.hpp"
#include "Transformacao2D.hpp"
#include "Transformacao3D.hpp"
#include "formas/Ponto.hpp"
#include "formas/Linha.hpp"
#include "formas/Poligono.hpp"
#include "formas/CurvaDeBezier.hpp"
#include "formas/CurvaBSpline.hpp"
#include "DescritorOBJ.hpp"

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
DescritorOBJ *descritor;

//Global Variables
std::vector<Coordenadas> wireframeCoords;
Coordenadas inicio = Coordenadas(0.0,0.0,0.0,1.0);
Coordenadas fim = Coordenadas(400.0,400.0,0.0,1.0);
double tamBorda = 10.0;
bool preencherPoligono = false;

//Gtk and beyond
GtkBuilder *gtkBuilder;
GtkWidget *window_widget;

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

static gboolean drawWindow (GtkWidget *widget, cairo_t *cr, gpointer data) {
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);
  return FALSE;
}

/* Toda vez que a função draw é chamada, ativa essa função.*/
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
	DisplayFile * aux = world->getDisplayfile();
	std::unordered_map<std::string, Objeto*> objetos = aux->getAllObjectsFromTheWorld();
	std::string print = "";
	for (auto it = objetos.begin(); it != objetos.end(); it++) {
		print.append(it->second->getName());
		print.append("\t");
		print.append(it->second->getTipo());
		print.append("\n");
	}

	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(windowListaObjetos));
	gtk_text_buffer_set_text(buffer, print.c_str(), -1);
	return FALSE;
}

/*Clear the surface, removing the scribbles*/
static void clear_surface () {
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint (cr);
	cairo_destroy (cr);
}

/*Creates the surface*/
static gboolean configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
	if (surface)
	cairo_surface_destroy (surface);
	surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
		CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width (widget),
		gtk_widget_get_allocated_height (widget));
	clear_surface ();
	return TRUE;
}

/* Redraw the screen from the surface */
void repaintWindow() {
	cairo_t *cr;
	clear_surface();
	cr = cairo_create (surface);
	Window::instancia().normalizaCoordenadasDoMundo();
	viewportP->desenhaEnquadramento(cr);
	for (auto obj : world->getDisplayfile()->instancia().getAllObjectsFromTheWorld()) {
		obj.second->clipa();
	}
	viewportP->transformada(cr, Coordenadas(-1.0,-1.0,0.0,1.0), Coordenadas(1.0,1.0,0.0,1.0), world->getDisplayfile());
	gtk_widget_queue_draw (drawing_area);
}

void printCommandLogs(const char* text) {
	GtkTextIter it;
	GtkTextMark *textMarks = gtk_text_buffer_get_insert(buffer);
	gtk_text_buffer_get_iter_at_mark (buffer, &it, textMarks);
	gtk_text_buffer_insert(buffer, &it, text, -1);
	gtk_text_view_scroll_to_mark(outputCommandsShell, textMarks, 0, false, 0, 0);
}

extern "C" G_MODULE_EXPORT void btn_rotate_window_left_clicked() {
	printCommandLogs("btn_rotate_window_left_clicked\n");
	Window::instancia().novoAngulo(10, 0, 0);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void check_box_fill_wireframe() {
	preencherPoligono = true;
}

extern "C" G_MODULE_EXPORT void check_box_cs_clippa_reta() {
	GtkToggleButton *botaoCS = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "cohen-sutherland"));
	GtkToggleButton *botaoLB = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "liang-barsky"));
	if (gtk_toggle_button_get_active(botaoCS)) {
		Algoritmos::setaMetodoClippingReta(true);
	}
	if (gtk_toggle_button_get_active(botaoLB)) {
		Algoritmos::setaMetodoClippingReta(false);
	}
}

extern "C" G_MODULE_EXPORT void btn_rotate_window_right_clicked() {
	printCommandLogs("btn_rotate_window_right_clicked\n");
	Window::instancia().novoAngulo(-10.0, 0.0, 0.0);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_save_file_obj_actived () {
	printCommandLogs("btn_save_file_obj_actived\n");
	GtkWidget *escolherArquivoParaSalvar;
	gint resposta;
	escolherArquivoParaSalvar = gtk_file_chooser_dialog_new("Save File",
		GTK_WINDOW(window_widget), GTK_FILE_CHOOSER_ACTION_SAVE,
		"_Cancel", GTK_RESPONSE_CANCEL,
		"_Open", GTK_RESPONSE_ACCEPT,
		NULL);
	resposta = gtk_dialog_run (GTK_DIALOG (escolherArquivoParaSalvar));
	if (resposta == GTK_RESPONSE_ACCEPT) {
		char *nomeDoArquivo;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (escolherArquivoParaSalvar);
		nomeDoArquivo = gtk_file_chooser_get_filename (chooser);
		descritor->leiaObjetoFromPath(nomeDoArquivo);
		for (auto &objetos : world->getDisplayfile()->instancia().getAllObjectsFromTheWorld())
			printCommandLogs(descritor->transcrevaObjeto(objetos.second, nomeDoArquivo).c_str());
		g_free (nomeDoArquivo);
	}
	gtk_widget_hide(escolherArquivoParaSalvar);
}

extern "C" G_MODULE_EXPORT void btn_open_file_obj_actived () {
	printCommandLogs("btn_open_file_obj_actived\n");
	GtkWidget *escolherArquivoParaAbrir;
	gint resposta;
	escolherArquivoParaAbrir = gtk_file_chooser_dialog_new("Open File",
		GTK_WINDOW(window_widget), GTK_FILE_CHOOSER_ACTION_OPEN,
		"_Cancel", GTK_RESPONSE_CANCEL,
		"_Open", GTK_RESPONSE_ACCEPT,
		NULL);
	resposta = gtk_dialog_run (GTK_DIALOG (escolherArquivoParaAbrir));
	if (resposta == GTK_RESPONSE_ACCEPT) {
		char *nomeDoArquivo;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (escolherArquivoParaAbrir);
		nomeDoArquivo = gtk_file_chooser_get_filename (chooser);
		printCommandLogs(descritor->leiaObjetoFromPath(nomeDoArquivo).c_str());
		Window::instancia().normalizaCoordenadasDoMundo();
		repaintWindow();
		g_free (nomeDoArquivo);
	}
	gtk_widget_hide(escolherArquivoParaAbrir);
}

extern "C" G_MODULE_EXPORT void btn_cancel_insertion_actived () {
	printCommandLogs("btn_cancel_insertion_actived\n");
	gtk_widget_hide(windowInsertion);
}

extern "C" G_MODULE_EXPORT void btn_cancel_remove_actived () {
	printCommandLogs("btn_cancel_remove_actived\n");
	gtk_widget_hide(windowRemove);
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

extern "C" G_MODULE_EXPORT void btn_up_clicked() {
	printCommandLogs("btn_up_clicked\n");
	Window::instancia().mover(0.0,10.0,0.0);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_down_clicked() {
	printCommandLogs("btn_down_clicked\n");
	Window::instancia().mover(0.0,-10.0,0.0);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_left_clicked() {
	printCommandLogs("btn_left_clicked\n");
	Window::instancia().mover(-10.0,0.0,0.0);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_right_clicked() {
	printCommandLogs("btn_right_clicked\n");
	Window::instancia().mover(10.0,0.0,0.0);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_zoom_in_clicked() {
	printCommandLogs("btn_zoom_in_clicked\n");
	Window::instancia().zoom(0.9);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_zoom_out_clicked() {
	printCommandLogs("btn_zoom_out_clicked\n");
	Window::instancia().zoom(1.1);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_reset_zoom_actived() {
	printCommandLogs("btn_reset_zoom_actived\n");
	inicio = Coordenadas(0.0,0.0,0.0,1.0);
	fim = Coordenadas(400.0,400.0,0.0,1.0);
	Window::instancia().setCoordsWindow(&inicio, &fim);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_rotate_left_by_clicked() {
	printCommandLogs("btn_rotate_left_by_clicked\n");
	double angulo = 0.0;
	GtkEntry *entryStep = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryStepSize"));
	const char *entryStepText = (char*) gtk_entry_get_text (entryStep);
	if (strcmp(entryStepText, "") == 0) {
		printCommandLogs("Erro: angulo não informado\n");
		return;
	}
	angulo = atof(entryStepText);
	Window::instancia().novoAngulo(angulo, 0.0, 0.0);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_rotate_right_by_clicked() {
	printCommandLogs("btn_rotate_right_by_clicked\n");
	double angulo = 0.0;
	GtkEntry *entryStep = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryStepSize"));
	const char *entryStepText = (char*) gtk_entry_get_text (entryStep);
	if (strcmp(entryStepText, "") == 0) {
		printCommandLogs("Erro: angulo não informado\n");
		return;
	}
	angulo = atof(entryStepText);
	Window::instancia().novoAngulo(-angulo, 0.0, 0.0);
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_remove_object_actived() {
	printCommandLogs("btn_remove_object_actived\n");
	GtkEntry *entryStep = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "RemoveObjectName"));
	const char *entryStepText = (char*) gtk_entry_get_text (entryStep);
	gtk_widget_hide(windowRemove);
	if (strcmp(entryStepText, "") == 0) {
		printCommandLogs("Erro: Nome do objeto não informado\n");
		return;
	}
	if (!world->getDisplayfile()->isEmpty()) {
		world->removeObjetosNoMundo(entryStepText);
		repaintWindow();
	}
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_point_actived() {
	printCommandLogs("btn_ok_insert_point_actived\n");
	GtkEntry *entryNameNewPoint =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameNewPoint"));
	GtkEntry *entryXPoint =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryXPoint"));
	GtkEntry *entryYPoint =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryYPoint"));
	GtkEntry *entryZPoint =  GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZPoint"));

	gtk_widget_hide(windowInsertion);
	const char *entryPointName = gtk_entry_get_text (entryNameNewPoint);
	if (strcmp(entryPointName, "") == 0) {
		printCommandLogs("Erro: Ponto sem nome\n");
		return;
	}
	const char *entryXPointAux = gtk_entry_get_text (entryXPoint);
	const char *entryYPointAux = gtk_entry_get_text (entryYPoint);
	const char *entryZPointAux = gtk_entry_get_text (entryZPoint);

	double XPoint = atof(entryXPointAux);
	double YPoint = atof(entryYPointAux);
	double zPoint= atof(entryZPointAux);

	Ponto * ponto = new Ponto(std::string(entryPointName), "Ponto", std::vector<Coordenadas>({Coordenadas(XPoint, YPoint, zPoint, 1.0)}));
	if (!world->adicionaObjetosNoMundo(ponto)) {
		printCommandLogs("Erro: Ponto já existe\n");
		return;
	}
	std::string ret = "btn_ok_insert_point_actived X: ";
	ret += entryXPointAux;
	ret += " Y: ";
	ret += entryYPointAux;
	ret += " Z: ";
	ret += entryZPointAux;
	ret += "\n";
	printCommandLogs(ret.c_str());
	ponto->clipa();
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_line_actived() {
	// printCommandLogs("btn_ok_insert_line_actived\n");

	GtkEntry *entryNameNewLine = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameNewLine"));
	GtkEntry *entryX1Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryX1Line"));
	GtkEntry *entryY1Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryY1Line"));
	GtkEntry *entryZ1Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZ1Line"));
	GtkEntry *entryX2Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryX2Line"));
	GtkEntry *entryY2Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryY2Line"));
	GtkEntry *entryZ2Line = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZ2Line"));

	gtk_widget_hide(windowInsertion);
	const char *entryLineName = gtk_entry_get_text (entryNameNewLine);
	if (strcmp(entryLineName, "") == 0) {
		printCommandLogs("Erro: Linha sem nome\n");
		return;
	}
	const char *entryX1LineAux = gtk_entry_get_text (entryX1Line);
	const char *entryY1LineAux = gtk_entry_get_text (entryY1Line);
	const char *entryZ1LineAux = gtk_entry_get_text (entryZ1Line);
	const char *entryX2LineAux = gtk_entry_get_text (entryX2Line);
	const char *entryY2LineAux = gtk_entry_get_text (entryY2Line);
	const char *entryZ2LineAux = gtk_entry_get_text (entryZ2Line);

	double X1Line = atof(entryX1LineAux);
	double Y1Line = atof(entryY1LineAux);
	double Z1Line= atof(entryZ1LineAux);
	double X2Line= atof(entryX2LineAux);
	double Y2Line= atof(entryY2LineAux);
	double Z2Line= atof(entryZ2LineAux);

	Linha * linha = new Linha(std::string(entryLineName), "Linha", std::vector<Coordenadas>({Coordenadas(X1Line, Y1Line, Z1Line, 1.0),Coordenadas(X2Line, Y2Line, Z2Line, 1.0)}));
	if (!world->adicionaObjetosNoMundo(linha)) {
		printCommandLogs("Erro: Linha já existe\n");
		return;
	}
	std::string ret = "btn_ok_insert_line_actived X1: ";
	ret += entryX1LineAux;
	ret += " Y1: ";
	ret += entryY1LineAux;
	ret += " Z1: ";
	ret += entryZ1LineAux;
	ret += " X2: ";
	ret += entryX2LineAux;
	ret += " Y2: ";
	ret += entryY2LineAux;
	ret += " Z2: ";
	ret += entryZ2LineAux;
	ret += "\n";
	printCommandLogs(ret.c_str());
	Window::instancia().normalizaCoordenadasDoMundo();
	linha->clipa();
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_curve_actived() {
	printCommandLogs("btn_ok_insert_curve_actived\n");

	GtkEntry *entryNameNewCurve = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameNewCurve"));
	const char *entryWireframeName = gtk_entry_get_text (entryNameNewCurve);
	gtk_widget_hide(windowInsertion);
	if (strcmp(entryWireframeName, "") == 0) {
		printCommandLogs("Erro: Curva sem nome\n");
		wireframeCoords.clear();
		return;
	}

	GtkToggleButton *BotaoBezier = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "buttonBezierCurve"));
	GtkToggleButton *BotaoBSpline = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "buttonBSplineCurve"));

	if (gtk_toggle_button_get_active(BotaoBezier)) {
		if(wireframeCoords.size()<4){
			printCommandLogs("Erro: Curva com menos de quatro pontos\n");
			wireframeCoords.clear();
			return;
		}
		CurvaDeBezier * curvaBezier = new CurvaDeBezier(std::string(entryWireframeName), "Curva", wireframeCoords);
		if (!world->adicionaObjetosNoMundo(curvaBezier)) {
			printCommandLogs("Erro: Curva já existe\n");
			wireframeCoords.clear();
			return;
		}
		wireframeCoords.clear();
		Window::instancia().normalizaCoordenadasDoMundo();
		curvaBezier->gerarPontosDaCurva();
	}
	if (gtk_toggle_button_get_active(BotaoBSpline)) {
		CurvaBSpline * curvaBSpline = new CurvaBSpline(std::string(entryWireframeName), "Curva", wireframeCoords);
		if (!world->adicionaObjetosNoMundo(curvaBSpline)) {
			printCommandLogs("Erro: Curva já existe\n");
			wireframeCoords.clear();
			return;
		}
		wireframeCoords.clear();
		Window::instancia().normalizaCoordenadasDoMundo();
		curvaBSpline->gerarPontosDaCurva();
	}
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_coords_curve_actived() {

	GtkEntry *entryX1Wireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryXCurve"));
	GtkEntry *entryY1Wireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryYCurve"));
	GtkEntry *entryZ1Wireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZCurve"));

	const char *entryX1WireframeAux = gtk_entry_get_text (entryX1Wireframe);
	const char *entryY1WireframeAux = gtk_entry_get_text (entryY1Wireframe);
	const char *entryZ1WireframeAux = gtk_entry_get_text (entryZ1Wireframe);

	double X1Wireframe = atof(entryX1WireframeAux);
	double Y1Wireframe = atof(entryY1WireframeAux);
	double Z1Wireframe= atof(entryZ1WireframeAux);
	std::string ret = "btn_ok_insert_coords_curve_actived X: ";
	ret += entryX1WireframeAux;
	ret += " Y: ";
	ret += entryY1WireframeAux;
	ret += " Z: ";
	ret += entryZ1WireframeAux;
	ret += "\n";
	printCommandLogs(ret.c_str());
	wireframeCoords.push_back(Coordenadas(X1Wireframe, Y1Wireframe, Z1Wireframe, 1.0));
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_wireframe_actived() {
	printCommandLogs("btn_ok_insert_wireframe_actived\n");

	GtkEntry *entryNameNewWireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameNewWireframe"));
	const char *entryWireframeName = gtk_entry_get_text (entryNameNewWireframe);
	gtk_widget_hide(windowInsertion);
	if (strcmp(entryWireframeName, "") == 0) {
		printCommandLogs("Erro: Poligono sem nome\n");
		wireframeCoords.clear();
		return;
	}
	wireframeCoords.push_back(wireframeCoords.front());
	Poligono * poligono = new Poligono(std::string(entryWireframeName), "Poligono", wireframeCoords, preencherPoligono);
	if (!world->adicionaObjetosNoMundo(poligono)) {
		printCommandLogs("Erro: Poligono já existe\n");
		wireframeCoords.clear();
		return;
	}
	wireframeCoords.clear();
	Window::instancia().normalizaCoordenadasDoMundo();
	preencherPoligono =  false;
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_ok_insert_coords_wireframe_actived() {

	GtkEntry *entryX1Wireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryX1Wireframe"));
	GtkEntry *entryY1Wireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryY1Wireframe"));
	GtkEntry *entryZ1Wireframe = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZ1Wireframe"));

	const char *entryX1WireframeAux = gtk_entry_get_text (entryX1Wireframe);
	const char *entryY1WireframeAux = gtk_entry_get_text (entryY1Wireframe);
	const char *entryZ1WireframeAux = gtk_entry_get_text (entryZ1Wireframe);

	double X1Wireframe = atof(entryX1WireframeAux);
	double Y1Wireframe = atof(entryY1WireframeAux);
	double Z1Wireframe= atof(entryZ1WireframeAux);

	std::string ret = "btn_ok_insert_coords_wireframe_actived X: ";
	ret += entryX1WireframeAux;
	ret += " Y: ";
	ret += entryY1WireframeAux;
	ret += " Z: ";
	ret += entryZ1WireframeAux;
	ret += "\n";
	printCommandLogs(ret.c_str());
	wireframeCoords.push_back(Coordenadas(X1Wireframe, Y1Wireframe, Z1Wireframe, 1.0));
}

extern "C" G_MODULE_EXPORT void btn_ok_translacao_objeto() {
	printCommandLogs("btn_ok_translacao_objeto\n");

	GtkEntry *entryNameObjeto = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameObjeto"));
	GtkEntry *entryXTranslacao = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryXTranslacao"));
	GtkEntry *entryYTranslacao = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryYTranslacao"));
	GtkEntry *entryZTranslacao = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZTranslacao"));

	const char *entryObjetoName = gtk_entry_get_text (entryNameObjeto);
	const char *entryXTranslacaoAux = gtk_entry_get_text (entryXTranslacao);
	const char *entryYTranslacaoAux = gtk_entry_get_text (entryYTranslacao);
	const char *entryZTranslacaoAux = gtk_entry_get_text (entryZTranslacao);

	double XTranslacao = atof(entryXTranslacaoAux);
	double YTranslacao = atof(entryYTranslacaoAux);
	double ZTranslacao = atof(entryZTranslacaoAux);

	gtk_widget_hide(windowTranslacao);
	if (strcmp(entryObjetoName, "") == 0) {
		printCommandLogs("Erro: Nome do objeto não informado\n");
		return;
	}
	// if (!world->objetoExisteNoMundo(entryObjetoName)){
	// 	printCommandLogs("Erro: Objeto não encontrado\n");
	// 	return;
	// }
	world->transformarObjeto(std::string(entryObjetoName),Transformacao2D::translacao(XTranslacao, YTranslacao));
	// 
	// Translacao em 3D
	// world->transformarObjeto(std::string(entryObjetoName),Transformacao3D::translacao(XTranslacao, YTranslacao, ZTranslacao));
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_ok_escalona_objeto() {
	printCommandLogs("btn_ok_escalona_objeto\n");

	GtkEntry *entryNameObjeto = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameObjetoEsc"));
	GtkEntry *entryXEscalona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryXEscalona"));
	GtkEntry *entryYEscalona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryYEscalona"));
	GtkEntry *entryZEscalona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZEscalona"));

	const char *entryObjetoName = gtk_entry_get_text (entryNameObjeto);
	const char *entryXEscalonaAux = gtk_entry_get_text (entryXEscalona);
	const char *entryYEscalonaAux = gtk_entry_get_text (entryYEscalona);
	const char *entryZEscalonaAux = gtk_entry_get_text (entryZEscalona);

	double XEscalona = atof(entryXEscalonaAux);
	double YEscalona = atof(entryYEscalonaAux);
	double ZEscalona = atof(entryZEscalonaAux);

	gtk_widget_hide(windowEscalona);
	if (strcmp(entryObjetoName, "") == 0) {
		printCommandLogs("Erro: Nome do objeto não informado\n");
		return;
	}
	// if (!world->objetoExisteNoMundo(entryObjetoName)){
	// 	printCommandLogs("Erro: Objeto não encontrado\n");
	// 	return;
	// }
	world->scalonarObjeto(std::string(entryObjetoName),Transformacao2D::escalonamento(XEscalona, YEscalona));
	// 
	// Escalonamento em 3D
	// world->scalonarObjeto(std::string(entryObjetoName),Transformacao3D::escalonamento(XEscalona, YEscalona, ZEscalona));
	repaintWindow();
}

extern "C" G_MODULE_EXPORT void btn_ok_rotaciona_objeto() {
	printCommandLogs("btn_ok_rotaciona_objeto\n");

	GtkEntry *entryNameObjeto = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryNameObjetoRot"));
	GtkEntry *entryAngleRotaciona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "AngleToRotate"));
	const char *entryObjetoName = gtk_entry_get_text (entryNameObjeto);
	const char *entryAngleRotate = gtk_entry_get_text (entryAngleRotaciona);
	gtk_widget_hide(windowRotaciona);
	double angulo = atof(entryAngleRotate);
	if (strcmp(entryObjetoName, "") == 0) {
		printCommandLogs("Erro: Nome do objeto não informado\n");
		return;
	}
	// if (!world->objetoExisteNoMundo(entryObjetoName)){
	// 	printCommandLogs("Erro: Objeto não encontrado\n");
	// 	return;
	// }
	GtkToggleButton *BotaoCentroDoMundo = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "botaoCentroDoMundo"));
	GtkToggleButton *BotaCentroDoObjeto = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "botaCentroDoObjeto"));

	// printCommandLogs("Erro: Objeto não encontrado\n");
	if (gtk_toggle_button_get_active(BotaoCentroDoMundo)) {
		Coordenadas centroDoMundo = Coordenadas(0.0,0.0,0.0,1.0);
		world->rotacionarObjeto(std::string(entryObjetoName), false, centroDoMundo, Transformacao2D::rotacao(angulo));
		// 
		// Rotação em 3D
		// world->rotacionarObjeto(std::string(entryObjetoName), false, centroDoMundo, Transformacao3D::rotacao(angulo));
		// 
	}
	if (gtk_toggle_button_get_active(BotaCentroDoObjeto)) {
		Objeto* ob = world->getDisplayfile()->getTheObjectFromTheWorld(std::string(entryObjetoName));
		world->rotacionarObjeto(std::string(entryObjetoName),false, ob->centroDoObjeto(), Transformacao2D::rotacao(angulo));
		// 
		// Rotação em 3D
		// world->rotacionarObjeto(std::string(entryObjetoName),false, ob->centroDoObjeto(), Transformacao3D::rotacao(angulo));
		// 
	} else {
		GtkEntry *entryXRotaciona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryXRotaciona"));
		GtkEntry *entryYRotaciona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryYRotaciona"));
		GtkEntry *entryZRotaciona = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EntryZRotaciona"));
		const char *entryXRotacionaAux = gtk_entry_get_text (entryXRotaciona);
		const char *entryYRotacionaAux = gtk_entry_get_text (entryYRotaciona);
		const char *entryZRotacionaAux = gtk_entry_get_text (entryZRotaciona);
		double XRotaciona = atof(entryXRotacionaAux);
		double YRotaciona = atof(entryYRotacionaAux);
		double ZRotaciona = atof(entryZRotacionaAux);
		world->rotacionarObjeto(std::string(entryObjetoName),true, Coordenadas{XRotaciona, YRotaciona, ZRotaciona,1.0}, Transformacao2D::rotacao(angulo));
		// 
		// Rotação em 3D
		// world->rotacionarObjeto(std::string(entryObjetoName),true, Coordenadas{XRotaciona, YRotaciona, ZRotaciona,1.0}, Transformacao3D::rotacao(angulo));
		// 
	}
	repaintWindow();
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "mainwindow.glade", NULL);
	window_widget = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "MainWindow"));
	drawing_area = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area"));
	windowInsertion = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "WindowInsertion"));
	windowRemove = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "removeObject"));
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
	Viewport vp = Viewport(Coordenadas(tamBorda, tamBorda, 0.0, 1.0),Coordenadas(fim.getX()-tamBorda, fim.getY()-tamBorda, 0.0, 1.0));
	viewportP = &vp;
	Window::instancia().setWindow(&inicio, &fim, displayFile);
	World wd = World();
	world = &wd;
	descritor = new DescritorOBJ(&wd);

	g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw_event), NULL);
	g_signal_connect(drawing_area, "draw", G_CALLBACK (drawWindow), NULL);
	g_signal_connect(drawing_area,"configure-event", G_CALLBACK (configure_event_cb), NULL);
	g_signal_connect(windowInsertion, "delete_event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
	g_signal_connect(windowRemove, "delete_event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
	g_signal_connect(outputCommandsShell, "delete_event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
	g_signal_connect(windowTranslacao, "delete_event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
	g_signal_connect(windowEscalona, "delete_event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
	g_signal_connect(windowRotaciona, "delete_event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);

	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main ();
	return 0;
}
