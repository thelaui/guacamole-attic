#ifndef SOURCE_HPP
#define SOURCE_HPP
#include "DataField.hpp"
#include <iostream>

template< class T >
class Source: public DataField<T> {
	public:
		Source( T value, Field* parent = NULL ):
			DataField<T>( value, parent )
			{};
		virtual ~Source() {};
		void operator<<( T other ) 
			{ 
				this->last_changed_ = TIME_FUNCTION ;
				this->value_ = other;
			};

};



#endif // SOURCE_HPP
