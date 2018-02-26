/*
 * geom1.cxx
 * 
 * Copyright 2018 Cherevkov Sergey <MandoMirsh@debcom>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
class Coord {
	double x,y;
	public:
	Coord(){
		x=0;
		y=0;
	};
	Coord(double a, double b=0){
		x=a;
		y=b;
	};
public:
 bool operator==(Coord ob2){
	 return ((x=ob2.x)&&(y=ob2.y));
 };
 friend std::ostream& operator<< (std::ostream& output, Coord ob){
	output<<'('<<ob.x<<" , "<<ob.y<<')';
	return output;
 };
 friend std::istream& operator>> (std::istream& input, Coord & ob){
	 input>>ob.x>>ob.y;
	 return  input;
 };
 friend int turn( Coord a,Coord b, Coord c);
  friend int main(int argc,char** argv);
};
class Interval {
	Coord a,b;
public:
	Interval(double x2, double y2){
		Coord ob1;
		a = ob1;
		Coord ob2(x2,y2);
		b = ob2;
	};
	Interval(double x1, double y1,double x2, double y2){
		Coord ob1(x1,y1), ob2(x2,y2);
		a = ob1;
		b = ob2;
	};
  bool operator==(Interval ob2){
	  return (((a==ob2.a)&&(b==ob2.b))||((a==ob2.b)&&(b==ob2.a)));
  };
 friend std::ostream& operator<< (std::ostream& output, Interval ob){
	output<<'{'<<ob.a<<" ; "<<ob.b<<'}';
	return output;
 };
 friend std::istream& operator>> (std::istream& input, Interval & ob){
	 input>>ob.a>>ob.b;
	 return  input;
 }; 
 friend int main(int argc,char** argv);
};

int turn(Coord a, Coord b, Coord c){
	float d11,d12,d21,d22;
	d11 = b.x - a.x;
	d12 = c.x - a.x;
	d21 = b.y - a.y;
	d22 = c.y - a.y;
	if (d11*d22-d21*d12==0)
		return 0;
	if (d11*d22-d21*d12<0)
		return -1;
	return 1;
};

int main (int argc, char **argv)
{
	Interval a(1,3);
	Coord b; 
	int c;
	std::cout<<a<<'\n';
	std::cin>>a;
	std::cin>>b;
	c = turn(a.a,a.b,b);
	std::cout<<"Interval:\n"<<a<<'\n'<<"Dot:\n"<<b<<'\n';
	switch (c){
	case 0: std::cout<<"collinear\n"; break;
	case 1: std::cout<<"on left\n"; break;
		default: std::cout<<"on right\n";
	}
	
	Interval d(3.0,5.0,-3.0,-5.0);
	Coord e(d.a.x*(1LL<<52),d.a.y*(1LL<<52));
	c = turn (d.a,d.b,e);
	std::cout<<"Interval:\n"<<d<<'\n'<<"Dot:\n"<<e<<'\n';
	switch (c){
	case 0: std::cout<<"collinear\n"; return 0;
	case 1: std::cout<<"on left\n"; return 0;
		default: std::cout<<"on right\n";
	}
	return 0;
}
