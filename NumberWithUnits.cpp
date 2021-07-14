#include <iostream>
#include <fstream>
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;


namespace ariel
{
       static map <pair<string, string>, double> db; 

       /**Constructor
     */
    NumberWithUnits::NumberWithUnits(double num1, string units1){
        // if (num1==0 )
        //         throw invalid_argument{"num cant be 0"};

        if (db.find(make_pair(units1 , units1))==db.end())
                throw invalid_argument{"Their is no units such as - ["+units1+"]"};
        num=num1;
        units=units1;
    }


	void NumberWithUnits:: read_units(std::ifstream& units_txt_file) { 

        multimap <string, pair<string, double>> initial_db; 

       string first_units, sec_units, trash; 
       double mul_secTo_first=0;
   
       while (units_txt_file >> trash >> first_units >> trash >> mul_secTo_first >> sec_units ){ // it will be false when its not possible to fill this elements (their is no line like that)
           initial_db.insert( make_pair(first_units, make_pair(sec_units , 1/mul_secTo_first)));
           initial_db.insert( make_pair(sec_units, make_pair(first_units , mul_secTo_first)));
       }

        for (auto [key , value]: initial_db){
            db.insert( make_pair( make_pair( key, value.first), value.second)); // insert to our final db, it will be easier to pull from this db
            db.insert( make_pair( make_pair( key, key), 0)); // we will use it to find units format in >> operator

        }

        //cout<< "-------" << endl;
       bool is_new_path= true;
        while(is_new_path)
        {
            is_new_path=false;
        for (auto [key , value]: initial_db){
            //cout << key << ", " << value.first << ", " << value.second << endl;
            auto begin_u = initial_db.lower_bound(value.first);
            auto end_u = initial_db.upper_bound(value.first); 
            for (auto i=begin_u; i!= end_u ; ++i){  // i want to creates more conections from what i have
                if ((db.count(make_pair(key,i->second.first))<1) && key!=i->second.first){
                    is_new_path= true;
		            //cout << i->first << "," << i->second.first << endl;
                    initial_db.insert( make_pair(key, make_pair(i->second.first , i->second.second*value.second))); //insert first, second of second, mul to*to
                    db.insert( make_pair( make_pair( key, i->second.first),  i->second.second*value.second));
                }
        }
        }
        }


    }

	double NumberWithUnits::convert_to_first_units(const NumberWithUnits& other) const{
        double other_with_this_units=other.num;
        if (other.units!=units){
            auto itr =db.find(make_pair(units , other.units));
            if (itr==db.end()){
                throw invalid_argument{"Units do not match - ["+other.units+"] cannot be converted to ["+units+"]"};
            }
            other_with_this_units= itr->second*other.num;
    }
    return other_with_this_units;
    }


    /**operator+
     * binary +
     * 2 options for unary+ :   
     * 1. inside the class without parameters
     * 2. outside the class whith 1 parameter
     * Note: units are determined by first number
     */  	
	NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& other) const{

		return  NumberWithUnits {(num+(this->convert_to_first_units(other))) , units};
	}

    /**operator+ ------------------------
     * unary +
     * 2 options for unary+ :   
     * 1. inside the class without parameters
     * 2. outside the class whith 1 parameter
     * Note: units are determined by first number
     */  	
	NumberWithUnits NumberWithUnits::operator+() {

		return  NumberWithUnits {num , units};
	}




    /**operator+=
     * Note: units are determined by first number
     */   
	NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other){

        num+=(this->convert_to_first_units(other));
		return *this;
	}


    /**operator-
     * binary -
     * Note: units are determined by first number
     */  	
	NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& other) const{
		return  NumberWithUnits {num-(this->convert_to_first_units(other)) , units};
	}


    /**operator- ------------------------
     * unary -
     * 2 options for unary- :   
     * 1. inside the class without parameters
     * 2. outside the class whith 1 parameter
     * Note: units are determined by first number
     */  	
	NumberWithUnits NumberWithUnits::operator-() {

		return  NumberWithUnits {-num , units};
	}


    /**operator-=
     * Note: units are determined by first number
     */   
	NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other){

        num-=(this->convert_to_first_units(other));
		return *this;
	}

//------------------ postfix and prefix ++ and --  --------------------

    /**prefix operator++
     * 1. increases 2. returns
     */ 
    NumberWithUnits& NumberWithUnits::operator++(){
        num++;
        return *this;
    }
    /**postfix operator++
     * 1. returns 2. increases
     * https://github.com/erelsgl-at-ariel/cpp-5781/blob/4d1e1405316f562f1182583a032cf510af8c5cc1/04-operator-overloading/1-arithmetic-operators/Complex.hpp 
     */
    NumberWithUnits NumberWithUnits::operator++(int){ // int is just to avoid ambiguity
        NumberWithUnits copy= *this;
        num++;
        return copy;
    }

    /**prefix operator--
     * 1. increases 2. returns
     */ 
    NumberWithUnits& NumberWithUnits::operator--(){
        //cout<< "lif--  " <<num<< endl;

        num--;
        //cout<< "ah--  " <<num<< endl;

        return *this;
    }
    /**postfix operator--
     * 1. returns 2. increases
     * https://github.com/erelsgl-at-ariel/cpp-5781/blob/4d1e1405316f562f1182583a032cf510af8c5cc1/04-operator-overloading/1-arithmetic-operators/Complex.hpp 
     */
    NumberWithUnits NumberWithUnits::operator--(int){ // int is just to avoid ambiguity
        NumberWithUnits copy= *this;
        num--;
        return copy;
    }






