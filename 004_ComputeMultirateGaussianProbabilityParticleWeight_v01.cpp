#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

/*
	calculate each measurement's Multivariate-Gaussian probability density using
	 the formula above and the previously calculated values. In this example the
	  standard deviation for both x and y is 0.3.
	  Note that x and y are the observations in map coordinates from the 
	  landmarks quiz and \mu_xμx, \mu_yμy are the coordinates of the nearest 
	  landmarks. These should correspond to the correct responses from previous
	   quizzes.
*/

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

void distance_obs_landmarks(std::vector<std::vector<double>>& d,
	std::vector<Coord> obs,
	std::vector<Coord> ldmarks){

	for(int o=0;o<obs.size();++o){

		for(int i=0;i<ldmarks.size();++i){
			d[o][i] = euclidian_distance(obs[o].x,obs[o].y,ldmarks[i].x,
				ldmarks[i].y);
		}
	}
}

void print_distance_obs_landmarks(std::vector<std::vector<double>> d,
	int ldmarks_size){

	for(int o=0;o<d.size();++o){

		std::cout << "Landmark distances from obs[" << o << "] : ";
		for(int i=0;i<ldmarks_size;++i){
			std::cout << d[o][i] << ", ";
		}
		std::cout << std::endl;
	}
}

void associate_obs_landmarks(std::vector<int>& assoc, std::vector<Coord> obs,
	std::vector<Coord> ldmarks, std::vector<std::vector<double>> d){

	for(int o=0;o<obs.size();++o){
		assoc[o] = min_index(d[o]);
	}
}

void print_associate_obs_landmarks(std::vector<int> assoc){

	for(int o=0;o<assoc.size();++o){
		std::cout << "obs[" << o << "] : associated with Landmark Number : ";
		std::cout << assoc[o] << std::endl;
	}
}

void multivariate_gaussian_probability(std::vector<double>& prob,
	std::vector<Coord> obs, Coord std_dev, 
	std::vector<int> nearest_i, std::vector<Coord> landmarks){
	int i(0);
	double x(0.0),y(0.0),mux(0.0),muy(0.0),a(1.0),b(0.0),c(0.0),exponent(0.0);
	double stdx(std_dev.x), stdy(std_dev.y);

	if((stdx == 0) || (stdy == 0)){ return; }

	for(int o=0;o<obs.size();++o){
		// index of nearest landmark
		i = nearest_i[o];
		// coordinates observation
		x = obs[o].x; y = obs[o].y;
		// coordinates nearest landmark
		mux = landmarks[i].x; muy = landmarks[i].y;
		// computation probability
		a = 1 / (2*M_PI*std_dev.x*std_dev.y);
		b = (x - mux) / stdx;
		c = (y - muy) / stdy;
		prob[o] = a * std::exp(-(b*b + c*c)/2);
	}
}

void print_multivariate_gaussian_probability(std::vector<double> prob){
	
	std::cout << "CALCULATION OBSERVATIONS Multivariate-Gaussian ";
	std::cout << "probability density" << std::endl;
	for(int o=0; o < prob.size(); ++o){
		std::cout << "obs[" << o << "] : Multivariate-Gaussian probability ";
		std::cout << "density : " << prob[o] << std::endl;
	}
}

void compute_particle_weight(double& w, std::vector<double> prob){
	
	for(int o=0; o < prob.size(); ++o){
		w *= prob[o];
	}
}



int main(){
	// list of Measurements/Observations in map coordinates
	std::vector<Coord> obs{Coord(6,3),Coord(2,2),Coord(0,5)};
	// list of map landmarks in map coordinates
	std::vector<Coord> landmarks{Coord(5,3),Coord(2,1),Coord(6,1),Coord(7,4),
		Coord(4,7)};
	// list of distances between Observations and map landmarks
	std::vector<std::vector<double>> \
				dist(obs.size(),std::vector<double> (landmarks.size(),0));
	// observations nearest landmark indexes
	std::vector<int> obs_landmark_association(obs.size(),0);
	// Multivariate-Gaussian Probability Density for each observations
	std::vector<double> obs_gaussian_prob(obs.size(),0.0);
	// Standard deviation in x,y coordinates for Observation Prob. calculation
	Coord std_dev = Coord(0.3,0.3);
	// particle weights given observations, landmarks
	double particle_weight(1.0);


	std::cout << "CALCULATION LANDMARK DISTANCES FROM OBSERVATIONS " ;
	std::cout << "AND ASSOCATIONS TO LANDMARKS" << std::endl;

	distance_obs_landmarks(dist, obs, landmarks);
	associate_obs_landmarks(obs_landmark_association, obs, landmarks, dist);

	// print infos
	print_distance_obs_landmarks(dist, landmarks.size());
	print_associate_obs_landmarks(obs_landmark_association);

	// Compute Multivariate-Gaussian Probability Density for all
	// observation points
	multivariate_gaussian_probability(obs_gaussian_prob, obs, std_dev, 
			obs_landmark_association, landmarks);
	print_multivariate_gaussian_probability(obs_gaussian_prob);

	// compute + print particle weight (multipy all probabilities)
	compute_particle_weight(particle_weight, obs_gaussian_prob);
	std::cout << "Particle_weight = " << particle_weight << std::endl;

}

/*
NOT : gcc Multiples3And5_v01.c -o Multiples3And5_v01

Use g++ (and a .cpp file extension) for C++ code.

g++ Multiples3And5_v01.cpp -o Multiples3And5_v01
*/