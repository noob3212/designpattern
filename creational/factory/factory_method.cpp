#include <iostream>
#include <memory>

struct Transport{
	virtual void deliver()=0;
	virtual ~Transport() = default;
};

struct AirTransport:Transport{
	void deliver() override {
		std::cout << "Air Transport" << std::endl;
	}
	~AirTransport() = default ;  
};

struct RoadTransport:Transport{

	void deliver() override{
		std::cout << "Road Transport" << std::endl;
	}
	~RoadTransport() = default ;
};


struct SeaTransport:Transport{

	void deliver() override {
		std::cout<< "Sea Transport" << std::endl;
	}
	~SeaTransport() = default;

};


struct Logistics{
	virtual std::unique_ptr<Transport> create_transport() = 0;
	virtual ~Logistics() = default;
};

struct AirLogistics : Logistics{
	std::unique_ptr<Transport> create_transport() override{return std::make_unique<AirTransport>(); }
	~AirLogistics() = default;
};


struct RoadLogistics : Logistics{
	std::unique_ptr<Transport> create_transport() override {return std::make_unique<RoadTransport>();}
	~RoadLogistics() = default;
};



struct SeaLogistics : Logistics{
	std::unique_ptr<Transport> create_transport() override {return  std::make_unique<SeaTransport>();}
	~SeaLogistics() = default;
};

void client_code(Logistics &logistics){
	auto transport = logistics.create_transport();
	transport->deliver();
}

int main(){
RoadTransport road;
AirTransport air;
SeaTransport sea;
SeaLogistics sealogistics;
client_code(sealogistics); 


}
