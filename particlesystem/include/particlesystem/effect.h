#pragma once

#include "particle.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include <vector>
#include <cmath>

class Effects {
    
    public :
    //Constructor
    Effects(glm::vec2 _position, float _radius, float _velocity, glm::vec4 _color) {
        position = _position;
        radius = _radius;
        velocity = _velocity;
        color = _color;
    }

    //destructor
    virtual ~ Effects() {
    }
    
    virtual void affectParticle(std::vector<Particle>& particle) = 0 ;
    glm::vec2 position;
    glm::vec4 color;
    float radius;
    
    //protected för att wind och gravity ska nå.
    protected:
    float velocity;
};

class Wind : public Effects {
    
    public :
    //Constructor
    Wind(glm::vec2 _position, float _strength): Effects(_position, 5, _strength, {0, 0, 1, 1}) {
        
    };
    //destructor
    ~ Wind() override {
    }
    
    void affectParticle(std::vector<Particle>& particle) override {
    
               for(size_t i = 0; i < particle.size(); i++) {
                       particle[i].velocity.x -= velocity * (float)0.01;
                       particle[i].velocity.y -= velocity * (float)0.01;
               }
    }
};

class Gravity : public Effects {
    public :
    //Constructor
    Gravity(glm::vec2 _position, float _gravity): Effects(_position, 10, _gravity, {0, 1, 1, 1}) {
        
    };
    //destructor
    ~ Gravity() override {
    }
    
    void affectParticle(std::vector<Particle>& particle) override {
        
        for(size_t i = 0; i < particle.size(); i++){
            // pythagoras för det "visuella"
            float distance = (float)sqrt(pow(position.x - particle[i].position.x, 2) + pow(position.y - particle[i].position.y, 2));
            // vinkeln tas fram mha två sidor på traingeln, för att bara ta diagonalen. Distance = hyp
            float angle = acos((position.x - particle[i].position.x)/distance);
            // Om vinkeln är på negativa sidan flytta till positiva.
            if(position.y < particle[i].position.y)
                angle *= -1;
            
            // Formel för gravity, beroende av kraften * vinkeln. Dras till punkten.
            particle[i].velocity.x += (float)(velocity * cos(angle) * pow(distance,2) * 0.01);
            particle[i].velocity.y += (float)(velocity * sin(angle) * pow(distance,2) * 0.01);
        }
    }
    
    private:
    
};
