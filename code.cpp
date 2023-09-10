#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<string.h>
using namespace std;

// this class contain user id and password . And cheak valid id or password.
class user
{
    map<string, string> users_public;   //it contain public user email id and password
    map<string, string> users_private;  //it contain private user email id and password
    public:

    user()
    {
        ifstream in("account_public.txt");
        while(!in.eof())                        //it read public user email id and password
        {                                       // from file;
            string s1,s2;
            in>>s1;
            in>>s2;
            users_public[s1]=s2;
        }
        in.close();
        in.open("account_private.txt");
        while(!in.eof())
        {                           //it read public user email id and password from file
            string s1,s2;
            in>>s1;
            in>>s2;
            users_private[s1]=s2;
        }
        in.close();
    }
    void insert_public(string key,string value) 
    {                                           //insert new email id and passord in public map
        users_public[key]=value;
    }
    void insert_private(string key,string value)
    {
        users_private[key]=value;             //insert new email id and passord in public map
    }
    int is_private(string s)
    {
        if(users_private.find(s)!=users_private.end())
            return 1;                   //it cheack account is private or not
        return 0;
    }
    int is_public(string s)
    {
        if(users_public.find(s)!=users_public.end())
            return 1;                   //it cheack account is public or not
        return 0;
    }
    int is_password_currect(string s1,string s2)
    {                                   //it cheack password is currect or not
        if(is_public(s1))
        {
            if(users_public[s1]==s2)        
                return 1;
            return 0;
        }
        else if(is_private(s1))
        {
            if(users_private[s1]==s2)
                return 1;
                return 0;
        }   
        return 0; 
    }
    ~ user()
    {   
        ofstream out("account_private.txt");
        string st1,st2;
        for (auto it = users_private.begin(); it != users_private.end(); it++) 
        {
            st1=it->first;                  // write back all email id and password of
            st2=users_private[st1];         // private account in file.
            out<<st1<<"\t"<<st2<<"\n";
        }
        out.close();
        out.open("account_public.txt");
        for (auto it = users_public.begin(); it != users_public.end(); it++) 
        {
            st1=it->first;                  // write back all email id and password of
            st2=users_public[st1];          // public account in file.
            out<<st1<<"\t"<<st2<<"\n";
        }
        out.close();
    }
};
// This class contain information about users like name, phone number, DOB.
class profile
{
    string email;
    string name;
    string phone;
    string DOB;
    int followers;
    int following;
    string type;

    public:

    void set_email(string s)            //set email id
    {
        email=s;
    }
    string get_email()              //return email id
    {
       return email;
    }
    void set_followers(int i)           //set follower
    {
        followers=i;
    }
    void set_following(int i)           // set following
    {
        following=i;
    }
    void set_name(string s)         //set name
    {
        name=s;
    }
    string get_name()               //return name
    {
        return name;
    }
    void set_phone(string s)        //set phone number
    {
        phone=s;
    }
    string get_phone()              //return phone number
    {
        return phone;
    }
    void add_followers()            // increase followers by one
    {
        followers++;
    }
    int get_followers()             // return followers
    {
        return followers;
    }
    void sub_followers()            // decrease follower by one
    {
        followers--;
    }
    void add_following()            // increase following by one
    {
        following++;
    }
    void sub_following()            //decrease following by one
    {
        following--;
    }
    int get_following()             // return following
    {
        return following;
    }
    void set_type(string s)         //set type of account (public/private)
    {
        type=s;
    }
    void set_DOB(string s)          //set date of birth
    {
        DOB=s;
    }
    string get_DBO()        //return date of birth
    {
        return DOB;
    }
};

//this calss contain all follower and all following of user;
class friends
{
    vector<string> follower;       //it contain all followers
    vector<string> following;       //it contain all following
    string e;                          //email id of user;
    public:

