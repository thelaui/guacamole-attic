#ifndef ADDER_HPP
#define ADDER_HPP

#include "SingleField.hpp"
#include "FieldContainer.hpp"

template< class T >
class adder: public FieldContainer {
	public:
		adder():

			FieldContainer(),
			output_value_( 0, this )
			{ this->add_output( &output_value_ ); };
		virtual ~adder() {

				for (auto input : this->inputs_ ) {
					delete input;
				}	
				};
		void evaluate( ) {

			T result( 0 );
			for ( auto field : this->input_values_ ) {
				result += field->value();
			}
			output_value_ << result;
			this->is_dirty_ = false;

		};
		SingleField<T>* output(  ) { return &output_value_; };
		SingleField<T>* add_input_value(  )	{
			SingleField<T>* field_ptr( new SingleField<T>( 0, this ) );
			input_values_.insert( field_ptr );
			this->add_input( field_ptr );
			return field_ptr;
				
		};	

	private:
		SingleField<T> output_value_;
		std::set< SingleField<T>* > input_values_;
		

};

#endif // ADDER_HPP
