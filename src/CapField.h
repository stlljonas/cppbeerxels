#ifndef _CAP_FIELD_H_
#define _CAP_FIELD_H_

#include <filesystem>
#include <vector>
#include<opencv2/opencv.hpp>

class BeerxelTiling {
  public:
    virtual void optimalTiling() = 0;
    virtual std::vector<cv::Point> getNodes() = 0;
    virtual int getRadius() = 0;
};

class HoneyCombTiling : public BeerxelTiling {
  public:
    HoneyCombTiling() = default;
    HoneyCombTiling(const int refXDim, const int refYdim, const int maxNumNodes) : _referenceXDimension(refXDim), _referenceYDimension(refYdim), _maxNumberOfNodes(maxNumNodes) {};
    
    void optimalTiling() override;
    std::vector<cv::Point> getNodes() override;
    int getRadius() override;
    
    void showNodes();
    void showNodes(std::vector<cv::Point> nodes, int radius);

  private:
    std::vector<cv::Point> _tile(int radius);
    bool _circleIsInBound(int x, int y, int radius);
    bool _circleIsInBound(float xFloat, float yFloat, int radius);
    size_t _findNumberOfNodes(int radius);
    int _nearestInt(float f);
    void _centerNodes();
    std::vector<cv::Point> _nodes;
    int _radius;
    int _numberOfNodesX;
    int _numberOfNodesY;
    float _overhangX;
    float _overhangY;

    int _referenceXDimension;
    int _referenceYDimension;
    int _maxNumberOfNodes;
};

class CapField {
  public:
    CapField(std::filesystem::path referenceImagePath_) : referenceImagePath(referenceImagePath_) {};
    std::vector<cv::Scalar> referenceTargetColors;
    std::filesystem::path referenceImagePath;
    HoneyCombTiling honeyCombTiling;
};

#endif /* _CAP_FIELD_H_ */