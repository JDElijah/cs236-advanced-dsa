#include <iostream>
using namespace std; 

// Draw a line with a given tick length and optional label. 
void drawLine(int tickLength, int tickLabel) {
	for (int j = 0; j < tickLength; j++)
		cout << "-";
	if (tickLabel >= 0)
		cout << " " << tickLabel;
	cout << endl; 
}

// Draw a line with a given tick length (no label) 
void drawLine(int tickLength) {
	drawLine(tickLength, -1);
}

// Recursively draws interior ticks bewteen major ticks
void drawInterval(int centralLength) {
	if (centralLength >= 1) {
		drawInterval(centralLength - 1); // top interval 
		drawLine(centralLength); // center tick 
		drawInterval(centralLength - 1); // bottom interval 
	}
}

// Draws an English Ruler for the given number of inches and major tick length
void drawRuler(int nInches, int majorLength) {
	drawLine(majorLength, 0); // draw inch 0 and label 
	for (int j = 1; j <= nInches; j++) {
		drawInterval(majorLength - 1); // draw interior ticks 
		drawLine(majorLength, j); // draw major ticks with labels.
	}
}

// Example usage 
int main() {
	int nInches = 3; 
	int majorLength = 4; 
	drawRuler(nInches, majorLength); 
	return 0; 
}