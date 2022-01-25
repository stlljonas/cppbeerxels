#ifndef _TILING_H_
#define _TILING_H_

#include <opencv2/opencv.hpp>
#include <vector>

class BeerxelTiling {
public:
  virtual void optimalTiling() = 0;
  virtual std::vector<cv::Point> getNodes() = 0;
  virtual int getRadius() = 0;
};

class HoneyCombTiling : public BeerxelTiling {
public:
  HoneyCombTiling() = default;
  HoneyCombTiling(const int refXDim, const int refYdim, const int maxNumNodes)
      : _referenceXDimension(refXDim), _referenceYDimension(refYdim),
        _maxNumberOfNodes(maxNumNodes){};

  void optimalTiling() override;
  std::vector<cv::Point> getNodes() override;
  int getRadius() override;

  void showNodes();
  void showNodes(std::vector<cv::Point> nodes, int radius);
  void setDimensions(const int xDimension, const int yDimension);
  void setMaxNumNodes(const int maxNumNodes);

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

#endif /* _TILING_H_ */