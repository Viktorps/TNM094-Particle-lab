#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <rendering/window.h>

#include "particle.h"
#include "effect.h"
#include "emitter.h"

class Particlesystem {
    public :
    
    // Constructor, fylla fönster med partiklar
    Particlesystem() {
        
    }
    
    //kolla om en partickel ska finnas
    void update(float dt) {
        
        //lever fortfarande particeln?
        for(size_t i = 0; i < particle.size(); ++i) {
            if(!particle[i].alive()){
                particle.erase(particle.begin() + (int)i);
            }
        }
        
        
        for(Particle& p : particle ) {
            p.update(dt);
        }
        
    
        for(Emitter* e : emitters) {
            if(e->update(dt)) {
                e->createNewParticle(particle);
            }
        }
        
        for(Effects* e : effects) {
            e->affectParticle(particle);
        }
    }
    
    //kolla om en partickel ska finnas
    void remove() {
        // Delete all Emitter pointers and clear the vector
        for(Emitter* e : emitters) {
            if (e != nullptr) { // Check if the pointer is not null
                delete e;
                e = nullptr; // Optional: Set the pointer to nullptr after deletion
            }
        }
        emitters.clear(); // Clear the vector to remove all dangling pointers

        // Delete all Effects pointers and clear the vector
        for(Effects* e : effects) {
            if (e != nullptr) { // Check if the pointer is not null
                delete e;
                e = nullptr; // Optional: Set the pointer to nullptr after deletion
            }
        }
        effects.clear(); // Clear the vector to remove all dangling pointers
    }
    
    
    void draw(rendering::Window& window, float x, float y, float angle) {
        
        window.drawPoint({x, y}, 20, {1, 1, 1, 1});
        //start
        window.drawPoint({x + 0.04* cos(angle), y + 0.04 * sin(angle)}, 15, {1, 1, 1, 1});
        
        for(const Particle& p : particle ) {
            window.drawPoint(p.position, p.radius, p.color);
        }
       /*
        for(Emitter* e : emitters ) {
            window.drawPoint(e->position, e->radius, e->color);
        }
        for(Effects* e : effects ) {
            window.drawPoint(e->position, e->radius, e->color);
        }
        */
    }
    
    std::vector<Particle> particle; // skapar bara en typ av partiklar
    std::vector<Emitter*> emitters; // kan inte skapa egna saker, behöver pointer, abstract class
    std::vector<Effects*> effects; // också pointer
    
};
