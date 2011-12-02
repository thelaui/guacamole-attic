#ifndef NODE_HPP
#define NODE_HPP

#include<shared_ptr>

class Node {
    public:
        Node();
        virtual ~Node();

        void add_child( Node* child );

        std::list<Node*> const& get_children() const;
        std::shared_ptr<Core> get_core() const;

    private:

};

#endif // NODE_HPP
