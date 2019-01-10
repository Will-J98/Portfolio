#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//https://github.com/sessamekesh/IndigoCS_Mandelbrot/blob/master/main.cpp

struct Colour
{
	string name;
	int red;
	int green;
	int blue;

};
double mapToReal(int x, int imageWidth, double minR, double maxR);
double mapToImaginary(int y, int imageHeight, double minI, double maxI);
int mandelBrotFormula(double cr, double ci, int max_iterations);
int FindNumColours(string ColourList);
void LoadColours(Colour List[], int NumColours, string ColourList);
void DisplayColours(Colour List[], int NumColours);

int main()
{
	
	int NumColours = FindNumColours("list.txt");

	if (NumColours == -1)
	{
		cout << "File could not be found" << endl;
		return 1;
	}
	
	
	Colour* RGB = new Colour[NumColours];

	LoadColours(RGB, NumColours, "list.txt");

	DisplayColours(RGB, NumColours);

	//int indexColour = 9;

	
	int indexColour = 0;
	int loop = 0;
	while (loop != 1)
	{
		string ChosenColour;
		cout << "Enter a colour that you want your fractal outline to be from the list." << endl;
		cin >> ChosenColour;

		for (int i = 0; i < NumColours; i++)
		{
			if (ChosenColour == RGB[i].name)
			{
				indexColour = i;
				loop = 1;
			}
		}

	}
	
	
	ifstream input("input.txt");
	int imageWidth, imageHeight, maxN;
	double minR, maxR, minI, maxI;

	if (!input)
	{
		cout << "Could not find file!" << endl;
		return 1;
	}
	input >> imageWidth >> imageHeight >> maxN;
	input >> minR >> maxR >> minI >> maxI;
	input.close();

	ofstream output("final_image.ppm");
	output << "P3" << endl;
	output << imageWidth << " " << imageHeight << endl; // dimensions
	output << "256" << endl; // max rgb value

	for (int y = 0; y < imageHeight; y++) // for each row
	{
		for (int x = 0; x < imageWidth; x++) // coulumns
		{
			double cr = mapToReal(x, imageWidth, minR, maxR);
			double ci = mapToImaginary(y, imageHeight, minI, maxI);

			int n = mandelBrotFormula(cr, ci, maxN);

			int red = (n % (RGB[indexColour].red));
			int green = (n % (RGB[indexColour].green));
			int blue = (n % (RGB[indexColour].blue));

			output << red << " " << green << " " << blue << " ";

		}
		output << endl;
	}
	output.close();
	cout << "Done" << endl;

	system("pause");

	return 0;
}
//The following three functions are sourced from https://github.com/sessamekesh/IndigoCS_Mandelbrot/blob/master/main.cpp.
double mapToReal(int x, int imageWidth, double minR, double maxR)
{
	double range = maxR - minR;
	return x * (range / imageWidth) + minR;
}
double mapToImaginary(int y, int imageHeight, double minI, double maxI)
{
	double range = maxI - minI;
	return y * (range / imageHeight) + minI;
}
int mandelBrotFormula(double cr, double ci, int max_iterations)
{
	int i = 0;
	double zr = 0.0;
	double zi = 0.0;
	while (i < max_iterations && ((zr * zr) + (zi * zi) < 4.0))
	{
		double temp = (zr * zr) - (zi * zi) + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp; //used because you can't assign more than one x
		i++;
	}
	return i;
}
// end of sourced code.

void LoadColours(Colour List[], int NumColours, string ColourList)
{
	ifstream listColours("list.txt");
	if (!listColours)
	{
		cout << "your file could not be found" << endl;
		return;
	}

	for (int i = 0; i < NumColours; i++)
	{
		listColours >> List[i].name >> List[i].red >> List[i].green >> List[i].blue;
	}
	listColours.close();
}
void DisplayColours(Colour List[], int NumColours)
{
	cout << "Colour" << endl;

	for (int i = 0; i < NumColours; i++)
	{
		cout << List[i].name;
		cout << endl;
	}
}

int FindNumColours(string ColourList)
{
	ifstream inFile(ColourList);
	if (!inFile)
	{
		return -1;
	}
	int counter = 0;
	string tempLine;
	while (!inFile.eof())
	{
		getline(inFile, tempLine);
		counter++;
	}
	int length = tempLine.length();
	if (length <= 0)
	{
		counter--;
	}
	return counter;

}
