#include "NumberWithUnits.hpp"



    using namespace std;
    namespace ariel
    {
         
        map<string,std::map<string,double>> graph;
        
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
                graph[unitA][unitB] = size2;
                graph[unitB][unitA] = 1/size2;
                set_graph(unitA, unitB);                 
            }
        }


        ///////////////////////////////////////////////////////////////
        ///////////////////////Private Methods/////////////////////////
        ///////////////////////////////////////////////////////////////

        void NumberWithUnits::set_graph(const string &unitA, const string &unitB)
        {
            //add to the graph from first way
            for(auto &unit : graph[unitB])
            {
                if(unit.first != unitA){
                    double new_size = graph[unitA][unitB]*unit.second;
                    graph[unitA][unit.first] = new_size;
                    graph[unit.first][unitA] = 1/new_size;
                }
            }
            //add to the graph from second way
            for(auto &unit : graph[unitA])
            {
                if(unit.first != unitB){
                    double new_size = graph[unitB][unitA]*unit.second;
                    graph[unitB][unit.first] = new_size;
                    graph[unit.first][unitB] = 1/new_size;
                }
            }
        }
        NumberWithUnits NumberWithUnits::adjust_units(const NumberWithUnits &nwu)
        {
            if (!(this->unit == nwu.unit || graph[this->unit].find(nwu.unit) != graph[this->unit].end()))
            {
                throw invalid_argument("[-] Diffrent Unit Group");
            }
            if (this->unit == nwu.unit)
            {
                return nwu;
            }
            double temp = nwu.num * graph[nwu.unit][this->unit];
            return NumberWithUnits(temp,this->unit);
        } 
        NumberWithUnits NumberWithUnits::adjust_unit()
        {
            if (this->num > 1000)
            {
                
                return *this;
            }
            else if(this->num<1000)
            {

                return *this;
            }
            else
            {
                return *this;
            }
            
        }       
        double NumberWithUnits::adjust(const NumberWithUnits& nwu)
        {
            return 0.2;
        }


        ///////////////////////////////////////////////////////////////
        ///////////////////////Public Methods/////////////////////////
        ///////////////////////////////////////////////////////////////

        //===============================================================
        //Arithmetic Operators===========================================
        NumberWithUnits NumberWithUnits::operator+ (const NumberWithUnits& nwu)
        {
            double n = this->num+(this->adjust_units(nwu)).num;
            NumberWithUnits ans(n,this->unit);
            ans.adjust_unit();
            return ans;
        }
        NumberWithUnits NumberWithUnits::operator+=(const NumberWithUnits& nwu)
        {
            this->num+=(this->adjust_units(nwu)).num;
            this->adjust_unit();
            return *this;
        }
        NumberWithUnits NumberWithUnits::operator+ ()
        {return *this;}
        NumberWithUnits NumberWithUnits::operator- (const NumberWithUnits& nwu)
        {
            double n = this->num-this->adjust_units(nwu).num;
            NumberWithUnits ans(n,this->unit);
            ans.adjust_unit();
            return ans;
        }
        NumberWithUnits NumberWithUnits::operator-= (const NumberWithUnits& nwu)
        {
            this->num-=this->adjust_units(nwu).num;
            this->adjust_unit();
            return *this;
        }
        NumberWithUnits NumberWithUnits::operator-()
        {
            this->num=-1*this->num;
            return *this;
        }
        //===============================================================


        //===============================================================
        //Compartion Operators===========================================
        bool ariel::NumberWithUnits::operator< (const NumberWithUnits& nwu) const
        {
            if (this->unit == nwu.unit) {
                return (abs(this->num - nwu.num)) < Epsilone;
            }
            NumberWithUnits temp(*this);
            temp.adjust_units(nwu);
            return (abs(temp.num - nwu.num)) < Epsilone;
        }
        bool ariel::NumberWithUnits::operator<= (const NumberWithUnits& nwu) const
        {
            if (this->unit == nwu.unit) {
                return (abs(this->num - nwu.num)) <= Epsilone;
            }
            NumberWithUnits temp(*this);
            temp.adjust_units(nwu);
            return (abs(temp.num - nwu.num)) <= Epsilone;
        }
        bool ariel::NumberWithUnits::operator> (const NumberWithUnits& nwu) const
        {
            if (this->unit == nwu.unit) {
                return (abs(this->num - nwu.num)) > Epsilone;
            }
            NumberWithUnits temp(*this);
            temp.adjust_units(nwu);
            return (abs(temp.num - nwu.num)) > Epsilone;
        }
        bool ariel::NumberWithUnits::operator>= (const NumberWithUnits& nwu) const
        {
            if (this->unit == nwu.unit) {
                return (abs(this->num - nwu.num)) >= Epsilone;
            }
            NumberWithUnits temp(*this);
            temp.adjust_units(nwu);
            return (abs(temp.num - nwu.num)) >= Epsilone;
        }
        bool ariel::NumberWithUnits::operator== (const NumberWithUnits &nwu) const
        {
            if (this->unit == nwu.unit) {
                return (abs(this->num - nwu.num)) <= Epsilone;
            }
            NumberWithUnits temp(*this);
            temp.adjust_units(nwu);
            return (abs(temp.num - nwu.num)) <= Epsilone;
        }
        bool ariel::NumberWithUnits::operator!= (const NumberWithUnits& nwu) const
        {return true;}
        //===============================================================


        //===============================================================
        //Prefix Operators===============================================
        NumberWithUnits& NumberWithUnits::operator++ ()
        {
            this->num++;
            this->adjust_unit();
            return *this;
        }
        NumberWithUnits& NumberWithUnits::operator-- ()
        {
            this->num--;
            this->adjust_unit();
            return *this;
        }
        //==============================================================


        //==============================================================
        //Psotfix Operators=============================================
        NumberWithUnits& NumberWithUnits::operator++ (int)
        {
            this->num++;
            this->adjust_unit();
            return *this;
        }
        NumberWithUnits& NumberWithUnits::operator-- (int)
        {
            this->num--;
            this->adjust_unit();
            return *this;
        }
        //==============================================================


        //==============================================================
        //Multiplication Operators======================================
        NumberWithUnits operator* (double num1, const NumberWithUnits &nwu)
        {
            
            NumberWithUnits ans(nwu.num*num1,nwu.unit);
            ans.adjust_unit();
            return ans;
        }
        NumberWithUnits operator* (const NumberWithUnits &nwu, double num1)
        {
            NumberWithUnits ans(nwu.num*num1,nwu.unit);
            ans.adjust_unit();
            return ans;
        }
        //==============================================================


    }

    //==============================================================
    //Stream Operators==============================================
    std::ostream &ariel::operator<<(std::ostream &os, const NumberWithUnits &nwu) 
    {
        os<<nwu.num<<" ["<<nwu.unit<<"]";
        return os;
    }
    std::istream &ariel::operator>>(std::istream &is, NumberWithUnits &nwu) 
    {return is;}
    //==============================================================
    
