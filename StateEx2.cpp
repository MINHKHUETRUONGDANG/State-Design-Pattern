#include <iostream>
#include <thread>

using namespace std;
class GumballMachine;

class State{
    public:
        virtual void insertQuarter() = 0;
        virtual void ejectQuarter() = 0;
        virtual void turnCrack() = 0;
        virtual void dispense() = 0;
};

class SoldOut: public State{ //GumballMachine *gumballMachine;
    public: //SoldOut(GumballMachine *gm): gumballMachine(gm){};
        static SoldOut *getInstance(){ static SoldOut soldout; return &soldout; }
        virtual void insertQuarter(){ cout << "\nYou can’t insert a quarter, the machine is sold out"; };
        virtual void ejectQuarter(){ cout << "\nYou can’t eject, you haven’t inserted a quarter yet"; };
        virtual void turnCrack(){ cout << "\nYou turned, but there are no gumballs"; };
        virtual void dispense(){ cout << "\nNo gumball dispensed"; };    
};
class NoQuarter: public State{ //GumballMachine *gumballMachine;
    public: //NoQuarter(GumballMachine *gm): gumballMachine(gm){};
        static NoQuarter *getInstance(){ static NoQuarter noQuarter; return &noQuarter; }
        virtual void insertQuarter(){ cout << "\nYou inserted a quarter"; };
        virtual void ejectQuarter(){ cout << "\nYou haven’t inserted a quarter"; };
        virtual void turnCrack(){ cout << "\nYou turned but there’s no quarter"; };
        virtual void dispense(){ cout << "\nYou need to pay first"; };
};
class HasQuarter: public State{ //GumballMachine *gumballMachine;
    public: //HasQuarter(GumballMachine *gm): gumballMachine(gm){};
        static HasQuarter *getInstance(){ static HasQuarter hasQuarter; return &hasQuarter; }
        virtual void insertQuarter(){ cout << "\nYou can’t insert another quarter"; };
        virtual void ejectQuarter(){ cout << "\nQuarter returned"; };
        virtual void turnCrack(){ cout << "\nYou turned..."; };
        virtual void dispense(){ cout << "\nNo gumball dispensed"; };
};
class Sold: public State{ 
    public: static Sold *getInstance(){ static Sold sold; return &sold; }
        virtual void insertQuarter(){ cout << "\nPlease wait, we’re already giving you a gumball"; };
        virtual void ejectQuarter(){ cout << "\nSold successfully, waiting for another quarter!"; };
        virtual void turnCrack(){ cout << "\nTurning twice doesn’t get you another gumball!"; };
        virtual void dispense(){ cout << "\nNo gumball dispensed"; };
};


class GumballMachine{
    private:
        // State *soldout; 
        // State *hasQuarter;
        // State *sold;
        // State *noQuarter;
        State *state = SoldOut::getInstance();
        int count;
    public:
        GumballMachine(int numOfGumballs): count(numOfGumballs){
            if(numOfGumballs > 0){
                state = NoQuarter::getInstance();
            }
        }
        
        void run(){
            int i = 0;
            while(i < count){
                    state = HasQuarter::getInstance();
                    state->turnCrack();
                    this_thread::sleep_for(chrono::seconds(1));
                    
                    releaseBall();
                    
                    state = Sold::getInstance();
                    state->ejectQuarter();
                    this_thread::sleep_for(chrono::seconds(1));
                    
                    cout << endl;
            }
            
            state = SoldOut::getInstance();
            state->insertQuarter();
            this_thread::sleep_for(chrono::seconds(1));
        }
        
        void releaseBall(){
            cout << "\nA gumball comes rolling out the slot....";
            this_thread::sleep_for(chrono::seconds(1));
        
            if(count != 0){
                count--;
            }
        }
};

int main()
{
    cout<<"State Design Pattern"<<endl;
    GumballMachine gumballMachine(3);
    
    gumballMachine.run();

    return 0;
};
