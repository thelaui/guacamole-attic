#include "Field.hpp"
#include "FieldContainer.hpp"
#include "SingleField.hpp"


FieldContainer::FieldContainer()
	{}

FieldContainer::~FieldContainer() {}

void FieldContainer::touch() {

		for ( auto field : outputs_ ) {
			if (! field->is_dirty() )	field->touch();
		}
	

}

bool FieldContainer::is_dirty() const {
	for ( auto field : inputs_ ) {
		if ( field->is_dirty() ) return true;	
	}
	return false;

}


void FieldContainer::add_output( Field* new_output ) { outputs_.insert( new_output ); }

void FieldContainer::add_input( Field* new_input ) { inputs_.insert( new_input ); }
