#include "Security.h"

bool Security::check_pass(string password){

    string user_pass;
    cout << "Enter password : ";
    cin >> user_pass;

    if(password == user_pass){
        return true;
    } else {
        cout << " Incorect password " << endl;
        cout << " Try agin : ";
        cin >> user_pass;

        if(password == user_pass){
            return true;
        } else {
            cout << " Incorect password " << endl;
            cout << " Lust try : ";
            cin >> user_pass;
        }
            if(password == user_pass){
                return true;
            } else {

                return false;
            }

        }
    }

