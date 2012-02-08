#ifndef FIELD_CONTAINER_HPP
#define FIELD_CONTAINER_HPP

#include <set>



class Field;

class FieldContainer {
	public:
		FieldContainer();
		virtual ~FieldContainer();
		virtual void evaluate() = 0;
		void touch();
		bool is_dirty( ) const;
		void add_output( Field* );
		void add_input( Field* );	
	protected:
		bool is_dirty_;
		std::set< Field* > inputs_ ;
		std::set< Field* > outputs_;
};


#endif // FIELD_CONTAINER_HPP
