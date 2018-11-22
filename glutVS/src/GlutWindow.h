#pragma once

#include <vector>
#include <set>
#include <memory>

#include "Camera.h"
#include "Drawable.h"
#include "Axis.h"

class GlutWindow
{
public:
	static void init(){
		int i = INSTANCES.size() + 1;
		INSTANCES.push_back(GlutWindow(i));
	}

	static GlutWindow& get(int index) {
		return INSTANCES[index-1];
	}

	static void toggle() {
		active++;
		active %= INSTANCES.size();
		glutSetWindow(active + 1);
	}


	~GlutWindow();

	// glut triggered functions
	void display();
	void idleFunc();
	void keyboardFunc(unsigned char key, int x, int y);
	void keyboardUpFunc(unsigned char key, int x, int y);
	void specialFunc(unsigned char key, int x, int y);
	void specialUpFunc(unsigned char key, int x, int y);
	void mouseFunc(int button, int state, int x, int y);

private:
	static int active;


	static std::vector<GlutWindow> INSTANCES;

	int index;

	GlutWindow(int index);

	Axis axis;

	void initialize();

	// previously: list of bools for each key, init with all false
	// replaced with set of keys with 'true' value
	std::set<unsigned char> keys; 
	std::set<unsigned char> specialkeys;

	std::shared_ptr<Camera> camera;
};

