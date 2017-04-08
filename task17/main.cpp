#define CATCH_CONFIG_RUNNER 
#include "catch.hpp"
#include "proxy.h"
using namespace std;

TEST_CASE("Checking drawing first image")
{
	LazyBitmap img{ "kybik.png" };
	draw_image(img, "out.txt");
	ifstream f("out.txt");
	string s;
	getline(f, s);
	REQUIRE(s == "About to draw the image");
	getline(f, s);
	REQUIRE(s == "Loading image from kybik.png");
	getline(f, s);
	REQUIRE(s == "Drawing image");
	getline(f, s);
	REQUIRE(s == "Done drawing the image");
	f.close();
}

TEST_CASE("Checking drawing the same image image")
{
	LazyBitmap img{ "kybik.png" };
	draw_image(img, "out.txt");
	draw_image(img, "out1.txt");
	ifstream f("out1.txt");
	string s;
	getline(f, s);
	REQUIRE(s == "About to draw the image");
	getline(f, s);
	REQUIRE(s == "Drawing image");
	getline(f, s);
	REQUIRE(s == "Done drawing the image");
	f.close();
}

void virtual_proxy()
{
	LazyBitmap img{ "kybik.png" };
	draw_image(img, "out.txt"); // loaded whether the bitmap is loaded or not
	draw_image(img, "out1.txt");
}


int main(int argc, char* argv[])
{
	//virtual_proxy();

	int result = Catch::Session().run(argc, argv);
	getchar();
	return result;
}
