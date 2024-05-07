/*
#include <rendering/window.h>
#include <example/randomsystem.h>
#include <particlesystem/particlesystem.h>

#include <fmt/format.h>

#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

#include "particlesystem/particle.h"
#include "particlesystem/effect.h"
#include "particlesystem/emitter.h"

//#include "Windows.h"

#include <iostream>




 * This application represents the "Client" the uses your particle system
 
int main() try {
    rendering::Window window("Particle System v0.0.2 pre-release alpha", 850, 850);

    // Creates an example system with a 1000 particles.
    // This should be replaced with your new particle system
    const size_t numParticles = 1000;
    example::RandomSystem system{numParticles};

    float speed = 1.0f;
    float size = 1.0f;
    float color1 = 1.0f;
    float color2 = 1.0f;
    float color3 = 1.0f;
    bool running = true;

    while (running) {
        window.beginFrame();

        // Update the example system.
        // This should be replaced with a call to the new particle system
        system.update(window.time(), speed);

        // Clear screen with color
        window.clear({0, 0, 0, 1});

        // Draw particles
        // This should also be adjusted to work with the new particle system
        window.drawPoint({0.0,0.0}, size, {color1, color2, color3, 1.0});
        //window.drawPoints(system.getPosition(), system.getSize(), system.getColor());
        

        // Example user interface, extend for your needs.
        // Might add controls for effects and emitters etc.
        {
            window.beginGuiWindow("UI");
            window.text("Choose speed!");
            window.sliderFloat("Speed", speed, 0.001f, 10.0f);
            window.sliderFloat("Size", size, 1.0f, 100.0f);
            window.sliderFloat("color channal 1", color1, 0.0f, 1.0f);
            window.sliderFloat("color channal 2", color2, 0.0f, 1.0f);
            window.sliderFloat("color channal 3", color3, 0.0f, 1.0f);
            if (window.button("Close application")) {
                running = false;
            }
            window.endGuiWindow();
        }

        window.endFrame();
        running = running && !window.shouldClose();
    }

    return EXIT_SUCCESS;
} catch (const std::exception& e) {
    fmt::print("{}", e.what());
    return EXIT_FAILURE;
}
*/

#include <particlesystem/Tracy.hpp>
#include <rendering/window.h>
#include <particlesystem/particlesystem.h>
#include "particlesystem/particle.h"
#include "particlesystem/effect.h"
#include "particlesystem/emitter.h"

#include <cmath>
#include <cstdlib>
#include <vector>

#include <fmt/format.h>

int main(int, char**) try {
    rendering::Window window("Particle System v0.0.1 pre-release alpha", 850, 850);

    double prevTime = 0.0;
    float speed = 1.0f; //hur snabb simuleringen är
    float angle = 0.0f;
    float size = 10.0f;
    float color1 = 1.0f;
    float color2 = 0.0f;
    float color3 = 1.0f;
    int amount = 10;
    //float amount;
    float gravity = 0.0f;
    float wind = 0.0f;
    float x, y;
    bool running = true;

    // skapa partikelsystem utanför loop
    
    Particlesystem particleSystem{};
    
    while (running) {
        window.beginFrame();

        const double t = window.time();
        const double dt = t - prevTime; // inte samma tid för varje frame
        prevTime = t;

        // Clear screen with color
        window.clear({0, 0, 0, 1});

        // Draw particles
        particleSystem.update((float)(dt * speed));
        particleSystem.draw(window, x, y, angle);

        // UI
        {
            window.beginGuiWindow("UI");
            window.text("ParticleSystem!!");
            window.sliderFloat("Speed", speed, 0.001f, 10.0f);
            window.sliderFloat("Size", size, 1.0f, 100.0f);
            window.sliderInt("Amount of particles", amount, 1, 20);
            window.sliderFloat("Color1", color1, 0.0f, 1.0f);
            window.sliderFloat("Color2", color2, 0.0f, 1.0f);
            window.sliderFloat("Color3", color3, 0.0f, 1.0f);
            window.sliderFloat("X", x, -1.0, 1.0);
            window.sliderFloat("Y", y, -1.0, 1.0);
            //Emitter
            
            //Directional
            window.sliderFloat("Angle:",angle,0.0, float(2*3.14));
            
            //Uniform
            if (window.button("New uniform emitter")) {
                particleSystem.emitters.push_back(new Uniform({x, y}, size, amount, angle, color1, color2, color3));
            }
            
            if (window.button("New Snowfall emitter")) {
                particleSystem.emitters.push_back(new Snowfall({x, y}, size, amount, color1, color2, color3));
            }
            
            if (window.button("Reset all")) {
                particleSystem.remove();
            }
            //Effects
            
            //Gravity
            window.sliderFloat("Select gravity", gravity, 0.0, 10);
            
            window.sliderFloat("Select wind", wind, -10, 10);
            
            if (window.button("New Gravity effect")) {
                particleSystem.effects.push_back(new Gravity({x, y}, gravity));
            }
            //Wind
            
            if (window.button("New Wind effect")) {
                particleSystem.effects.push_back(new Wind({x, y}, wind));
            }
            
            if (window.button("Close application")) {
                running = false;
            }
            window.endGuiWindow();
        }

        window.endFrame();
        running = running && !window.shouldClose();
    }

    return EXIT_SUCCESS;
} catch (const std::exception& e) {
    fmt::print("{}", e.what());
    return EXIT_FAILURE;
}


