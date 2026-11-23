
#include <iostream>
#include <fstream>
#include <vector>
#include "Simulation.hpp"

using namespace std;

int main() {

    // Create the solar system simulation
    Simulation solarSystem;

    // Create the Sun
    CelestialBody sun("Sun", 1.989e30, Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0));

    // Create the Earth
    CelestialBody earth("Earth", 5.972e24, Vector3(1.496e11, 0.0, 0.0), Vector3(0.0, 29780.0, 0.0));

    // Add the Sun and Earth to the simulation
    solarSystem.addBody(sun);
    solarSystem.addBody(earth);

    // Simulation settings
    const double dt = 3600.0;     // 1 hour per time step
    const int totalSteps = 8760;  // 365 days

    // Open CSV file for writing
    ofstream file("orbit.csv");

    // Check whether the file opened successfully
    if (!file.is_open()) {
        cerr << "Error: Could not open orbit.csv" << endl;
        return 1;
    }

    // Write CSV column headers
    file << "time,x,y,z\n";

    // Retrieve the bodies stored inside the simulation
    const vector<CelestialBody>& bodies = solarSystem.getBodies();

    // Record Earth's initial position at time = 0
    const Vector3& initialPosition = bodies[1].getPosition();

    file << 0.0 << "," << initialPosition.getX() << "," << initialPosition.getY() << "," << initialPosition.getZ() << "\n";

    // Run the simulation for one year
    for (int i = 0; i < totalSteps; i++) {

        // Advance the simulation by one hour
        solarSystem.step(dt);

        // Calculate elapsed simulation time
        double currentTime = (i + 1) * dt;

        // Get Earth's updated position
        const Vector3& earthPosition = bodies[1].getPosition();

        // Save time and coordinates to the CSV file
        file << currentTime << "," << earthPosition.getX() << "," << earthPosition.getY() << "," << earthPosition.getZ() << "\n";
    }

    // Close the CSV file
    file.close();

    // Retrieve Earth's final position
    const Vector3& finalPosition = bodies[1].getPosition();

    // Display the results
    cout << "===== Solar System Simulation =====" << endl;
    cout << "Simulated time: 365 days" << endl;

    cout << "Earth's Final Position:" << endl;
    cout << "X: " << finalPosition.getX() << " m" << endl;
    cout << "Y: " << finalPosition.getY() << " m" << endl;
    cout << "Z: " << finalPosition.getZ() << " m" << endl;

    cout << "Orbital data saved to orbit.csv" << endl;

    return 0;
}
