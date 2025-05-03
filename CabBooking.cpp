#include <bits/stdc++.h>
using namespace std;


enum TripStatus{
	COMPLETED,
	PENDING,
	ONGOING,
	CANCELLED
};


class User{
private:
	int userId;
	string name;
public:
	User(int userId,string name):userId(userId),name(name){};

	int getId(){
		return this->userId;
	}

	string getName(){return this->name;}
};

class Driver:public User{
	private:
		bool available;
	public:
		Driver(int userId,string name):User(userId,name),available(true){};
	bool isAvailable(){
		return available;
	}

	void setAvailable(bool value){
		available=value;
	}
};


class Trip{
private:
	int tripId;
	string pickUpLocation;
	string dropLocation;
	TripStatus status;
	User *user;
	Driver *driver;
public:
	Trip(int tripId,string pickUpLocation,string dropLocation,TripStatus status,User *user,Driver *driver):
	tripId(tripId),
	pickUpLocation(pickUpLocation),
	dropLocation(dropLocation),
	status(status),
	user(user),
	driver(driver)
	{};

	int getTripId(){return tripId;}

	string getPickUpLocation(){return pickUpLocation;}

	string getDropLocation(){return dropLocation;}

	TripStatus getStatus(){return status;}

	User *getUser(){return user;}

	Driver *getDriver(){return driver;}

	void setTripStatus(TripStatus status){
		this->status=status;
	}

};


class RidingApp{
private:
	int cnt=0;
	unordered_map<int,User*>users;
	unordered_map<int,Driver*>drivers;
	unordered_map<int,Trip*>trips;

public:
	void registerUser(int id,string name){
		User *newUser=new User(id,name);
		users[id]=newUser;
	}

	void registerDriver(int id,string name){
		Driver *newDriver=new Driver(id,name);
		drivers[id]=newDriver;
	}

	void bookTrip(int userId,string pickUpLocation,string dropLocation){
		if(users.find(userId)==users.end()){
			cout<<"User Not Registered! Please Register First"<<endl;
			return;
		}
		Driver* driver=findDriver();
		if(!driver)
		{
			cout<<"No Driver available at the Moment. Please Try Later!"<<endl;
			return ;
		}
		User *user=users[userId];
		int tripId=cnt;
		cnt++;
		Trip *trip=new Trip(tripId,pickUpLocation,dropLocation,TripStatus::ONGOING,user,driver);
		driver->setAvailable(false);
		trips[tripId]=trip;
		cout<<"Trip Booked Successfully from "<<pickUpLocation<<" to "<<dropLocation<<endl;
	}

	void cancelTrip(int tripId){
		if(trips.find(tripId)==trips.end()){
			cout<<"Not A Valid Trip"<<endl;
			return ;
		}
		Trip* trip=trips[tripId];
		if(trip->getStatus()==TripStatus::COMPLETED){
			cout<<"Trip already completed"<<endl;
			return ;
		} 
		if(trip->getStatus()==TripStatus::PENDING || (trip->getStatus()==TripStatus::ONGOING))
		{
			trip->getDriver()->setAvailable(true);
			trip->setTripStatus(TripStatus::CANCELLED);
			cout<<"!!! Trip CANCELLED"<<endl;
			return ;
		}
		cout<<"Trip Already CANCELLED"<<endl;
	}

	void completeTrip(int tripId){
		if(trips.find(tripId)==trips.end()){
			cout<<"Not A Valid Trip"<<endl;
			return ;
		}
		Trip* trip=trips[tripId];
		if(trip->getStatus()==TripStatus::ONGOING)
		{
			trip->getDriver()->setAvailable(true);
			trip->setTripStatus(TripStatus::COMPLETED);
		}
	}

	void printTrip(int tripId) {
	if (trips.find(tripId) == trips.end()) {
		cout << "Trip not found" << endl;
		return;
	}
	Trip* t = trips[tripId];
	cout << "Trip #" << t->getTripId() << ": "
	     << t->getUser()->getName() << " from " << t->getPickUpLocation()
	     << " to " << t->getDropLocation()
	     << " with driver " << t->getDriver()->getName()
	     << " | Status: " << statusToString((t->getStatus())) << endl;
	}

	Driver* findDriver()
	{
		for(auto &i:drivers){
			if(i.second->isAvailable()){
				return i.second;
			}
		}
		return NULL;
	}

	string statusToString(TripStatus status) 
	{
		switch(status) {
			case COMPLETED: return "COMPLETED";
			case PENDING: return "PENDING";
			case ONGOING: return "ONGOING";
			case CANCELLED: return "CANCELLED";
			default: return "UNKNOWN";
		}
	}

	~RidingApp() {
		for (auto& it : users) delete it.second;
		for (auto& it : drivers) delete it.second;
		for (auto& it : trips) delete it.second;
	}
};




int main(){
	RidingApp app;
	app.registerUser(1, "Alice");
	app.registerDriver(100, "Bob");
	app.bookTrip(1, "A", "B");
	app.completeTrip(0);
	app.printTrip(0);
	app.cancelTrip(0);
	app.cancelTrip(0);
}
