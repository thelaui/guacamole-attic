#ifndef DATA_FIELD_HPP
#define DATA_FIELD_HPP
#include "Field.hpp"

template< class T >
class DataField: public Field {
	public:
		DataField( T value, Field* parent = NULL ):
			Field( parent ),
			value_( value ),
			last_changed_( TIME_FUNCTION )
			{ };
		virtual ~DataField() {};

		T value( ) const { return value_; };

	protected:
		T value_;

};

#endif // DATA_FIELD_HPP
