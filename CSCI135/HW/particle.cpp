/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 9 F
*/
/*
This program makes your own particle.
*/

#include <iostream>
using namespace std;

// Structure to store 3D coordinates
struct Coord3D
{
    double x, y, z;
};

// Particle class declaration
class Particle
{
public:
    // Data members
    Coord3D position;
    Coord3D velocity;

    // Constructor
    Particle(double x, double y, double z, double vx, double vy, double vz)
    {
        position.x = x;
        position.y = y;
        position.z = z;
        velocity.x = vx;
        velocity.y = vy;
        velocity.z = vz;
    }

    // Function to update the velocity
    void setVelocity(double vx, double vy, double vz)
    {
        velocity.x = vx;
        velocity.y = vy;
        velocity.z = vz;
    }

    // Function to get the current position
    Coord3D getPosition()
    {
        return position;
    }

    // Function to move the particle based on its velocity
    void move(double dt)
    {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        position.z += velocity.z * dt;
    }
};

// Function to dynamically allocate memory and create a particle
Particle *createParticle(double x, double y, double z, double vx, double vy, double vz)
{
    return new Particle(x, y, z, vx, vy, vz);
}

// Function to set the particle's velocity
void setVelocity(Particle *p, double vx, double vy, double vz)
{
    p->setVelocity(vx, vy, vz);
}

// Function to get the particle's position
Coord3D getPosition(Particle *p)
{
    return p->getPosition();
}

// Function to move the particle by updating its position
void move(Particle *p, double dt)
{
    p->move(dt);
}

// Function to delete the dynamically allocated memory for the particle
void deleteParticle(Particle *p)
{
    delete p;
}

int main()
{
    // Create a new particle
    Particle *p = createParticle(1.0, 1.5, 2.0, 0.1, 0.2, 0.3);
    double time = 0.0;
    double dt = 0.1;

    // Simulate the motion of the particle
    while (time < 3.0)
    {
        // Update its velocity
        setVelocity(p, 10.0 * time, 0.3, 0.1);

        // Move the particle
        move(p, dt);
        time += dt;

        // Print the particle's position
        Coord3D pos = getPosition(p);
        cout << "Time: " << time << " \t";
        cout << "Position: " << pos.x << ", " << pos.y << ", " << pos.z << endl;
    }

    // Remove the particle and deallocate memory
    deleteParticle(p);

    return 0;
}