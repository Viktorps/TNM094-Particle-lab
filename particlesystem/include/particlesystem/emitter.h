#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include "particlesystem/particle.h"


class Emitter {
   
    public :
    //Constructor
    Emitter(glm:: vec2 _position, float _radius, float _delay, glm::vec4 _color)  {
        position = _position;
        radius = _radius;
        delay = _delay;
        color = _color;
    }
    
    //Destructor
    virtual ~ Emitter(){
    }
    
    //samma för alla emitters, tidsberoende.
    // dt = tiden som gått sedan förra omgången i loopen
    bool update(float dt) {
        time += dt;
        if (time > delay) {
            time = 0; // om går över ett, kör om och om igen
            return true;
        }
        return false;
    }
        
        virtual void createNewParticle(std::vector<Particle>& particle)  = 0;
        glm::vec2 position;
        float radius;
        glm::vec4 color;
    
    private :
    float time = 0, delay;
};


class Uniform : public Emitter {
    
    public:
    //Constructor
    Uniform(glm::vec2 _position, float _size, int _amount, float _angle, float color1, float color2, float color3) :
    Emitter(_position, _size, 1, {color1, color2, color3, 1}),amount(_amount), angle1(_angle) {
        color = {color1, color2, color3, 1};
    };
    
    //Destructor
    ~ Uniform() override {
    }
        
        void createNewParticle(std::vector<Particle>& particle) override {
          
            if(amount > 1){
                for (int i = 0; i < amount; ++i) {
                    double angle = i * 2 * 3.14/amount; // cirkel, ett helt varv. Omkretsen för
                    particle.push_back(Particle(position, {cos(angle), sin(angle)}, radius, color));
                }
            }else
                particle.push_back(Particle(position, {cos(angle1), sin(angle1)}, radius, color));
        }
    private :
    int amount;
    float angle1;
};

class Snowfall : public Emitter {
    
    public:
    //Constructor
    Snowfall(glm::vec2 _position, float _size, int _amount, float color1, float color2, float color3) :
    Emitter(_position, _size, (float)0.1, {color1, color2, color3, 1}) {
        amount = _amount;
        color = {color1, color2, color3, 1};
    };
    
    //Destructor
    ~ Snowfall() override {
    }
    
        void createNewParticle(std::vector<Particle>& particle) override {
          
            double newPosition = -0.9;
            int randomAmount = rand() % amount;
            
            for (int i = 0; i < randomAmount; i++) {
                
                int randPosition = rand() % 200 + 1;
                newPosition += (double)randPosition/100;
                
                int iSecret = rand() % 100 + 1;
                double randomAngle = (2.90*3.14/2) + (double)iSecret/100;
                
                std::cout << randomAngle << "\n";
                
                particle.push_back(Particle({newPosition, 1}, {cos(randomAngle), sin(randomAngle)}, radius, color));
                }
            }
    private :
    int amount;
};
