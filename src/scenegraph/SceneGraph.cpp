#include "include/scenegraph/SceneGraph.hpp"

#include "include/scenegraph/Core.hpp"
#include "include/utils/PathParser.hpp"
#include "include/utils/debug.hpp"

SceneGraph::SceneGraph():
    root_(new Node("/")),
    end_(new Node("end")),
    last_search_request_(),
    last_search_result_() {}


SceneGraph::~SceneGraph() {
    delete root_;
}

void SceneGraph::add_node(std::string const& path_to_parent, std::string const& node_name,
                          Eigen::Transform3f const& transform, Core* core) {
    Node* searched_parent(find_node(path_to_parent));

    auto searched_parents_children(searched_parent->get_children());
    bool valid_name(true);
    for (auto child : searched_parents_children)
        if (child->get_name() == node_name) {
            ERROR("A node with the name \"%s\" already exists at this level of the tree! Please choose another one",
                   node_name.c_str());
            valid_name = false;
            break;
        }

    if (valid_name)
        searched_parent->add_child(new Node(node_name, transform, core));
}

Eigen::Transform3f const& SceneGraph::get_transform(std::string const& path_to_node) const {
    return find_node(path_to_node)->get_transform();
}

Eigen::Transform3f SceneGraph::get_relative_transform(std::string const& path_to_node,
                                                          std::string const& path_to_relative_node) const {
    Eigen::Transform3f result(Eigen::Transform3f::Identity());

    find_node(path_to_node);
    std::list<Node*> node_results(last_search_result_);

    find_node(path_to_relative_node);
    std::list<Node*> relative_node_results(last_search_result_);

    auto starting_point(node_results.end());

    for (auto it(node_results.begin()); it != node_results.end(); ++it)
        if (*it == relative_node_results.back())
            starting_point = it;

    if (starting_point == node_results.end()) {
        ERROR("\"%s\" and \"%s\" are not part of the same subtree! Returning identity matrix instead.",
              path_to_node.c_str(),
              path_to_relative_node.c_str());
        return result;
    } else {
        for (auto node(starting_point); node != node_results.end(); ++node) {
            result = result * (*node)->get_transform();
        }
        return result;
    }
}

SceneGraph::Iterator SceneGraph::get_iterator(std::string const& path_to_node) {
    return Iterator(find_node(path_to_node));
}

SceneGraph::Iterator SceneGraph::begin() {
    return get_iterator("/");
}

SceneGraph::Iterator SceneGraph::end() {
    return Iterator(end_);
}

Node* SceneGraph::find_node(std::string const& path_to_node,
                                        std::string const& path_to_start) const {

    if (path_to_node == last_search_request_)
        return last_search_result_.back();

    else {
        PathParser parser;
        parser.parse(path_to_node);
        auto path_data(parser.get_parsed_path());

        Node* to_be_found(path_to_start == "/" ? root_ : find_node(path_to_start));

        last_search_request_ = path_to_node;
        last_search_result_.clear();
        last_search_result_.push_back(to_be_found);

        for (auto node_name : path_data) {

            if (to_be_found->get_name() != node_name) {

                for (auto child : to_be_found->get_children()) {
                    if (child->get_name() == node_name) {
                        to_be_found = child;
                        break;
                    }
                }

                if (to_be_found->get_name() != node_name) {
                    WARNING("Node \"%s\" does not exist! Creating it with default parameters.",
                             node_name.c_str());
                    Node* new_child(new Node(node_name));
                    to_be_found->add_child(new_child);
                    to_be_found = new_child;
                }

                last_search_result_.push_back(to_be_found);
            }
        }

        return to_be_found;
    }
}

