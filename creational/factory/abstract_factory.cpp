#include <iostream>
#include <memory>

struct Transport{
	virtual void deliver()=0;
	virtual ~Transport() = default;
};

struct Packaging{
    virtual void pack() = 0;
    virtual ~Packaging() = default;
};

struct AirTransport:Transport{
	void deliver() override {
		std::cout << "Air Transport" << std::endl;
	}
	~AirTransport() = default ;  
};

struct AirPackaging:Packaging{
	void pack() override {
		std::cout << "Air packaging" << std::endl;
	}
	~AirPackaging() = default ;  
};

struct RoadTransport:Transport{

	void deliver() override{
		std::cout << "Road Transport" << std::endl;
	}
	~RoadTransport() = default ;
};

struct RoadPackaging:Packaging{
	void pack() override {
		std::cout << "Road packaging" << std::endl;
	}
	~RoadPackaging() = default ;  
};


struct SeaTransport:Transport{

	void deliver() override {
		std::cout<< "Sea Transport" << std::endl;
	}
	~SeaTransport() = default;

};


struct SeaPackaging:Packaging{
	void pack() override {
		std::cout << "Sea packaging" << std::endl;
	}
	~SeaPackaging() = default ;  
};

struct LogisticsFactory{
	virtual std::unique_ptr<Transport> create_transport() = 0;
	virtual std::unique_ptr<Packaging> create_packaging() =0;
    virtual ~LogisticsFactory() = default;
};

struct AirLogistics : LogisticsFactory{
	std::unique_ptr<Transport> create_transport() override{return std::make_unique<AirTransport>(); }
	std::unique_ptr<Packaging> create_packaging() override{return std::make_unique<AirPackaging>();}
    ~AirLogistics() = default;
};


struct RoadLogistics : LogisticsFactory{
	std::unique_ptr<Transport> create_transport() override {return std::make_unique<RoadTransport>();}
	std::unique_ptr<Packaging> create_packaging() override {return std::make_unique<SeaPackaging>();}
    ~RoadLogistics() = default;
};



struct SeaLogistics : LogisticsFactory{
	std::unique_ptr<Transport> create_transport() override {return  std::make_unique<SeaTransport>();}
    std::unique_ptr<Packaging> create_packaging() override {return std::make_unique<SeaPackaging>();}
	~SeaLogistics() = default;
};

void client_code(LogisticsFactory &logistics){
	auto transport = logistics.create_transport();
    auto packaging = logistics.create_packaging();
	transport->deliver();
    packaging->pack();
}

int main(){
    RoadTransport road;
    AirTransport air;
    SeaTransport sea;
    SeaLogistics sealogistics;
    client_code(sealogistics); 


}