//----------- friend operators - the implementation is outside the class-----------------


    /**operator*
     * binary *
     */    
    NumberWithUnits operator*(const double& other_d, const NumberWithUnits& n1 ){ //const on the element->we wouldnt change this element, const on the function-> we wouldnt change the object (this), and their is also const on the returned value, and const on an object that lock the posibilty to use unConst functions
        return  NumberWithUnits {other_d*n1.num , n1.units}; 
    }

    /**operator*
     * binary *
     */    
    NumberWithUnits operator*(const NumberWithUnits& n1, const double& other_d ){ //const on the element->we wouldnt change this element, const on the function-> we wouldnt change the object (this), and their is also const on the returned value, and const on an object that lock the posibilty to use unConst functions
        return  NumberWithUnits {other_d*n1.num , n1.units}; 
    }




     /**operator==
     * The implementation is outside the class
     * https://stackoverflow.com/questions/6837007/comparing-float-double-values-using-operator
     */ 
	bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        
        double other_with_this_units=n2.num;
        if (n2.units!=n1.units){
           auto itr =db.find(make_pair(n1.units , n2.units));
            if (itr==db.end()){ // tow diff type of units
                throw invalid_argument{"Units do not match - ["+n2.units+"] cannot be compared to ["+n1.units+"]"};
            }
            if((n1.num!=0&&n2.num==0) || (n1.num==0&&n2.num!=0)){return false;}

            other_with_this_units= itr->second*n2.num;
    
        }
        if (n1.num==0&&other_with_this_units==0 ){
            return true;
        }

          return (abs(other_with_this_units/n1.num - 1) < 5.96e-08);
        //  //return (abs(other_with_this_units - n1.num) < 0.00000000000001f);
         }
	
     /**operator!=
     * The implementation is outside the class
     */       
    bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2){

         return (!(n1==n2));
         }

     /**operator<
     * The implementation is outside the class
     */       
    bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2){ 
        double other_with_this_units=n2.num;
        if (n2.units!=n1.units){
            auto itr =db.find(make_pair(n1.units , n2.units));
             if (itr==db.end())
                throw invalid_argument{"Units do not match - ["+n2.units+"] cannot be converted to ["+n1.units+"]"};
            other_with_this_units= itr->second*n2.num;
        }
         return (n1.num<other_with_this_units);
         }

     /**operator<=
     * The implementation is outside the class
     */       
    bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2){ 
        double other_with_this_units=n2.num;
        if (n2.units!=n1.units){
            auto itr =db.find(make_pair(n1.units , n2.units));
             if (itr==db.end())
                throw invalid_argument{"Units do not match - ["+n2.units+"] cannot be converted to ["+n1.units+"]"};
            other_with_this_units= itr->second*n2.num;
        }
         return (n1.num<=other_with_this_units);
         }

     /**operator>
     * The implementation is outside the class
     */       
    bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double other_with_this_units=n2.num;
        if (n2.units!=n1.units){
            auto itr =db.find(make_pair(n1.units , n2.units));
             if (itr==db.end())
                throw invalid_argument{"Units do not match - ["+n2.units+"] cannot be converted to ["+n1.units+"]"};
            other_with_this_units= itr->second*n2.num;
        }
         //return (n1.num>other_with_this_units);
         return (n1.num- other_with_this_units > 0.0000001);
         }

     /**operator>=
     * The implementation is outside the class
     */       
    bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double other_with_this_units=n2.num;
        if (n2.units!=n1.units){
            auto itr =db.find(make_pair(n1.units , n2.units));
             if (itr==db.end())
                throw invalid_argument{"Units do not match - ["+n2.units+"] cannot be converted to ["+n1.units+"]"};
            other_with_this_units= itr->second*n2.num;
        }
         return (n1.num>=other_with_this_units);
         }


    std::ostream& operator<< (std::ostream& output, const NumberWithUnits& n1){
          output<<n1.num<<"["<<n1.units<<"]"; 
          return   output;
    }

    std::istream& operator>> (std::istream& input , NumberWithUnits& n1){

        string in_units, trash; 
       double in_num=0;  
       string nums;
        if(input>>in_num>>trash>>in_units>>trash){     
                cout <<"good" <<in_num << ", " << trash << ", " << in_units << endl;
             if (db.find(make_pair(in_units , in_units))==db.end())
                throw invalid_argument{"Their is no units such as - ["+in_units+"]"};
            
            n1.num=in_num;
            n1.units=in_units;

        }
        else{
            throw invalid_argument{"bad input format"};

        }
          return   input;
    }

 



}