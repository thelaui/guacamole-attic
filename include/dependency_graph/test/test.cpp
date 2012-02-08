#define BOOST_TEST_MODULE FieldTest
#include <boost/test/minimal.hpp>
#include "SingleField.hpp"
#include "FieldContainer.hpp"
#include "adder.hpp"

int test_main( int argc, char* argv[] ){
	adder<int> adder_1;
	SingleField<int>* output =  adder_1.output();
			
	SingleField<int>* input_1 = adder_1.add_input_value();
	SingleField<int>* input_2 = adder_1.add_input_value();
	SingleField<int>* input_3 = adder_1.add_input_value();
		
	(*input_1) << 100;
	
	
	BOOST_CHECK(  input_1->is_dirty()  );
	BOOST_CHECK( ! input_2->is_dirty()  );
	BOOST_CHECK( ! input_3->is_dirty()  );
	BOOST_CHECK(  adder_1.is_dirty()  );
	BOOST_CHECK(  output->is_dirty()  );

	BOOST_CHECK( output->value() == 100 );

	BOOST_CHECK( ! input_1->is_dirty()  );
	BOOST_CHECK( ! input_2->is_dirty()  );
	BOOST_CHECK( ! input_3->is_dirty()  );
	BOOST_CHECK( ! adder_1.is_dirty()  );
	BOOST_CHECK( ! output->is_dirty()  );

}

