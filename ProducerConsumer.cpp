// #include <cuchar>
// #include <map>
// #include <set>
// #include <list>
// #include <cmath>
// #include <ctime>
// #include <deque>
// #include <queue>
// #include <stack>
// #include <string>
// #include <bitset>
// #include <cstdio>
// #include <limits>
// #include <type_traits>
// #include <vector>
// #include <climits>
// #include <cstring>
// #include <cstdlib>
// #include <fstream>
// #include <numeric>
// #include <sstream>
// #include <iostream>
// #include <algorithm>
// #include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

// Topic -> T1

// Producer P1 
// Consumer C1

// c1 -> T1

// P1 (T1, "") -> publis the message on T1


// c1 -> process the messag recieved on t1.

//Topic = name,queue<message>, // published

//enum{PUBLISHER||CONSUMER}

//User(
//id,<TopicID>,type
//)

////
//Publisher = id, methods

//Consumer =id,<TopicId>


//Manager= <Consumer>, <TopicId>



//app => app.publish(P,topicName,mess);

class Topic{
    string name;
    vector<string>messages;
    
    public:
    Topic(string name,string message):name(name){
        messages.push_back(message);
    };
    
    void addMessage(string message){
        messages.push_back(message);
    }
    
    string getName(){return name;}
};

enum UserType{
    PROCUCER,
    CONSUMER,
};


class User{
    protected:
    string id;
    UserType type;
    public:
    User(string id,UserType type):id(id),type(type){};
    
    UserType getType(){
        return this->type;
    }
    string getId(){
        return this->id;
    }
};

class Publisher:User{
    public:
    Publisher(string id):User(id,UserType::PROCUCER){};
};


class Subscriber:User{
    protected:
    vector<string>topicNames;
    public:
    Subscriber(string id):User(id,UserType::CONSUMER){};
    string getId(){
        return this->id;
    }
    
    vector<string> getTopics(){
        return topicNames;   
    }
    
    void addTopic(string topicName){
        this->topicNames.push_back(topicName);
    }
    
};

class Manager{
    public:
    unordered_map<string,Subscriber*>subscribers;
    unordered_map<string,Topic*>topics;
    
    //O(1)
    void addSubscribers(Subscriber& user){
        subscribers[user.getId()]=&user;
    }
    //T.C=O(1) 
    void subscribeTopic(Subscriber& user,Topic topic){
        topics[topic.getName()]=&topic;
        Subscriber* subscriber=subscribers[user.getId()];
        subscriber->addTopic(topic.getName());
    }
    
    
    //Time- O(Len(subs)*(No.ofTopic));
    //Spac=(Above+Topic)
    void publishMessgae(Publisher& user,string topicName,string message){
        Topic* topic=topics[topicName];
        topic->addMessage(message);
        for(auto& subscriber:subscribers){
            for(auto topicNames:subscriber.second->getTopics())
            {
                if(topicNames==topicName){
                    cout<<subscriber.second->getId()<<" recieved "<<message<<endl;
                }
            }
        }
    }
    
};

int main() {
    
      Manager app;
      Publisher P1("producer1");
      Publisher P2("producer2");
      Subscriber C1("consumer1");
      Subscriber C2("consumer2");
      Subscriber C3("consumer3");
      Subscriber C4("consumer4");
      Subscriber C5("consumer5");
      Topic T1("topic1","HEY");
      Topic T2("topic2","HEY");
      app.addSubscribers(C1);
      app.addSubscribers(C2);
      app.addSubscribers(C3);
      app.addSubscribers(C4);
      app.addSubscribers(C5);
      
      app.subscribeTopic(C1,T1);
      app.subscribeTopic(C2,T1);
      app.subscribeTopic(C3,T1);
      app.subscribeTopic(C4,T1);
      app.subscribeTopic(C5,T1);
      
      app.subscribeTopic(C1,T2);
      app.subscribeTopic(C3,T2);
      app.subscribeTopic(C4,T1);
      
      app.publishMessgae(P1,T1.getName(),"Hurray1");
      app.publishMessgae(P1,T1.getName(),"Hurray2");
      app.publishMessgae(P2,T1.getName(),"Hurray3");
      app.publishMessgae(P1,T2.getName(),"Hurray4");
      app.publishMessgae(P2,T2.getName(),"Hurray5");
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}