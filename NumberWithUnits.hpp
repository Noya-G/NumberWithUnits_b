#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <map>

#define Epsilone 0.0001;

namespace ariel{
    class NumberWithUnits
    {
    private:
        std::string unit;
        double num;
        static void set_graph(const std::string &src_unit, const std::string &dest_unit);
        NumberWithUnits adjust_units(const NumberWithUnits &nwu1,const NumberWithUnits &nwu2);
        NumberWithUnits adjust_unit(const NumberWithUnits &nwu);
        double adjust(const NumberWithUnits& nwu);
        
        public:
        NumberWithUnits(double num, std::string unit);
        NumberWithUnits(const NumberWithUnits& n);
        ~NumberWithUnits();
        static void read_units(std::ifstream& units_file);


        //===============================================================
        //Arithmetic Operators===========================================
        NumberWithUnits operator+ (const NumberWithUnits& nwu);
        NumberWithUnits operator+=(const NumberWithUnits& nwu);
        NumberWithUnits operator+ ();
        friend NumberWithUnits operator+(double number,const NumberWithUnits &nwu);
        NumberWithUnits operator- (const NumberWithUnits& nwu);
        NumberWithUnits operator-= (const NumberWithUnits& nwu);
        NumberWithUnits operator-();
        //===============================================================


        //===============================================================
        //Compartion Operators===========================================
        bool operator< (const NumberWithUnits& nwu)const;
        bool operator<= (const NumberWithUnits& nwu)const;
        bool operator> (const NumberWithUnits& nwu)const;
        bool operator>= (const NumberWithUnits& nwu)const;
        bool operator== (const NumberWithUnits &nwu) const;
        bool operator!= (const NumberWithUnits& nwu)const;
        //===============================================================


        //===============================================================
        //Prefix Operators===============================================
        NumberWithUnits& operator++ ();
        NumberWithUnits& operator-- ();
        //==============================================================


        //==============================================================
        //Psotfix Operators=============================================
        NumberWithUnits& operator++ (int);
        NumberWithUnits& operator-- (int);
        //==============================================================


        //==============================================================
        //Multiplication Operators======================================
        NumberWithUnits& operator* (double num1);
        friend NumberWithUnits operator*(double number, const NumberWithUnits &nwu);
        //==============================================================


        //==============================================================
        //Stream Operators==============================================
        friend  std::ostream& operator<<( std::ostream& os, const NumberWithUnits& nwu);
        friend  std::istream& operator>>( std::istream &is, NumberWithUnits &nwu);
        //==============================================================

    };



    
}



