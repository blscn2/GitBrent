//============================================================================
// Name        : lab10.cpp
// Author      : Brent Schultz
// Version     :
// Copyright   : Your copyright notice
// Description : Lab 10
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

// abstract base class for conic sections
class BaseConic{
	protected:
		double x;
		double y;
		double radius1;

	public:
		BaseConic(double x0 = 0.0, double y0 = 0.0);
		virtual ~BaseConic();
		virtual void Display();
		void Move(double nx, double ny);
		virtual double Area() const = 0; //PURE VIRTUAL FUNCTION which makes this an ABC

};

void BaseConic::Move(double nx, double ny){
	x = nx + x;
	y = nx + y;
}

void BaseConic::Display(){
	cout << "Coordinates: (" << x << ", " << y << ")" << endl
	 << "Radius: " << radius1 << endl
	 << "Area of shape: " << Area() << " units sq \n" << endl;
}

BaseConic::BaseConic(double x0, double y0){
	x = x0;
	y = y0;
	radius1 = 0;
}

BaseConic::~BaseConic(){

}

class Ellipse: public BaseConic{
	private:
		double radius2;
		double theta;

	public:
		void Rotate(double nang);
		void Vertices();
		void Resize(double scale1, double scale2);
		void Display();
		double Area() const {return 3.14 * radius1 * radius2;}

		Ellipse();
		Ellipse( double x0, double y0);
		virtual ~Ellipse();
};

void Ellipse::Rotate( double nang){
	theta += nang;
	if(theta >= 360){
		theta -= 360;
	}
}

void Ellipse::Vertices(){
	int x1, x2, y1, y2;
	x1 = x + radius1;
	x2 = x - radius1;
	y1 = y + radius2;
	y2 = y - radius2;

	cout << "The ellipses vertices are:" << endl
			<< "(" << x1 << ",0)"<< endl
			<< "(" << x2 << ",0)"<< endl
			<< "(0," << y1 << ")"<< endl
			<< "(0," << y2 << ")\n" << endl;

}

void Ellipse::Resize(double scale1, double scale2){
	radius1 *= scale1;
	radius2 *= scale2;
}

void Ellipse::Display(){
	cout << "Coordinates: (" << x << ", " << y << ")" << endl
		 << "XRadius: " << radius1 << endl
		 << "YRadius: "<< radius2 << endl
		 << "Area of shape: " << Area() << " units sq \n" << endl;
}

Ellipse::Ellipse(){
	radius1 = 1;
	theta = 0;
}

Ellipse::Ellipse( double x0, double y0){
	radius1 = x0;
	radius2 = y0;
	theta =1;
}

Ellipse::~Ellipse(){

}

class Circle: public BaseConic{
	public:
		int InCircle( double xc, double yc);
		virtual double Area() const {return 3.14 * radius1 * radius1;}

		void Resize(double scale);
		Circle();
		Circle( double rad);
		Circle( double x0, double y0);
		~Circle();
};

int Circle::InCircle( double xc, double yc){
	if( (xc <= x + radius1 && xc >= x - radius1) && (yc <= y + radius1 && yc >= y - radius1)){
		return 1;
	}
	else
		return 0;
}

void Circle::Resize(double scale){
	radius1 *= scale;
}

Circle::Circle(){

}

Circle::Circle(double rad){
	radius1 = rad;
}

Circle::Circle(double x0, double y0){

}

Circle::~Circle(){

}

int main(){

	double rad1;
	cout<<"Enter radius to be used " <<endl;
	cin >> rad1;
	if ( rad1 <= 0){
		cout << "Using 0 or negative radii is unacceptable " << endl;
		return 0;
	}
	Circle circle1(rad1);
	cout << "Original Circle: " << endl;
	circle1.Display();
	circle1.Move(5,5);
	cout << "After Moving: " << endl;
	circle1.Display();
	circle1.Resize(5);
	cout << "After Resize: " << endl;
	circle1.Display();

	int xcord = 20;
	int ycord = 20;

	if ( 1 == circle1.InCircle(xcord, ycord) ){
		cout << "Point (" << xcord << "," << ycord <<") is inside circle \n" << endl;
	}
	else if ( 0 == circle1.InCircle(xcord, ycord) ){
		cout << "Point (" << xcord << "," << ycord <<") is not inside circle \n" << endl;
	}


	double rad2;
	cout<<"Enter radius to be used " <<endl;
	cin >> rad2;
	if ( rad2 <= 0){
			cout << "Using 0 or negative radii is unacceptable " << endl;
			return 0;
		}
	Ellipse ellipse1(rad1, rad2);
	cout << "Original Ellipse: " << endl;
	ellipse1.Display();
	ellipse1.Vertices();
	ellipse1.Move(5,5);
	cout << "After Moving: " << endl;
	ellipse1.Display();
	ellipse1.Resize(2,3);
	cout << "After Resize: " << endl;
	ellipse1.Display();
	ellipse1.Rotate(30);
	cout << "After Rotate: " <<  endl;
 	ellipse1.Display();

	return 0;
}


