#ifndef COMPOSITE_FIELD_HPP
#define COMPOSITE_FIELD_HPP

#include "Field.hpp"

class CompositeField: public Field { 
	public:
		CompositeField( ):
			Field( NULL )
			{};
		virtual ~CompositeField() {};
		

};
#endif // COMPOSITE_FIELD_HPP
