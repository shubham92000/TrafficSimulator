#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include "TrafficObject.h"

class Graphics
{
public:
    // constructor / desctructor

    Graphics(){
        this->terminate = nullptr;
    }

    Graphics(std::shared_ptr<Terminate> terminate){
        this->terminate = terminate ;
    }

    ~Graphics(){
        // for(auto & tr : _trafficObjects){
        //     std::cout  << tr.use_count() << std::endl;
        // }
        
        // std::cout << "Graphics destructor " << std::endl;
    }

    // getters / setters
    void setBgFilename(std::string filename) { _bgFilename = filename; }
    void setTrafficObjects(std::vector<std::shared_ptr<TrafficObject>> &trafficObjects) 
    {
        _trafficObjects = std::move(trafficObjects); 
    };

    // typical behaviour methods
    void simulate();

private:
    // typical behaviour methods
    void loadBackgroundImg();
    void drawTrafficObjects();

    // member variables
    std::vector<std::shared_ptr<TrafficObject>> _trafficObjects;
    std::string _bgFilename;
    std::string _windowName;
    std::vector<cv::Mat> _images;
    std::shared_ptr<Terminate> terminate ;
};

#endif