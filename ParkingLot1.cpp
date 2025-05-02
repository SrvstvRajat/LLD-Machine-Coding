#include <bits/stdc++.h>
using namespace std;


enum VehicleType{
	BIKE,
	CAR,
	TRUCK
};


class Vehicle {
private:
	int id;
	VehicleType type;

public:
	Vehicle(int id,VehicleType type):id(id),type(type){};

	int getVehicleId(){
		return id;
	}

	VehicleType getVehicleType(){
		return type;
	}
};

class ParkingSpot{
private:
	int id;
	VehicleType type;
	bool isAvailable;
	int parkedVehicleId;

public:
	ParkingSpot(int id,VehicleType type,bool isAvailable=true):id(id),type(type),isAvailable(isAvailable){};

	int getParkingSpotId(){return id;}

	VehicleType getPakingVehicleType(){return type;}

	bool canPark(){return isAvailable;}

	bool parkVehicle(int parkedVehicleId){
		this->isAvailable=false;
		this->parkedVehicleId=parkedVehicleId;
		return true;
	}

};

class ParkingFloor{
private:
	int floorNo;
	int bikeCapacity;
	int carCapacity;
	int truckCapacity;
	map<int,ParkingSpot*>Spots;
public:

	ParkingFloor(int floorNo,int bikeCapacity=2,int carCapacity=10,int truckCapacity=5):floorNo(floorNo),bikeCapacity(bikeCapacity),carCapacity(carCapacity),truckCapacity(truckCapacity){
		int id=1;
		for(int i=0;i<bikeCapacity;i++){
			ParkingSpot* spot=new ParkingSpot(id,VehicleType::BIKE,true);
			Spots[id++]=spot;
		}
		for(int i=0;i<carCapacity;i++){
			ParkingSpot* spot=new ParkingSpot(id++,VehicleType::CAR,true);
			Spots[id++]=spot;
		}
		for(int i=0;i<truckCapacity;i++){
			ParkingSpot* spot=new ParkingSpot(id++,VehicleType::TRUCK,true);
			Spots[id++]=spot;
		}
	}

	int getFloorNo(){return floorNo;}

	int getBikeCapacity(){return bikeCapacity;}


	int getCarCapacity(){return carCapacity;}

	int getTruckCapacity(){return truckCapacity;}

	bool isSpotAvailable(VehicleType type){
		for(auto spot:Spots){
			if(spot.second->getPakingVehicleType()==type && spot.second->canPark()){
				return spot.second->canPark();
			}
		}
		return false;
	}

	int parkVehicle(Vehicle vehicle){
		for(auto spot:Spots){
			if(spot.second->getPakingVehicleType()==vehicle.getVehicleType() && spot.second->canPark()){
				spot.second->parkVehicle(vehicle.getVehicleId());
				return spot.first;
			}
		}
		return -1;
	}

};


class ParkingLot{
private:
	int numOfFLoors;
	vector<ParkingFloor*>Floors;
public:

	ParkingLot(int numOfFLoors):numOfFLoors(numOfFLoors){
		for(int i=1;i<=numOfFLoors;i++){
			ParkingFloor* curFloor=new ParkingFloor(i);
			Floors.push_back(curFloor);
		}
	}

	int getNumberOfFloors(){return numOfFLoors;}


	void park(Vehicle vehicle){
		for(auto curFloor:Floors){
			if(curFloor->isSpotAvailable(vehicle.getVehicleType()))
			{
				int spotId=curFloor->parkVehicle(vehicle);

				cout<<spotId<<endl;

				cout<<"Vehicle of "<<vehicle.getVehicleId()<<" parked Successfully at Floor Number: "<<curFloor->getFloorNo()<<" and SpotID : "<<spotId<<endl;
				return ;
			}
		}
		cout<<"Parking Space Not Avalable"<<endl;
	}

};

int main(){
	int numOfFLoors=2;
	// cin>>numOfFLoors;

	Vehicle MyBike(45678,VehicleType::BIKE);

	Vehicle MyBike2(78,VehicleType::BIKE);
	Vehicle MyBike3(0001,VehicleType::BIKE);

	ParkingLot MyParking(numOfFLoors);


	MyParking.park(MyBike);

	MyParking.park(MyBike2);

	MyParking.park(MyBike3);



}