#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <list>

class Core;

class Node {
    public:
        Node(Core* core);
        virtual ~Node();

        void add_child( Node* child );

        std::list<Node*> const& get_children() const;
        std::shared_ptr<Core> get_core() const;

    private:
        Node* parent_;
        std::list<Node*> children_;

        std::shared_ptr<Core> core_;

};

#endif // NODE_HPP
