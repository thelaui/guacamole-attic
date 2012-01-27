#ifndef DATA_FIELD_HPP
#define DATA_FIELD_HPP
#include "Field.hpp"
#include <set>
#include <vector>

template< class T >
class DataField: public Field {
	public:

		enum EvaluationMode { UNDEFINED, LATEST, OLDEST, BIGGEST, SMALLEST, SUM };
		DataField( T value, EvaluationMode mode = UNDEFINED, Field* parent = NULL):
			Field( parent),
			mode_( mode ),
			value_( value )
			{ };
		virtual ~DataField() {};

		T value( ) {
			read(); 
			return value_; 
			};

		void operator<<( T other ) 
			{ 
				this->last_checked_ = TIME_FUNCTION ;
				this->value_ = other;
			};

		void read( ) {

			TIME_TYPE time_at_start( TIME_FUNCTION );
			switch ( dependencies_.size() ) { 
				case 0: break;
				case 1:
					this->value_ = ( *( dependencies_.begin()) )->value();
					break;
				default: {
					bool any_new_values( false );	
					std::vector< std::pair< TIME_TYPE , T > > results;

					for ( DataField<T>*  source : dependencies_ ) {
					
						any_new_values = ( this->last_checked_  < source->last_checked() ) | any_new_values  ;
						results.push_back( std::pair< TIME_TYPE, T >( source->last_checked() , source->value() ) );
					};
				
					if (any_new_values) {
						switch (mode_) {
							case LATEST :
								this->value_ = std::max_element( results.begin(), results.end(),  
									[&]( std::pair< TIME_TYPE, T > a , std::pair< TIME_TYPE, T > b ) { return ( a.first <  b.first ) ; })->second ;
								break;	
							case OLDEST :
								this->value_ = std::min_element( results.begin(), results.end(),  
									[&]( std::pair< TIME_TYPE, T > a , std::pair< TIME_TYPE, T > b ) { return ( a.first <  b.first ) ; })->second ;
								break;
							case BIGGEST :
								this->value_ = std::max_element( results.begin(), results.end(),  
									[&]( std::pair< TIME_TYPE, T > a , std::pair< TIME_TYPE, T > b ) { return ( a.second <  b.second ) ; })->second ;
								break;
							case SMALLEST :
								this->value_ = std::min_element( results.begin(), results.end(),  
									[&]( std::pair< TIME_TYPE, T > a , std::pair< TIME_TYPE, T > b ) { return ( a.second <  b.second ) ; })->second ;
								break;
							case SUM : {
								auto addend( results.begin() );
								T sum_value( addend->second );
								++addend;
								for ( ; addend != results.end() ; ++addend ) sum_value += addend->second ;
								this->value_ = sum_value;
								break;
							}
							case UNDEFINED :
							default:
								this->value_ = results.front().second;
								break;
							}
					};
				}
				}  

			this->last_checked_ = time_at_start ; 
			};
		void depend_on( DataField<T>* from ) { 
			dependencies_.insert( from ) ; 
			
		};

		int number_of_dependencies( ) const { return dependencies_.size(); };
		bool independent( ) const { return ( dependencies_.size() == 0 ) ; };	
	protected:
		T value_;
		std::set< DataField<T>* > dependencies_;
		EvaluationMode mode_;
};

#endif // DATA_FIELD_HPP
