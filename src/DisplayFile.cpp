#include "../include/DisplayFile.hpp"

bool DisplayFile::addObjectInTheWorld(Objeto* obj){
	return objectsInTheWorld.insert(std::make_pair(obj->getName(), obj)).second;
}

void DisplayFile::removeObjectFromTheWorld(std::string objName){
	objectsInTheWorld.erase(objName);
}

Objeto* DisplayFile::getTheObjectFromTheWorld(std::string objName){
	return objectsInTheWorld.find(objName)->second;
}

std::unordered_map<std::string, Objeto*> DisplayFile::getAllObjectsFromTheWorld(){
	return objectsInTheWorld;
}	
