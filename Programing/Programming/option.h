#include <stdio.h>
#include <stdlib.h>  
#include <cassert>
#include <iostream>
#include <algorithm>
#include <ostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <sstream>

using namespace std;


namespace command {
    class Option{
    public:
        char c;
        string nom;
    public:
        Option(){}
        virtual ~Option(){}
        virtual void decode(char* argv[], int& argc) =0;
        virtual Option* clone() const=0;
    };
    
    
    template <typename T>
    class OptionField:public Option{
    public:
        T* var;
        OptionField(){var = new T;}
        virtual ~OptionField(){}
        //Constructeur de la classe OptionField.
        OptionField(char c1, string name,T &b){
            c = c1;
            nom = name;
            var = &b;
        }
        virtual Option* clone() const;
        // Decodage des arguments.
        virtual void decode(char* argv[], int& argc) {
            for(int i=1; i<argc; i++){
                stringstream str;
                stringstream str2;
                stringstream str3;
                str << argv[i];
                str2 << c;
                if(str.str().find("--"+nom) < str.str().length()){
                    string s = str.str();
                    s.replace(s.find("--"+nom), nom.length()+3, "");
                    stringstream str3;
                    str3 << s;
                    str3 >> (*var);
                    break;
                    
                }else if(str.str().find("-"+str2.str()) < str.str().length()){
                
                    str3 << argv[i+1];
                    str3 >> (*var);
                    break;
                }
            }
        }
    };
    
    template <typename T>
    Option* OptionField<T>::clone()const{
        return new OptionField<T>(*this);
    }
    
    //Réécrivons la classe pour les type booléens.
    template <>
    class OptionField<bool> :public Option{
        
    public:
        bool* var;
        OptionField(char ch,string name,bool &b){
            c = ch;
            nom=name;
            var = &b;
            *var=false;
        }
        virtual ~OptionField(){
        }
        
        Option* clone() const{
            return new OptionField<bool>(*this);
        }
        
        void decode (char * argv[], int &argc) {
            for(int i=1;i<argc;i++){
                stringstream str;
                stringstream str2;
                str <<argv[i];
                if(str.str().find("--"+nom)<str.str().length()){
                    *var =true;
                    break;
                }
                str2<<c;
                if(str.str().find("-"+str2.str())<str.str().length()){
                    *var = true;
                    break;

                }if(str.str().find(str2.str())<str.str().length() && (str.str())[0]=='-' && (str.str())[1]!='-'){
                    *var = true;
                    break;
                }
            }
        }
    };
    
    
    
    template <typename T>
    OptionField<T>* make_option(char c, string nom, T& var){
        OptionField<T>* opt=new OptionField<T>(c,nom,var);
        return opt;
    }
    template <>
    OptionField<bool>* make_option(char c, string nom, bool& var){
        OptionField<bool>* opt=new OptionField<bool>(c,nom,var);
        return opt;
    }
    class CmdLine{
        vector <Option*> opt;
    public:
        CmdLine(){}
        void add(Option * option){
            opt.push_back((option->clone()));
        }
        ~CmdLine(){
            for(int i=0;i<opt.size();i++){
                delete opt[i];
            }}
        void process(char * argv[], int &argc){
            for(int i=0;i<opt.size();i++){
                
                (*(opt[i])).decode(argv,argc);
            }
        }
    };
}