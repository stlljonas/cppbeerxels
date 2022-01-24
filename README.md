# cppbeerxels
C++ implementation of Beerxels project (previously in Python)


Architecture (Dependency Diagram):


Tiling <------------------------------------
                                           :
SmartCircle <-- Cap <-- CapShepherd <-- CapField
    ^                                      ;
    '---------------------------------------
                                           ;
                                           v
                                        Munkres