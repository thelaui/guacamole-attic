#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "include/scenegraph/SceneGraph.hpp"
#include "include/scenegraph/Node.hpp"
#include "include/utils/debug.hpp"

#include <memory>

class SceneGraph::Iterator {
    public:
        Iterator(Node* node = NULL);

        int get_depth() const;

        std::string const& get_name() const;
        void set_name(std::string const& name) const;

        Eigen::Transform3f const& get_transform() const;
        void set_transform(Eigen::Transform3f const& transform) const;

        template <class T = Core>
        T* get_core() const {
            if (current_node_) {
                auto casted_core(current_node_->get_core<T>());
                if (!casted_core)
                    WARNING("The core you are trying to get is not of the type you expect!");
                return casted_core;
            }
            return NULL;
        }


        void set_core(Core* core) const;

        void scale(double x, double y, double z);
        void rotate(double angle, double x, double y, double z);
        void translate(double x, double y, double z);

        void operator ++();
        bool operator ==(Iterator const& rhs);
        bool operator !=(Iterator const& rhs);

        Iterator& operator << (std::string const& name);
        Iterator& operator << (Eigen::Transform3f const& transform);
        Iterator& operator << (Core*core);

    private:
        Node* current_node_;
        Node* start_node_;

        void find_next_node();

        static const std::string end_name_;
        static const Eigen::Transform3f end_transform_;
};

#endif //ITERATOR_HPP