    friends(string email)
    {
        e=email;
        ifstream in(email+"follower.txt");
        while(!in.eof())                    //read id of all follower from file.
        {
            string s1;
            in>>s1;
            follower.push_back(s1);
        }
        in.close();
        in.open(email+"following.txt");     //read id of all follower from file.
        while(!in.eof())
        {
            string s1;
            in>>s1;
            following.push_back(s1);
        }
        in.close();
    }
    int is_follower(string s)
    {
        for(int i=0;i<follower.size();i++)  //it cheack is follower or not.
        {
            if(s==follower[i])
                return 1;
        }
        return 0;
    }
    int is_following(string s)              //it cheack is following or not.
    {
        for(int i=0;i<following.size();i++)
        {
            if(s==following[i])
                return 1;
        }
        return 0;
    }
    void insert_follower(string s)         // add follower
    {
        follower.push_back(s);
    }
    void insert_following(string s)         //add following
    {
        following.push_back(s);
    }

    friend void see_follower(string email);       //make friend function for use private member fild.
    friend void see_following(string email);
    friend void post(string email);

    ~friends()
    {
        ofstream out(e+"following.txt");
        for(int i=0;i<following.size();i++)
        {
            string s;               //write back id of all following into file. 
            s=following[i];
            out<<s<<"\n";
        }
        out.close();
        out.open(e+"follower.txt");
        for(int i=0;i<follower.size();i++)
        {
            string s;
            s=follower[i];          //write back id of all follower into file.
            out<<s<<"\n";
        }
        out.close();
    }
};
//This fuction create account 
void create_account(user &users)
{
    string email,passward;
    std::cout<<"\t email Id\t";          
    cin>>email;                     //enter email id
    if(!(email.find("@gmail.com")!= string::npos))      //it cheack email id is valid or not
    {
        cout<<"invalid email id\n";
    }
    else if(users.is_private(email))             //cheack email id already exit or not
       std:: cout<<"already exit\n\n"<<endl;     // if exit ,then back
    else if(users.is_public(email))
        std::cout<<"already exit\n\n"<<endl;
    else
    {
        profile acc;                            //take persnal information
        string name,phone,DOB;                  // and store in profile class
        //char[10] phon;
        cout<<"passward(without space)\t";
        cin>>passward;
        cout<<"name\t";
        cin>>name;
        acc.set_name(name);
        cout<<"Phone No.\t";
        cin>>phone;
        acc.set_phone(phone);
        cout<<"DOB(dd-mm-yyyy)\t";
        cin>>DOB;
        acc.set_DOB(DOB);
        acc.set_email(email);
        acc.set_followers(0);
        acc.set_following(0);

        cout<<"1 for public account\n2 for private account\n";
                int i;
                while(1)                    
                {
                    cin>>i;
                    if(i==1||i==2)
                        break;
                    cout<<"enter valid number";
                }
                if(i==2)
                    users.insert_private(email,passward);      //set account is private
                else if(i==1)
                    users.insert_public(email,passward);       //set account is public

        ofstream out(email+".txt");         //write back all information of profile 
        out.write((char*)&acc,sizeof(acc));     //class in file in binary form
        out.close();
        out.open(email+"follower.txt");         //create file for store id of follower
        out.close();
        out.open(email+"following.txt");        //create file for store id of following
        out.close();
        out.open(email+"message.txt");          //create file for store message
        out.close();
        out.open(email+"post.txt");         //create file for store all post
        out.close();
        cout<<"account create successfully\n";
    }
}

