#include <chrono>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <thread>
#include <tuple>

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
class Vehicle;
using PricingFunction = std::function<int(const Vehicle& vehicle, TimePoint parked_since, TimePoint parked_until)>;

class Vehicle {
private:
    std::string registration_plate;
    std::optional<TimePoint> parked_since;

public:
    Vehicle(std::string registration_plate) : registration_plate(registration_plate) {}
    virtual ~Vehicle() = default;

    virtual double area() const = 0;
    virtual std::string type() const = 0;

    virtual std::optional<TimePoint> park(TimePoint since) {
        this->parked_since = since;
        return this->parked_since;
    }

    virtual std::optional<TimePoint> park() {
        return this->park(std::chrono::system_clock::now());
    }

    void drive() {
        this->parked_since = std::nullopt;
    }

    friend class ParkingLot;
    friend class Ticket;
};

class Car : public Vehicle {
public:
    Car(std::string registration_plate) : Vehicle(registration_plate) {}
    virtual double area() const { return 20; };
    virtual std::string type() const { return "Car"; };
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(std::string registration_plate) : Vehicle(registration_plate) {}
    virtual double area() const { return 5; };
    virtual std::string type() const { return "Motorcycle"; };
};



class Ticket {
private:
    std::string vehicle_type;
    std::string registration_plate;
    double taken_up_area;
    TimePoint parked_since;
    TimePoint parked_until;
    PricingFunction pricing_function;
    int amount_to_pay;

public:
    Ticket(const Vehicle& vehicle, TimePoint parked_since, TimePoint parked_until, PricingFunction pricing_function) 
        : vehicle_type(vehicle.type()),
          registration_plate(vehicle.registration_plate),
          taken_up_area(vehicle.area()), 
          parked_since(parked_since), 
          parked_until(parked_until), 
          pricing_function(pricing_function), 
          amount_to_pay(pricing_function(vehicle, parked_since, parked_until)) {}

    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
        std::time_t raw_parked_since = std::chrono::system_clock::to_time_t(ticket.parked_since);
        std::time_t raw_parked_until = std::chrono::system_clock::to_time_t(ticket.parked_until);

        auto duration = ticket.parked_until - ticket.parked_since;
        auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
        duration -= hours;
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
        duration -= minutes;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);

        os << "======= Parking Ticket =======\n"
           << "Registration: " << ticket.registration_plate << "\n"
           << "Vehicle: " << ticket.vehicle_type << "\n"
           << "Area: " << ticket.taken_up_area << " m^2\n\n"
           << "Since: " << std::put_time(std::localtime(&raw_parked_since), "%Y-%m-%d %H:%M:%S") << "\n"
           << "Until: " << std::put_time(std::localtime(&raw_parked_until), "%Y-%m-%d %H:%M:%S") << "\n"
           << "Duration: "
           << std::setfill('0') << std::setw(2) << hours.count() << ":"
           << std::setfill('0') << std::setw(2) << minutes.count() << ":"
           << std::setfill('0') << std::setw(2) << seconds.count() << "\n\n"
           << "Amount to pay: " << ticket.amount_to_pay << " PLN\n"
           << "==============================\n";
        
        return os; 
    }
};



class ParkingLot {
private:
    std::map<std::string, std::unique_ptr<Vehicle>> parked_vehicles;
    PricingFunction pricing_strategy;

public:
    ParkingLot(PricingFunction strategy) : parked_vehicles(), pricing_strategy(std::move(strategy)) {};

    std::string park(std::unique_ptr<Vehicle> vehicle) {
        vehicle->park();

        std::string registration_plate = vehicle->registration_plate;
        this->parked_vehicles.insert_or_assign(registration_plate, std::move(vehicle));
        return registration_plate;
    }

    std::optional<std::tuple<std::unique_ptr<Vehicle>, Ticket>> drive_out(std::string registration_plate) {
        auto node = parked_vehicles.extract(registration_plate);
        if (node.empty()) {
            return std::nullopt;
        }

        auto parked_until = std::chrono::system_clock::now();

        std::unique_ptr<Vehicle> vehicle = std::move(node.mapped());

        Ticket ticket(*vehicle, vehicle->parked_since.value(), parked_until, pricing_strategy);
        vehicle->drive();
        return std::make_tuple(std::move(vehicle), ticket);
    }
};



int main() {
    auto pricing_strategy = [](const Vehicle& vehicle, TimePoint since, TimePoint until) -> int {
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(until - since).count();

        std::string type = vehicle.type();
        if (type == "Car") {
            return 10 + (seconds * 2);
        } else if (type == "Motorcycle") {
            return (vehicle.area() * 1) + (seconds * 1);
        } else {
            return vehicle.area() * 5; 
        }
    };

    ParkingLot parking_lot{pricing_strategy};
    std::unique_ptr<Vehicle> car = std::make_unique<Car>("KRK2026");
    std::unique_ptr<Vehicle> motorcycle = std::make_unique<Motorcycle>("KRK7432");

    std::string car_plate = parking_lot.park(std::move(car));
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::string motorcycle_plate = parking_lot.park(std::move(motorcycle));
    std::this_thread::sleep_for(std::chrono::seconds(5));

    auto [car_ptr1, car_ticket1] = parking_lot.drive_out(car_plate).value();
    auto [motorcycle_ptr1, motorcycle_ticket1] = parking_lot.drive_out(motorcycle_plate).value();

    std::cout << car_ticket1;
    std::cout << motorcycle_ticket1;

    car_plate = parking_lot.park(std::move(car_ptr1));
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto [car_ptr2, car_ticket2] = parking_lot.drive_out(car_plate).value();

    std::cout << car_ticket2;
}
