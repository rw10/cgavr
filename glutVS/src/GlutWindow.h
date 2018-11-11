#pragma once

#include <vector>
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
	void mouseFunc(int button, int state, int x, int y);

private:
	static GlutWindow* INSTANCE;

	GlutWindow();
	~GlutWindow();

	std::vector<std::shared_ptr<Drawable> > drawables;

	bool showAxis;
	void createAxis();
	std::vector<Block> axis;

	void initialize();

	// bools for each key, init with all false
	std::vector<bool> keys;

	Camera camera;
};

