#include "write.h"
#include "common.h"

map<char, DrawImage*> letters;

void initText() {
	string name = executablePath() + "/data/letters/";
	for (int i = 'a'; i < 'f'; i++) {
		string temp = name + (char)i + ".png";
		DrawImage *image = new DrawImage(temp.c_str());
		letters[i] = image;
	}
}

void drawText(string text, v2i pos) {
	int i = 0;
	int l = text.length();
	for (i = 0; i < l; i++) {
		char c = text[i];
		letters[c]->draw(pos[0]+i*32, pos[1]);
	}
}