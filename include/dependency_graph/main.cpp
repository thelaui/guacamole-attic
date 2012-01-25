#include <iostream>
#include "Source.hpp"
#include "Destination.hpp"


int main ( int argc, char* argv[] ) {

	Source<int>* a = new Source<int>( 1 );
	std::cout << a->last_changed() << " , " << a->value() << std::endl;
	(*a) << 10;
		
	std::cout << a->last_changed() << " , " << a->value() << std::endl;
	a->touch();
	
	std::cout << a->last_changed() << " , " << a->value() << std::endl;
	
	Source<int>* b = new Source<int>( 1 );

	Destination<int>* c = new Destination<int>( 0, Destination<int>::SUM );
	std::cout << "is c independent: " << ( c->independent() ? "yes" : "no" ) << std::endl;
	c->depend_on( a );
	c->depend_on( b );	
	std::cout << "is c independent: " << ( c->independent() ? "yes" : "no" ) << std::endl;
	
	std::cout << "is number of dependencies: " << c->number_of_dependencies() << std::endl;
	
	std::cout << c->last_changed() << " , " << c->value() << std::endl;
	c->read();
	std::cout << c->last_changed() << " , " << c->value() << std::endl;
	
	(*b) << 12;
	(*a) << 56;
	
	c->read();	
	std::cout << c->last_changed() << " , " << c->value() << std::endl;

	(*b) << 77;
	
	c->read();	
	std::cout << c->last_changed() << " , " << c->value() << std::endl;
	delete a;
	delete b;
	delete c;	
	return 0;
};
