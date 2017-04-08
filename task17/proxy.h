#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Image
{
	virtual ~Image() = default;
	virtual void draw(const string& file) = 0;
};

struct Bitmap : Image
{
	Bitmap(const string& filename, const string& file)
	{
		ofstream output_file(file, ios::app);
		output_file << "Loading image from " << filename << endl;
		output_file.close();
	}

	void draw(const string& file) override
	{
		ofstream output_file(file, ios::app);
		output_file << "Drawing image" << endl;
		output_file.close();
	}
};

struct LazyBitmap : Image
{
	LazyBitmap(const string& filename) : filename(filename) {}
	~LazyBitmap() { delete bmp; }
	void draw(const string& file) override
	{
		if (!bmp)
			bmp = new Bitmap(filename, file);
		bmp->draw(file);
	}

private:
	Bitmap* bmp{ nullptr};
	string filename;
};

void draw_image(Image& img, const string& file)
{
	ofstream output_file(file);
	output_file << "About to draw the image" << endl;
	output_file.close();
	img.draw(file);
	ofstream output_file1(file, ios::app);
	output_file1 << "Done drawing the image" << endl;
	output_file1.close();
}
