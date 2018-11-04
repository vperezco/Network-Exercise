#include "network.h" 
#include <iostream> 
#include <algorithm>
#include "random.h"




void Network::resize(const size_t& n){

	values.clear(); 
	
	for (unsigned int i=0; i < n ; ++i ) {
		values.push_back(RNG.normal(0,1)); 
	}
}


bool Network:: add_link(const size_t& a, const size_t& b){
	
	if (( a >= values.size() or b>= values.size()) or a==b ) {
		return false;
	}
	
	for (std::multimap<size_t,size_t>::iterator i = links.begin() ; i != links.end(); ++i){
		if ((i->first == a and i->second == b) or (i->first ==b and i->second == a)){ 
			return false; 
		}
	}
	
	std::pair<size_t,size_t> linka = std::make_pair(a,b);
	std::pair<size_t,size_t> linkb = std::make_pair(b,a);
	links.insert(linka);
	links.insert(linkb);	
	return true; 
			    
}


size_t Network::random_connect(const double& m){
	
	links.erase(links.begin(), links.end()); 
  
	int counter = 0; 
	
	for (size_t i=0; i< values.size(); ++i){
		
		//determines how many links will the node i create 
		int numberLinks = RNG.poisson(m); 
		std::vector<int>NewNeighbors = std::vector<int>(numberLinks);
		
		// determine which nodes will be the neighbors of the node i 
		int TotalNeighbors = values.size(); 
		RNG.uniform_int(NewNeighbors, 0, TotalNeighbors);
		
		//creates links between nodes  
		for (unsigned int i(0); i < NewNeighbors.size(); ++i){
			size_t a= i; 
			size_t b= NewNeighbors[i];
			if( a != b){
			++counter;
			}	
			add_link(a ,b); 
		
		}
  }
  
  return counter;
}

 size_t Network::set_values(const std::vector<double>& newValues){
	 

	 size_t nodes_reset =0; 
	 if ( newValues.size() > values.size()){
		 for (size_t i =0; i < values.size() ; ++i ){
			 values[i] = newValues[i]; 
			 ++ nodes_reset; 
		 }
	 }
	 if ( newValue.size() <= values.size(){
		 for (size_t i =0; i < newValues.size() ; ++i ){
			 values[i] = newValues[i]; 
			 ++ nodes_reset;
		 }
	 } 
	 return nodes_reset;
}
 
 

 size_t Network:: size() const{
	 
	return values.size();
}

size_t Network::degree(const size_t &_n) const{
	
	return links.count(_n);
}

double Network::value(const size_t &_n) const{
	
	return values[_n];
}

std::vector<double> Network::sorted_values() const{
	
	std::vector<double> sorted_val(values);
	
	if (values.size() != 0){
		sort(sorted_val.begin(), sorted_val.end(), std::greater<double>()); 
	}
	return sorted_val;
}


std::vector<size_t> Network:: neighbors(const size_t& n) const{
	
	//new vector containing the index of the neighbors of the node n 
	std::vector <size_t> neighbor;
	
	
	for (std::multimap<size_t,size_t>::const_iterator it= links.begin(); it!=links.end(); ++it){
		if( it->first == n){
		neighbor.push_back(it->second);
		}
	}

	return neighbor;
}


