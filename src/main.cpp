#include "include/utils/debug.hpp"

#include <eigen2/Eigen/Geometry>

#include "include/renderer/GeometryBase.hpp"
#include "include/renderer/MaterialBase.hpp"
#include "include/renderer/RenderBackend.hpp"
#include "include/renderer/tmp/tmp.hpp"

#include <thread>

void thread() {
    RenderBackend renderer(800, 600, ":0.0");

    GeometryCore ape1("teapot", "shiny");
    ape1.transform_.translate(Eigen::Vector3f(-2, 0, 0));

    GeometryCore ape2("teapot", "matt");
    ape2.transform_.translate(Eigen::Vector3f(2, 0, 0));
    ape2.transform_.scale(1.3);

    CameraCore cam(60.f, 4.f/3.f, 0.1f, 1000.f);
    cam.transform_.translate(Eigen::Vector3f(0, 0, 4));

    while (true) {
        ape1.transform_.rotate(Eigen::AngleAxisf(0.01, Eigen::Vector3f(0, 1, 0)));
        ape2.transform_.rotate(Eigen::AngleAxisf(-0.01, Eigen::Vector3f(0, 1, 0)));

        renderer.render({&ape1, &ape2}, {}, cam);
    }
}

int main() {
    GeometryBase::load_presets();
    MaterialBase::load_presets();

    RenderWindow::init();

    std::thread thread1(&thread);
    //std::thread thread2(&thread);

    thread1.join();
    //thread2.join();

    return 0;
}
