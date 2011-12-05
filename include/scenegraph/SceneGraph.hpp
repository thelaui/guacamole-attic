#ifndef SCENE_GRAPH_HPP
#define SCENE_GRAPH_HPP

class SceneGraph: {
    public:
        SceneGraph();
        virtual ~SceneGraph();

        Node* get_root() const;

        void lock();
        void unlock();

    private:
        Node* root_;

};

#endif // SCENE_GRAPH_HPP
