#pragma once
#include <iostream>
//include "units.txt"
#include <fstream>
#include <map>
#include <set>
#include <string>
using namespace std;
// https://github.com/erelsgl-at-ariel/cpp-5781/blob/master/04-operator-overloading/1-arithmetic-operators/Complex.cpp
namespace ariel{


  class NumberWithUnits {


      //static read_units<pair<string, string>, double> unit;
      
    private:

         double num;
         string units;

    public:
   
    /**Constructor
     */
    //NumberWithUnits(double num, string units): num(num), units(units){}
    NumberWithUnits(double num, string units);

    /**read_units
     * read units from txt file (units.txt)
     */
    static void read_units(std::ifstream &units_txt_file);  

	double convert_to_first_units(const NumberWithUnits& other) const;




    /**operator+
     * binary +
     * Note: units are determined by first number
     * 
     */    
    NumberWithUnits operator+(const NumberWithUnits& other) const; //const on the element->we wouldnt change this element
//const on the element->we wouldnt change this element, const on the function-> we wouldnt change the object (this), and their is also const on the returned value

    /**operator+
     * unary +
     * Note: units are determined by first number
     * 
     */    
    NumberWithUnits operator+(); //const on the element->we wouldnt change this element
//const on the element->we wouldnt change this element, const on the function-> we wouldnt change the object (this), and their is also const on the returned value

    /**operator+=
     * Note: units are determined by first number
     */   
    NumberWithUnits& operator+=(const NumberWithUnits& other);


    /**operator-
     * binary -
     * Note: units are determined by first number
     */    
    NumberWithUnits operator-(const NumberWithUnits& other) const; //const on the element->we wouldnt change this element

    /**operator-
     * unary -
     * Note: units are determined by first number
     */    
    NumberWithUnits operator-() ; 



    /**operator-=
     * Note: units are determined by first number
     */   
    NumberWithUnits& operator-=(const NumberWithUnits& other);



//------------------postfix and prefix ++ and ----------------------

    /**prefix operator++
     * 1. increases 2. returns
     */ 
    NumberWithUnits& operator++();

    /**postfix operator++
     * 1. returns 2. increases
     * i will implement it with copy ctor
     */
    NumberWithUnits operator++(int); // int is just to avoid ambiguity


    /**prefix operator--
     * 1. increases 2. returns
     */ 
    NumberWithUnits& operator--();

    /**postfix operator--
     * 1. returns 2. increases
     * i will implement it with copy ctor
     */
    NumberWithUnits operator--(int); // int is just to avoid ambiguity






//----------- friend operators - the implementation is outside the class-----------------

    /**operator*
     * binary *
     */    
    friend NumberWithUnits operator*(const double& other_d, const NumberWithUnits& n1 ); //const on the element->we wouldnt change this element, const on the function-> we wouldnt change the object (this), and their is also const on the returned value, and const on an object that lock the posibilty to use unConst functions
    

    /**operator*
     * binary *
     */    
    friend NumberWithUnits operator*(const NumberWithUnits& n1, const double& other_d); //const on the element->we wouldnt change this element, const on the function-> we wouldnt change the object (this), and their is also const on the returned value, and const on an object that lock the posibilty to use unConst functions
    


     /**operator==
     * The implementation is outside the class
     */       
    friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2);
     /**operator!=
     * The implementation is outside the class
     */       
    friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);

     /**operator<
     * The implementation is outside the class
     */       
    friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2);

     /**operator<=
     * The implementation is outside the class
     */       
    friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2);

     /**operator>
     * The implementation is outside the class
     */       
    friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2);

     /**operator>=
     * The implementation is outside the class
     */       
    friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2);



//-------- I/O operators---------

    friend std::ostream& operator<< (std::ostream& output, const NumberWithUnits& n1);
    
    friend std::istream& operator>> (std::istream& input , NumberWithUnits& n1);



  };

 
    



}