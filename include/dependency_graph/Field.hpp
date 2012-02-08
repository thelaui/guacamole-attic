#ifndef FIELD_HPP
#define FIELD_HPP

#include <set>

class FieldContainer;

class Field {
	public:
		Field( FieldContainer* master );
		virtual ~Field();
		void touch();
		bool is_dirty() const;
	protected:
		FieldContainer* master_;	
		bool is_dirty_;

		std::set< Field* > audience_;
};

#endif // FIELD_HPP
