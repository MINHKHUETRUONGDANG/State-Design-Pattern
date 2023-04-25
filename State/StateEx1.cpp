#include <iostream>
#include <thread>

using namespace std;
const int MAX = 3;

class TLState{ public: virtual void reqQuest() = 0; };

class RedState: public TLState{ 
    public: static RedState *getInstance(){ static RedState redReq; return &redReq; }; 
    void reqQuest(){ cout<<"Red is glowing for 1 sec"<<endl; }; };
class GreenState: public TLState{ 
    public: static GreenState *getInstance(){ static GreenState redReq; return &redReq; };
    void reqQuest(){ cout<<"Green is glowing for 1 sec"<<endl; }; };
class YellowState: public TLState{ 
    public: static YellowState *getInstance(){ static YellowState redReq; return &redReq; };
    void reqQuest(){ cout<<"Yellow is glowing for 1 sec"<<endl; }; };

class TLController{
    TLState *state;
    public:
        TLController() { state = nullptr; }
        
        void run(){
            int i = 0;
            while(i < MAX){
                state = RedState::getInstance();
                state->reqQuest();
                this_thread::sleep_for(chrono::seconds(1));
                
                state = GreenState::getInstance();
                state->reqQuest();
                this_thread::sleep_for(chrono::seconds(1));
                
                state = YellowState::getInstance();
                state->reqQuest();
                this_thread::sleep_for(chrono::seconds(1));
                i++;
            }
        }
};

int main()
{
    cout<<"State Design Pattern"<<endl;
     
    //start
    TLController obj;
    obj.run();

    return 0;
}