//This function display all information about user
void see_profile(profile acc)
{
    cout<<"Name  "<<acc.get_name()<<endl;
    cout<<"phone no. "<<acc.get_phone()<<endl;
    cout<<"DOB  "<<acc.get_DBO()<<endl;
    cout<<"followers "<<acc.get_followers()<<endl;
    cout<<"following "<<acc.get_following()<<endl<<endl;
}
//This function follow the other users 
void follow(profile &acc,user users)
{
    string fe;
    cout<<"Enter email id of which you want to follow\t";
    cin>>fe;            //it contain id of user whoes want follow
    if(users.is_private(fe)||users.is_public(fe))   //it cheak id is exit or not
    {
        friends f(acc.get_email()); //create friends class 
        if(f.is_following(fe))      //cheack it is allready following or not
        {
            cout<<"you already following\n";
        }
        else
        {                       //if it not following then
            acc.add_following();        //increase following user who is login
            profile fp;             
            ifstream in(fe+".txt");     //read profile of user whoes want to follow
                in.read((char*)&fp,sizeof(fp));
                in.close();
            fp.add_followers();     //increase follower of user whoes want to follow
            ofstream out(fe+".txt");
                out.write((char*)&fp,sizeof(fp));//write back all information of user in bineary from
                out.close();
            friends  ff(fe);            //make friend class 
            f.insert_following(fe);             //add following
            ff.insert_follower(acc.get_email());//add follower
            cout<<"successfully following\n\n";
        }
    }
    else
        cout<<"This email id  not found\n";
}
// This function sent message to other user
void message(profile acc)
{
    string fe;
    cout<<"Enter email id of which you want to message\t";
    cin>>fe;                //it contain id of user to sent message
    friends f(acc.get_email());     
    if(f.is_follower(fe)||f.is_following(fe))   //cheack id is follower or following or not
    {
        string message;
        cout<<"message\t";      //message which is sent

        cin>>message;
       // getline(cin,message);
        fstream out;
            out.open(acc.get_email()+"message.txt",ios::app);
            out<<"sended to "<<fe<<"\n";        //append message in user message file
            out<<message<<"\n\n";               //who sent message
            out.close();

            out.open(fe+"message.txt",ios::app);    //append message in user message file
            out<<"sended by "<<acc.get_email()<<"\n";//whoes sent message
            out<<message<<"\n\n";
            out.close();
            cout<<"Message send successfully\n";
    }
    else
        cout<<"This is not your friend\n";
}
// this function update information of user
void update_profile(profile &acc)
{
    int n;
    string s;
    while(1)
    {
        cout<<"1 for change name\n";
        cout<<"2 for change phone number\n";
        cout<<"3 for change DOB\n";
        cout<<"4 for back\n";
        cin>>n;
        if(n==1)
        {
            cout<<"Enter new name\t";
            cin>>s;
            acc.set_name(s);        //it change name of user
        }
        else if(n==2)
        {
            cout<<"Enter new phone number\t";
            cin>>s;
            acc.set_phone(s);       //it change phone number of user
        }
        else if(n==3)
        {
            cout<<"Enter new DOB\t";
            cin>>s;             
            acc.set_DOB(s);         // it change  DOB of user
        }
        else if (n==4)
        {
            break;
        }
        else
            cout<<"invalid option\n";
    }

}
// this is friend function of friends class. it display id of all follower
void see_follower(string email)
{
    friends f(email);
    for(int i=0;i<f.follower.size();i++)
    {
        cout<<i+1<<" "<<f.follower[i]<<endl;
    }
    cout<<endl;
}
// this is friend function of friends class. it display id of all following
void see_following(string email)
{
    friends f(email);
    for(int i=0;i<f.following.size();i++)
    {
        cout<<i+1<<" "<<f.following[i]<<endl;
    }
    cout<<endl;
}
//this function display all message from message file of user
void see_message(string email)
{
    string s;
    ifstream in(email+"message.txt");
    while(!in.eof())        //read message file and display line by line
        {
            getline(in,s);
            cout<<s<<endl;
        }
        in.close();

}
//This fuction display other pofile which is your friend or public account
void see_other_profile(user users,string s,profile acc)
{
    friends f(acc.get_email());
    if(users.is_public(s)||f.is_follower(s)||f.is_following(s)) //it cheack account is public of friend or not.
    {
        profile op;
        ifstream in(s+".txt");
           in.read((char*)&op,sizeof(op));  //read profile from file and store in profile class
            in.close();
        see_profile(op); //call see_profile for display informaation
    }
    else
        cout<<"This is private account\n\n";
}
// This function display all post
void see_post(string email)
{
    string s;
    ifstream in(email+"post.txt");  //read post file of user
    while(!in.eof())
        {
            getline(in,s);      //read and display line by line
            cout<<s<<endl;
        }
    in.close();
}

