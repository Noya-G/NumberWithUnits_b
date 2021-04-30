
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

const double Epsilone = 0.0001;

using namespace std;
namespace ariel
{
    class NumberWithUnits
    {

    private:
        double num;
        string unit;
        double adjust_unit(const NumberWithUnits &unit1) const;
        static void update_graph(const string &src_unit, const string &dest_unit);

    public:
        //builder
        NumberWithUnits(double s, const string &u);
        //reading units from file
        static void read_units(ifstream &units_file);

        //===============================================================
        //Arithmetic Operators===========================================
        NumberWithUnits operator+ (const NumberWithUnits& nwu);
        NumberWithUnits operator+=(const NumberWithUnits& nwu);
        NumberWithUnits operator+ ();
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
        NumberWithUnits operator++ (int);
        NumberWithUnits operator-- (int);
        //==============================================================


        //==============================================================
        //Multiplication Operators======================================
        friend NumberWithUnits operator* (double num1, const NumberWithUnits &nwu);
        friend NumberWithUnits operator* (const NumberWithUnits &nwu, double num1);
        //==============================================================


        //==============================================================
        //Stream Operators==============================================
        friend  std::ostream& operator<<( std::ostream& os, const NumberWithUnits& nwu);
        friend  std::istream& operator>>( std::istream &is, NumberWithUnits &nwu);
        //==============================================================
    };

}
