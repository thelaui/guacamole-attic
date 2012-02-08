#ifndef SINGLE_FIELD_HPP
#define SINGLE_FIELD_HPP

#include <set>

#include "Field.hpp"
#include "FieldContainer.hpp"


template < class T >
class SingleField: public Field {
	public:
		SingleField( T value, FieldContainer* master ):
			Field( master ),
			value_( value ),
			read_from_( nullptr )
			{};
		virtual ~SingleField( ) {};
		bool is_dirty( ) const { return this->is_dirty_; };
		bool touch() { 
			if ( ! this->is_dirty_ ) {
				this->is_dirty_ = true ;
				this->master_->touch();
				for ( auto field :  audience_ ) {
					if ( ! field->is_dirty() ) {
						field->touch();
					};
				}
			};
		};
		
		void operator<<( T const& other ) {
			value_ = other;
			touch();
		};
		T value( ) {
			if ( ! this->is_dirty_ ){
				return value_;
			} else {


				is_dirty_ = false;
				if (  read_from_ != nullptr ) value_ = read_from_->value();
			 	else if ( master_->is_dirty() ) master_->evaluate();
				is_dirty_ = false;

				return value_;
	
			};
		};
		void depend_on( SingleField<T>* other ) {
			read_from_ = other;
			other->audience_.insert( this );
		};
	private:
		T value_;
		SingleField<T>* read_from_;
		std::set< Field* > audience_;
};

#endif // SINGLE_FIELD_HPP