// This frien function of friends class.This function post the contain, which is see by all follower or following
void post(string email)
{
    string post;
    cout<<"Post  ";
    cin>>post;      //take post from user
    //getline(cin,post);
    friends f(email);       
    //update all post file of user who is follower
    for(int i=0;i<f.follower.size();i++)
    {
        fstream out;
            out.open(f.follower[i]+"post.txt",ios::app);
            out<<"post by "<<email<<"\n";   
            out<<post<<"\n\n";
            out.close();
    }
        //update all post file of user who is following
    for(int i=0;i<f.following.size();i++)
    {
        fstream out;
            out.open(f.following[i]+"post.txt",ios::app);
            out<<"post by "<<email<<"\n";
            out<<post<<"\n\n";
            out.close();
    }
        //update post file of user who post
    fstream out;
            out.open(email+"post.txt",ios::app);
            out<<"post by me "<<"\n";
            out<<post<<"\n\n";
            out.close();
    cout<<"posted successfully\n";
}
//This fuction is login account and provide various features.
//
void login(user &users,profile acc)
{
    while(1)
    {
        int n;
        for(int i=0;i<60;i++)
            cout<<"_";
            cout<<endl;
        //this features which is use by user.
        cout<<"1 for see profile\n";
        cout<<"2 for follow\n";
        cout<<"3 for send message \n";
        cout<<"4 for see message\n";
        cout<<"5 for see follower\n";
        cout<<"6 for see following\n";
        cout<<"7 for post\n";
        cout<<"8 for see post\n";
        cout<<"9 for update profile\n";
        cout<<"10 for see other profile\n";
        cout<<"11 for logout\n\n";
        cout<<"12 for delete account\n";
        cout<<"select your option\t";
        cin>>n;
        for(int i=0;i<60;i++)
            cout<<"_";
            cout<<endl;

        if(n==1)
        {
            see_profile(acc);   //call see_profile for display information of user
        }
        else if(n==2)
        {
            follow(acc,users);      //call follow for follow some one.
        }
        else if(n==3)
        {
            message(acc);        // call message for messaging other
        }
        else if(n==4)
        {
            see_message(acc.get_email());   //display all message
        }
        else if(n==5)
        {
            see_follower(acc.get_email());      //diplay all follower id 
        }
        else if(n==6)
        {
            see_following(acc.get_email());     //display all following id
        }
        else if(n==7)
        {
            post(acc.get_email());          //post any information
        }
        else if(n==8)
        {
            see_post(acc.get_email());      //display all post posted by your friend and you
        }
        else if(n==9)
        {
            update_profile(acc);        //call function for upadte profile like name, pnone number.
        }
        else if(n==10)
        {
            string s;
            cout<<"email id of which you want to see\t";
            cin>>s;
            see_other_profile(users,s,acc);     //you can see profile of other users.
        }
        else if(n==11)
        {
            string email=acc.get_email();
            ofstream out(email+".txt");
           out.write((char*)&acc,sizeof(acc)); //write back all information of profile class
            out.close();                       // in file in binary form.
            break;
        }
        else if(n==12)
        {
            if(users.is_private(acc.get_email()))
            {

            }
            else 
            {
                
            }
        }
        else
            cout<<"invalid input\n";
    }
}

int main()
{
    for(int i=0;i<80;i++)
            cout<<"_";
    cout<<endl;
    cout<<"\n\t\t\tWelcome\n\t\tsocila media plateform\n";
    
    while(1)
    {
        int n;
        for(int i=0;i<60;i++)
            cout<<"_";
        //we have three option of create account , login , exit.
        cout<<"\n\t\t 1 for create account \n";
        cout<<"\t\t 2 for login\n";
        cout<<"\t\t 3 for exit\n";
        cout<<"select option\t";
        cin>>n;
        for(int i=0;i<60;i++)
            cout<<"_";
            
            cout<<endl;
        user users;     //create users class for store all id and password of allready exited users.

        if(n==1)
        {
            create_account(users); //call function for create account.
        } 
        else if (n==2)
        {
            string email,passward;
            cout<<"email id\t";
            cin>>email;         //take id from user
            
            if(users.is_private(email)||users.is_public(email))  //cheack id exit or not
            {
                cout<<"Passward\t";
                    cin>>passward;
                    if(users.is_password_currect(email,passward)) //cheack passoword is right or wrong.
                    {
                        profile account; //create profile class 
                        ifstream in(email+".txt");  //read all information and set profile class
                        in.read((char*)&account,sizeof(account));
                        in.close();
                        login(users,account); //call login functon for use features
                    }
                    else
                        cout<<"incorrect passward\n";
                
            }
            else    
                cout<<"incorrect email\n\n";

        }
        else if(n==3)
        {
            cout<<"exit"<<endl; 
            break;              //break loop and end program.
        }
        else 
            cout<<"enter valid option/n";
        
    }

    return 0;

}