#include "NumberWithUnits.hpp"



    using namespace std;
    namespace ariel
    {
         
        map<string,std::map<string,double>> units;
        
        ///////////////////////////////////////////////////////////////
        ///////////////////////Constructors////////////////////////////
        ///////////////////////////////////////////////////////////////
        NumberWithUnits::NumberWithUnits(double num, std::string unit){
        this->num=num;
        this->unit=unit;
        }

        NumberWithUnits::NumberWithUnits(const NumberWithUnits& n)
        {
            this->num=n.num;
            this->unit=n.unit;
        }

        NumberWithUnits::~NumberWithUnits(){}

        void NumberWithUnits::read_units(std::ifstream& file)
        {
            string buff, unitA, unitB;
            double size1=0, size2=0;
            while(file >> size1 >> unitA >> buff >> size2 >> unitB)
            {                
                units[unitA][unitB] = size2;
                units[unitB][unitA] = 1/size2;
                set_graph(unitA, unitB);                 
            }
        }

        ///////////////////////////////////////////////////////////////
        ///////////////////////Private Methods/////////////////////////
        ///////////////////////////////////////////////////////////////

        void NumberWithUnits::set_graph(const string &unitA, const string &unitB)
        {
            //add to the graph from first way
            for(auto &unit : units[unitB])
            {
                if(unit.first != unitA){
                    double new_size = units[unitA][unitB]*unit.second;
                    units[unitA][unit.first] = new_size;
                    units[unit.first][unitA] = 1/new_size;
                }
            }
            //add to the graph from second way
            for(auto &unit : units[unitA])
            {
                if(unit.first != unitB){
                    double new_size = units[unitB][unitA]*unit.second;
                    units[unitB][unit.first] = new_size;
                    units[unit.first][unitB] = 1/new_size;
                }
            }
        }
        NumberWithUnits& NumberWithUnits::adjust_units(const NumberWithUnits &nwu1,const NumberWithUnits &nwu2)
        {
            return nwu1;
        }
        NumberWithUnits& NumberWithUnits::adjust_unit()
        {
            return this*;
        }


        
        ///////////////////////////////////////////////////////////////
        ///////////////////////Public Methods/////////////////////////
        ///////////////////////////////////////////////////////////////

        //===============================================================
        //Arithmetic Operators===========================================
        NumberWithUnits& NumberWithUnits::operator+ (const NumberWithUnits& nwu)
        {
            this->num=(this->num+this.adjust_units(nwu).num);
            this.adjust_unit;
            return *this;
        }
        NumberWithUnits& NumberWithUnits::operator+= (const NumberWithUnits& nwu)
        {return *this;}
        NumberWithUnits& NumberWithUnits::operator+ ()
        {return *this;}
        NumberWithUnits& NumberWithUnits::operator- (const NumberWithUnits& nwu)
        {return *this;}
        NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits& nwu)
        {return *this;}
        NumberWithUnits& NumberWithUnits::operator- ()
        {return *this;}
        //===============================================================


        //===============================================================
        //Compartion Operators===========================================
        bool ariel::NumberWithUnits::operator< (const NumberWithUnits& nwu) const
        {return true;}
        bool ariel::NumberWithUnits::operator<= (const NumberWithUnits& nwu) const
        {return true;}
        bool ariel::NumberWithUnits::operator> (const NumberWithUnits& nwu) const
        {return true;}
        bool ariel::NumberWithUnits::operator>= (const NumberWithUnits& nwu) const
        {return true;}
        bool ariel::NumberWithUnits::operator== (const NumberWithUnits &nwu) const
        {return true;}
        bool ariel::NumberWithUnits::operator!= (const NumberWithUnits& nwu) const
        {return true;}
        //===============================================================


        //===============================================================
        //Prefix Operators===============================================
        NumberWithUnits& NumberWithUnits::operator++ ()
        {return *this;}
        NumberWithUnits& NumberWithUnits::operator-- ()
        {return *this;}
        //==============================================================


        //==============================================================
        //Psotfix Operators=============================================
        NumberWithUnits& NumberWithUnits::operator++ (int)
        {return *this;}
        NumberWithUnits& NumberWithUnits::operator-- (int)
        {return *this;}
        //==============================================================


        //==============================================================
        //Multiplication Operators======================================
        NumberWithUnits& NumberWithUnits::operator* (double num1)
        {return *this;}
        //==============================================================
    }

    ariel::NumberWithUnits ariel::operator+(double number, const NumberWithUnits &nwu)
    {return nwu;}
    ariel::NumberWithUnits ariel::operator*(double number, const NumberWithUnits &nwu)
    {return nwu;}

    //==============================================================
    //Stream Operators==============================================
    std::ostream &ariel::operator<<(std::ostream &os, const NumberWithUnits &nwu) 
    {return os;}
    std::istream &ariel::operator>>(std::istream &is, NumberWithUnits &nwu) 
    {return is;}
    //==============================================================
    
