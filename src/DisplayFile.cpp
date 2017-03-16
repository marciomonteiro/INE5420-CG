#include "DisplayFile.h"

DisplayFile::DisplayFile(){
	
}
DisplayFile::~DisplayFile(){
	
}

bool DisplayFile::addObjectInTheWorld(Objeto* obj){
	return objectsInTheWorld.insert(std::make_pair(obj->getName(), obj)).second;
}

void DisplayFile::removeObjectFromTheWorld(std::string objName){
	objectsInTheWorld.erase(objName);
}

Objeto::Objeto* DisplayFile::getTheObjectFromTheWorld(std::string objName){
	return objectsInTheWorld.find(objName);
}

std::unordered_map<std::string, Objeto::Objeto*> DisplayFile::getAllObjectsFromTheWorld(){
	return objectsInTheWorld;
}	
