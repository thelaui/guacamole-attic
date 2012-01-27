#define BOOST_TEST_MODULE FieldTest
#include <boost/test/minimal.hpp>
#include "DataField.hpp"


int test_main( int argc, char* argv[] ){

	int a = 1;
	int b = 20;
	int c = 100;
	DataField<int>* field_a = new DataField<int>( a );
	DataField<int>* field_b = new DataField<int>( b, DataField<int>::LATEST );
	DataField<int>* field_c = new DataField<int>( c, DataField<int>::LATEST );
	BOOST_CHECK( a == field_a->value() );
	BOOST_CHECK( b == field_b->value() );


	
	BOOST_CHECK( field_b->number_of_dependencies() == 0 );
	BOOST_CHECK( b == field_b->value() );
	field_b->depend_on( field_a );
	BOOST_CHECK( field_b->number_of_dependencies() == 1 );
	BOOST_CHECK( a == field_b->value() );
	a = 5;
	(*field_a) << a;
	
	field_b->read();
	BOOST_CHECK( a == field_b->value() );
	field_c->depend_on( field_b );
	a = 120020;
	(*field_a) << a;
	field_c->read();
	BOOST_CHECK( field_b->value() == a );
	BOOST_CHECK( field_c->value() == a );
	delete field_a;
	delete field_b;
	delete field_c;
	return 0;
}

