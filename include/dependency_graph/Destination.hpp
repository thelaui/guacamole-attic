#ifndef DESTINATION_HPP
#define DESTINATION_HPP
#include "DataField.hpp"
#include "Source.hpp"
#include <iostream>
#include <set>
#include <vector>



template < class T >
class Destination: public DataField<T> {
	public:
		enum EvaluationMode { UNDEFINED, LATEST, OLDEST, BIGGEST, SMALLEST, SUM };
		Destination( T value, EvaluationMode mode = UNDEFINED, Field* parent = NULL):
			DataField<T>(value, parent),
			mode_( mode )
			{};
		virtual ~Destination() {};
		void read( ) { 
				bool any_new_values( false );	
				std::vector< std::pair< TIME_TYPE , T > > results;
				TIME_TYPE time_at_start( TIME_FUNCTION );
				for ( Source<T>*  source : dependencies_ ) {
					
					any_new_values = ( this->last_changed_  < source->last_changed() ) | any_new_values  ;
					results.push_back( std::pair< TIME_TYPE, T >( source->last_changed() , source->value() ) );
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
					this->last_changed_ = time_at_start ; 
				};  
			};
		void depend_on( Source<T>* from ) { 
			dependencies_.insert( from ) ; 
			
		};

		int number_of_dependencies( ) const { return dependencies_.size(); };
		bool independent( ) const { return ( dependencies_.size() == 0 ) ? true : false; };	

	private:
		std::set< Source<T>* > dependencies_;
		EvaluationMode mode_;

};


#endif // DESTINATION_HPP
