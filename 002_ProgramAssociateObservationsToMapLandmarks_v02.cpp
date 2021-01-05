#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


class Coord{
	public:
		double x;
		double y;
		
		Coord(double x, double y){
			this->x = x;
			this->y = y;
		}

		~Coord(){};
};

double euclidian_distance(double x1,double y1,double x2,double y2){
	return(std::sqrt(std::pow(x1 - x2,2) + std::pow(y1 - y2,2)));
}

int min_index(std::vector<double> a){
	return(std::min_element(a.begin(),a.end()) - a.begin());
}

int main(){

	Coord obs1 = Coord(6,3);
	std::vector<Coord> obs{Coord(6,3),Coord(2,2),Coord(0,5)};

	// std::cout << "obs1 = (" << obs1.x << "," << obs1.y << ")" << std::endl ;

	std::vector<Coord> landmarks{Coord(5,3),Coord(2,1),Coord(6,1),Coord(7,4),Coord(4,7)};
	std::vector<double> dist(landmarks.size(),0);

	for(int o=0;o<obs.size();++o){

		for(int i=0;i<landmarks.size();++i){
			// dist[i] = std::sqrt(std::pow(obs[o].x - landmarks[i].x,2) + std::pow(obs[o].y - landmarks[i].y,2));
			dist[i] = euclidian_distance(obs[o].x,obs[o].y,landmarks[i].x,landmarks[i].y);
		}

		std::cout << "Landmark distances from obs[" << o << "] : ";
		for(int i=0;i<landmarks.size();++i){
			std::cout << dist[i] << ", ";
		}
		// int minElementIndex = std::min_element(dist.begin(),dist.end()) - dist.begin();
		int minElementIndex = min_index(dist);
		std::cout << "Shortest distance Landmark Number : " << minElementIndex << std::endl;
	}

}

/*
NOT : gcc Multiples3And5_v01.c -o Multiples3And5_v01

Use g++ (and a .cpp file extension) for C++ code.

g++ Multiples3And5_v01.cpp -o Multiples3And5_v01
*/