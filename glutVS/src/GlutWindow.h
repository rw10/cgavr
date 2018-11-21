#pragma once

#include <vector>
#include <set>
#include <memory>

#include "Camera.h"
#include "Drawable.h"
#include "Block.h"

class GlutWindow
{
public:
	static void init() {
		INSTANCE = new GlutWindow();
	}

	static GlutWindow& get() {
		return *INSTANCE;
	}

	// glut triggered functions
	void display();
	void idleFunc();
	void keyboardFunc(unsigned char key, int x, int y);
	void keyboardUpFunc(unsigned char key, int x, int y);
	void specialFunc(unsigned char key, int x, int y);
	void specialUpFunc(unsigned char key, int x, int y);
	void mouseFunc(int button, int state, int x, int y);

private:
	static GlutWindow* INSTANCE;

	GlutWindow();
	~GlutWindow();

	// list of all drawn objects
	std::vector<std::shared_ptr<Drawable> > drawables;

	bool showAxis;
	void createAxis();
	std::vector<Block> axis;

	void initialize();

	// previously: list of bools for each key, init with all false
	// replaced with set of keys with 'true' value
	std::set<unsigned char> keys; 
	std::set<unsigned char> specialkeys;

	std::shared_ptr<Camera> camera;
};

