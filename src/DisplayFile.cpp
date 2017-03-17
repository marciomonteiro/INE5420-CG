#include "DisplayFile.hpp"

bool DisplayFile::addObjectInTheWorld(Objeto* obj){
	if (objectsInTheWorld.insert(std::make_pair(obj->getName(), obj)).second){
		std::cout<<"DisplayFile::addObjectInTheWorld: "<<obj->getName()<<std::endl;
		return true;
	}
	std::cout<<"false DisplayFile::addObjectInTheWorld: "<<obj->getName()<<std::endl;
	return false;
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
