#include "Field.hpp"
#include "FieldContainer.hpp"
Field::Field( FieldContainer* master ):
	master_( master )
	{}

Field::~Field() {}

bool Field::is_dirty() const { return is_dirty_ ; }

void Field::touch() { 
	is_dirty_ = true;
	for ( auto dependend : audience_ ) {
		if ( ! dependend->is_dirty() ) dependend->touch();
	}
	master_->touch();
}


