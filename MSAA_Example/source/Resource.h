#pragma once


//basic interface for resources(e.g. buffers, shaders, textures, etc.)
class Resource {

public:
	//create the resource
	virtual void Make() = 0;
	//bind it to the program/pipeline
	virtual void SetToPipeline() = 0;
	
};