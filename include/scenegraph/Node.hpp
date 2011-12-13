#ifndef NODE_HPP
#define NODE_HPP

#include <list>
#include <memory>
#include <eigen2/Eigen/Geometry>

#include "include/scenegraph/SceneGraph.hpp"

class SceneGraph::Node {
    public:
        Node(std::string const& name, Eigen::Transform3f transform = (Eigen::Transform3f)Eigen::Matrix3f::Identity(),
             Core* core = NULL);

        virtual ~Node();

        void add_child(Node* child);
        void remove_child(Node* child);

        Node* get_parent() const;
        void set_parent(Node* parent);
        std::list<Node*> const& get_children() const;

        std::string const& get_name() const;
        void set_name(std::string const& name);

        Eigen::Transform3f const& get_transform() const;
        void set_transform(Eigen::Transform3f const& transform);

        template <class T = Core>
        T* get_core() const {
            return dynamic_cast<T*>(core_);
        }

        void set_core(Core* core);

        void scale(double x, double y, double z);
        void rotate(double angle, double x, double y, double z);
        void translate(double x, double y, double z);

        int get_depth() const;
        std::string const get_path() const;

    private:
        std::string name_;

        Node* parent_;
        std::list<Node*> children_;

        Eigen::Transform3f transform_;
        Core* core_;
};


#endif //NODE_HPP
